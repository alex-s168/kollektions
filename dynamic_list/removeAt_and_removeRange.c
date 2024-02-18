//
// Created by Alexander Nutz on 17/02/2024.
//

#include "impl_utils.h"

/**
 * @param list Self
 * @param pos At which index to remove.
 */
void DynamicList_removeAt(struct DynamicList *list, size_t pos) {
    StaticList_removeAt(DynamicList_as_StaticList(list), pos);
    DynamicList_internal_postRemove(list);
}

/**
 * @param list Self
 * @param first The start index where to remove
 * @param last The end index where to remove
 */
void DynamicList_removeRange(struct DynamicList *list,
                             size_t first, size_t last) {
    StaticList_removeRange(DynamicList_as_StaticList(list), first, last);
    DynamicList_internal_postRemove(list);
}