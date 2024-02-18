//
// Created by Alexander Nutz on 17/02/2024.
//

#include "impl_utils.h"

/**
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void DynamicList_init(struct DynamicList *list, size_t stride,
                      Ally ally, size_t initCap) {
    void *alloc = NULL;
    if (initCap > 0) {
        alloc = ally.impl->alloc(ally.state, initCap * stride);
    }
    StaticList_init(DynamicList_as_StaticList(list), stride, alloc, initCap);
    list->ally = ally;
}

/**
 * @param list Self
 */
void DynamicList_clear(struct DynamicList *list) {
    list->ally.impl->free(list->ally.state, list->fixed.data, list->cap);
    list->cap = 0;
    list->fixed.len = 0;
    list->fixed.data = NULL;
}