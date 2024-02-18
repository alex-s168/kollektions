//
// Created by Alexander Nutz on 17/02/2024.
//

#include "../static_list.h"

#include <string.h>

/**
 * @param list Self
 * @param data The pointer to the element
 * @return 1 if ok. 0 if cap already reached.
 */
int StaticList_add(struct StaticList *list, void *data) {
    if (list->fixed.len >= list->cap)
        return 0;

    void *dest = FixedList_get(list->fixed, list->fixed.len);
    memcpy(dest, data, list->fixed.stride);

    list->fixed.len ++;

    return 1;
}

/**
 * @param list Self
 * @param data The array of elements
 * @return 1 if ok. 0 if cap already reached.
 */
int StaticList_addAll(struct StaticList *list, void *data, size_t len) {
    if (list->fixed.len + len > list->cap)
        return 0;

    void *dest = FixedList_get(list->fixed, list->fixed.len);
    memcpy(dest, data, list->fixed.stride * len);

    list->fixed.len += len;

    return 1;
}