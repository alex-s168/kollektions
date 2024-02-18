//
// Created by Alexander Nutz on 17/02/2024.
//

#include "../static_list.h"

/**
 * @param list Self
 * @param stride The size of each element
 * @param cap The maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void StaticList_init(struct StaticList *list, size_t stride,
                     void *data, size_t cap) {
    list->fixed.stride = stride;
    list->fixed.data = data;
    list->cap = cap;
    list->fixed.len = 0;
}

/**
 * @param list Self
 */
void StaticList_clear(struct StaticList *list) {
    list->fixed.len = 0;
}