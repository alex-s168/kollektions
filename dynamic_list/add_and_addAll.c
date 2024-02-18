//
// Created by Alexander Nutz on 17/02/2024.
//

#include "impl_utils.h"


/**
 * @param list Self
 * @param data The pointer to the element
 */
void DynamicList_add(struct DynamicList *list, void *data) {
    DynamicList_reserve(list, 1);
    StaticList_add(DynamicList_as_StaticList(list), data);
}

/**
 * @param list Self
 * @param data The array of elements
 */
void DynamicList_addAll(struct DynamicList *list, void *data, size_t len) {
    DynamicList_reserve(list, len);
    StaticList_addAll(DynamicList_as_StaticList(list), data, len);
}