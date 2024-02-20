//
// Created by Alexander Nutz on 19/02/2024.
//

#include "../blocking_list.h"
#include <pthread.h>

/**
 * Initializes a normal BlockingList
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void BlockingList_init(struct BlockingList *list, size_t stride,
                       Ally ally, size_t initCap) {
    list->useMutex = true;
    pthread_mutex_init(&list->mutex, NULL);
    DynamicList_init(&list->dyn, stride, ally, initCap);
}

/**
 * Initializes a BlockingList where many threads should have read access at the same time.
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void BlockingList_initManyReader(struct BlockingList *list, size_t stride,
                                 Ally ally, size_t initCap) {
    list->useMutex = false;
    pthread_rwlock_init(&list->rwlock, NULL);
    DynamicList_init(&list->dyn, stride, ally, initCap);
}

void BlockingList_destroy(struct BlockingList *list) {
    BlockingList_startWriteAccess(list);
    DynamicList_clear(&list->dyn);
    BlockingList_stopWriteAccess(list);

    if (list->useMutex) {
        pthread_mutex_destroy(&list->mutex);
    } else {
        pthread_rwlock_destroy(&list->rwlock);
    }
}
