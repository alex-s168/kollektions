//
// Created by Alexander Nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_BLOCKING_LIST_H
#define KOLLEKTIONS_BLOCKING_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>

#include "dynamic_list.h"
#include "kallok.h"
#include "attrib.h"

struct BlockingList {
UNSAFE
    struct DynamicList dyn;

INTERNAL
    pthread_rwlock_t rwlock;
    bool useMutex;
    pthread_mutex_t mutex;
};

/**
 * Initializes a normal BlockingList
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void BlockingList_init(struct BlockingList *list, size_t stride,
                       KALLOK_PREFIX Ally ally, size_t initCap);

/**
 * Initializes a BlockingList where many threads should have read access at the same time.
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void BlockingList_initManyReader(struct BlockingList *list, size_t stride,
                                 KALLOK_PREFIX Ally ally, size_t initCap);

void BlockingList_startReadAccess(struct BlockingList *list);
void BlockingList_stopReadAccess(struct BlockingList *list);

void BlockingList_startWriteAccess(struct BlockingList *list);
void BlockingList_stopWriteAccess(struct BlockingList *list);

void BlockingList_destroy(struct BlockingList *list);

#ifdef __cplusplus
}
#endif

#endif //KOLLEKTIONS_BLOCKING_LIST_H
