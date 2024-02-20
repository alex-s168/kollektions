//
// Created by Alexander Nutz on 19/02/2024.
//

#include "../blocking_list.h"
#include <pthread.h>

void BlockingList_startReadAccess(struct BlockingList *list) {
    if (list->useMutex) {
        pthread_mutex_lock(&list->mutex);
    } else {
        pthread_rwlock_rdlock(&list->rwlock);
    }
}

void BlockingList_stopReadAccess(struct BlockingList *list) {
    if (list->useMutex) {
        pthread_mutex_unlock(&list->mutex);
    } else {
        pthread_rwlock_unlock(&list->rwlock);
    }
}

void BlockingList_startWriteAccess(struct BlockingList *list) {
    if (list->useMutex) {
        pthread_mutex_lock(&list->mutex);
    } else {
        pthread_rwlock_wrlock(&list->rwlock);
    }
}

void BlockingList_stopWriteAccess(struct BlockingList *list) {
    if (list->useMutex) {
        pthread_mutex_unlock(&list->mutex);
    } else {
        pthread_rwlock_unlock(&list->rwlock);
    }
}
