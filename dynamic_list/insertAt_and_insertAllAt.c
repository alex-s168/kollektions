//
// Created by Alexander Nutz on 17/02/2024.
//

#include "impl_utils.h"

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void DynamicList_insertAt(struct DynamicList *list, size_t index, void *data) {
    DynamicList_reserve(list, 1);
    StaticList_insertAt(DynamicList_as_StaticList(list), index, data);
}

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void DynamicList_insertAllAt(struct DynamicList *list, size_t index,
                             void *data, size_t len) {
    DynamicList_reserve(list, len);
    StaticList_insertAllAt(DynamicList_as_StaticList(list), index, data, len);
}