//
// Created by Alexander Nutz on 21/02/2024.
//

#include "../linked_list.h"

#include <string.h>

static struct DoubleLinkedElement *allocElem(struct DoubleLinkedList *list) {
    return list->ally.impl->alloc(list->ally.state,
                                  sizeof(struct DoubleLinkedElement) + list->stride);
}

/**
 * @param list Self
 * @param data The pointer to the element
 */
void DoubleLinkedList_add(struct DoubleLinkedList *list, void *data) {
    struct DoubleLinkedElement *elem = allocElem(list);
    memcpy(DoubleLinkedElement_data(elem), data, list->stride);
    elem->next = NULL;
    elem->prev = list->end;
    if (list->end != NULL)
        list->end->next = elem;
    list->end = elem;
    list->size += 1;
}

/**
 * @param list Self
 * @param data The pointer to the element
 */
void DoubleLinkedList_addFront(struct DoubleLinkedList *list, void *data) {
    struct DoubleLinkedElement *elem = allocElem(list);
    memcpy(DoubleLinkedElement_data(elem), data, list->stride);
    elem->prev = NULL;
    elem->next = list->start;
    if (list->start != NULL)
        list->start->prev = elem;
    list->start = elem;
    list->size += 1;
}
