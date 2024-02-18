//
// Created by Alexander Nutz on 17/02/2024.
//

#include "../static_list.h"

#include <string.h>

/**
 * @param list Self
 * @param pos At which index to remove.
 */
void StaticList_removeAt(struct StaticList *list, size_t pos) {
    if (pos != list->fixed.len - 1) {
        // not last element
        void *dest = FixedList_get(list->fixed, pos);
        void *src = FixedList_get(list->fixed, pos + 1);
        size_t amount = list->fixed.len - (pos + 1);
        memcpy(dest, src, amount * list->fixed.stride);
    }
    list->fixed.len --;
}

/**
 * @param list Self
 * @param first The start index where to remove
 * @param last The end index where to remove
 */
void StaticList_removeRange(struct StaticList *list,
                            size_t first, size_t last) {
    size_t amToRem = last - first + 1;
    if (last != list->fixed.len - 1) {
        // not last element
        void *dest = FixedList_get(list->fixed, first);
        void *src = FixedList_get(list->fixed, last + 1);
        size_t amount = list->fixed.len - (first + amToRem);
        memcpy(dest, src, amount * list->fixed.stride);
    }
    list->fixed.len -= amToRem;
}