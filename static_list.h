//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_STATIC_LIST_H
#define KOLLEKTIONS_STATIC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "fixed_list.h"

struct StaticList {
    struct FixedList fixed;
    size_t cap;
};

/**
 * @param list Self
 * @param stride The size of each element
 * @param cap The maximum amount of elements
 * @param data The array of data. needs to be at least @arg cap * @arg stride
 * @return The index of the element. -1 if not found.
 */
void StaticList_init(struct StaticList *list, size_t stride,
                     void *data, size_t cap);

/**
 * @param list Self
 */
void StaticList_clear(struct StaticList *list);

/**
 * @param list Self
 * @param data The pointer to the element
 * @return 1 if ok. 0 if cap already reached.
 */
int StaticList_add(struct StaticList *list, void *data);

/**
 * @param list Self
 * @param data The array of elements
 * @return 1 if ok. 0 if cap already reached.
 */
int StaticList_addAll(struct StaticList *list, void *data, size_t len);

/**
 * @param list Self
 * @param pos At which index to remove.
 */
void StaticList_removeAt(struct StaticList *list, size_t pos);

/**
 * @param list Self
 * @param first The start index where to remove
 * @param last The end index where to remove
 */
void StaticList_removeRange(struct StaticList *list,
                            size_t first, size_t last);

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void StaticList_insertAt(struct StaticList *list, size_t index, void *data);

/**
 * @param list Self
 * @param list At what position to insert the element
 * @param data The element to add
 */
void StaticList_insertAllAt(struct StaticList *list, size_t index,
                            void *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif //KOLLEKTIONS_STATIC_LIST_H