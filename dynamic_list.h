//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_DYNAMIC_LIST_H
#define KOLLEKTIONS_DYNAMIC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "fixed_list.h"
#include "kallok.h"
#include "attrib.h"

struct DynamicList {
    struct FixedList fixed;
    size_t cap;

INTERNAL
    KALLOK_PREFIX Ally ally;
};

#define DynamicList_as_StaticList(dl) ((struct StaticList *) dl)

/**
 * @param list Self
 * @param stride The size of each element
 * @param cap The initial maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void DynamicList_init(struct DynamicList *list, size_t stride,
                      KALLOK_PREFIX Ally ally, size_t initCap);

/**
 * @param list Self
 */
void DynamicList_clear(struct DynamicList *list);

/**
 * @param list Self
 * @param data The pointer to the element
 */
void DynamicList_add(struct DynamicList *list, void *data);

/**
 * @param list Self
 * @param data The array of elements
 */
void DynamicList_addAll(struct DynamicList *list, void *data, size_t len);

/**
 * @param list Self
 * @param pos At which index to remove.
 */
void DynamicList_removeAt(struct DynamicList *list, size_t pos);

/**
 * @param list Self
 * @param first The start index where to remove
 * @param last The end index where to remove
 */
void DynamicList_removeRange(struct DynamicList *list,
                             size_t first, size_t last);

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void DynamicList_insertAt(struct DynamicList *list, size_t index, void *data);

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void DynamicList_insertAllAt(struct DynamicList *list, size_t index,
                             void *data, size_t len);

/**
 * Reserves space for at least x additional elements on top of the length of the list
 * @param list Self
 * @param additional The amount of additional elements to reserve on top of the length of the list
 */
void DynamicList_reserve(struct DynamicList *list, size_t additional);

/**
 * Reserves space for exactly x additional elements on top of the length of the list
 * @param list Self
 * @param additional The amount of additional elements to reserve on top of the length of the list
 */
void DynamicList_reserveExact(struct DynamicList *list, size_t additional);

/**
 * Shrinks the list allocation to be as big as the list.
 * @param list Self
 */
void DynamicList_shrink(struct DynamicList *list);

#ifdef __cplusplus
}
#endif

#endif //KOLLEKTIONS_DYNAMIC_LIST_H
