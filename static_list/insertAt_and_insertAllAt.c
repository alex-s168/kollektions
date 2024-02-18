//
// Created by Alexander Nutz on 17/02/2024.
//

#include "../static_list.h"

#include <string.h>

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void StaticList_insertAt(struct StaticList *list, size_t index, void *data) {
    return StaticList_insertAllAt(list, index, data, 1);
}

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void StaticList_insertAllAt(struct StaticList *list, size_t index,
                            void *data, size_t len) {
    void *elem = FixedList_get(list->fixed, index);
    {
        void *src = elem;
        void *dst = FixedList_get(list->fixed, index + len);
        size_t am = list->fixed.len - index - len;
        memcpy(dst, src, am * list->fixed.stride);
    }
    {
        void *src = data;
        void *dst = elem;
        size_t am = len;
        memcpy(dst, src, am * list->fixed.stride);
    }
}