//
// Created by Alexander Nutz on 21/02/2024.
//

#ifndef KOLLEKTIONS_LINKED_LIST_H
#define KOLLEKTIONS_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "dynamic_list.h"
#include "kallok.h"
#include "attrib.h"

struct DoubleLinkedElement {
    struct DoubleLinkedElement *next;
    struct DoubleLinkedElement *prev;
};

static inline void *DoubleLinkedElement_data(struct DoubleLinkedElement *elem) {
    return elem + sizeof(struct DoubleLinkedElement);
}

struct DoubleLinkedList {
    size_t size;
    size_t stride;
    struct DoubleLinkedElement *start;
    struct DoubleLinkedElement *end;

INTERNAL
    KALLOK_PREFIX Ally ally;
};

static void DoubleLinkedList_init(struct DoubleLinkedList *list, size_t stride, KALLOK_PREFIX Ally ally) {
    list->size = 0;
    list->stride = stride;
    list->start = NULL;
    list->end = NULL;
    list->ally = ally;
}

/**
 * @param list Self
 */
void DoubleLinkedList_clear(struct DoubleLinkedList *list);

struct DoubleLinkedElement *DoubleLinkedList_linkAt(struct DoubleLinkedList *list, size_t index);

struct DoubleLinkedFindResult {
    struct DoubleLinkedElement *link;
    void *data;
    size_t index;
};

struct DoubleLinkedFindResult DoubleLinkedList_find(struct DoubleLinkedList *list, void *element);

struct DoubleLinkedFindResult DoubleLinkedList_findLast(struct DoubleLinkedList *list, void *element);

/**
 * Removes a link from the list. The link will be deallocated afterwards.
 * @param list
 * @param element
 */
void DoubleLinkedList_remove(struct DoubleLinkedList *list, struct DoubleLinkedElement *element);

/**
 * Removes all links from [first] (inclusive) to [end] (inclusive) from the list and deallocates the links.
 * @param list
 * @param first
 * @param last
 * @param removed
 */
void DoubleLinkedList_removeMultiple(struct DoubleLinkedList *list, struct DoubleLinkedElement *first, struct DoubleLinkedElement *last, size_t removed);

/**
 * @param list Self
 * @param data The pointer to the element
 */
void DoubleLinkedList_add(struct DoubleLinkedList *list, void *data);

/**
 * @param list Self
 * @param data The pointer to the element
 */
void DoubleLinkedList_addFront(struct DoubleLinkedList *list, void *data);

/**
 * @param list Self
 * @param data The array of elements
 */
void DoubleLinkedList_addAll(struct DoubleLinkedList *list, void *data, size_t len);

/**
 * @param list Self
 * @param data The array of elements
 */
void DoubleLinkedList_addAllFront(struct DoubleLinkedList *list, void *data, size_t len);

/**
 * @param list Self
 * @param dest The destination list where to add all the elements of this list
 */
void DoubleLinkedList_flattenInto(struct DoubleLinkedList *list, struct DynamicList *dest);

#ifdef __cplusplus
}
#endif

#endif //KOLLEKTIONS_LINKED_LIST_H
