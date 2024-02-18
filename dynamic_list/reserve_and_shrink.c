//
// Created by Alexander Nutz on 17/02/2024.
//

#include "impl_utils.h"

/**
 * Reserves space for at least x additional elements on top of the length of the list
 * @param list Self
 * @param additional The amount of additional elements to reserve on top of the length of the list
 */
void DynamicList_reserve(struct DynamicList *list, size_t additional) {
    size_t new = list->fixed.len + additional;

    if (new <= list->cap)
        return;

    new = (new + 3) & ~3;

    list->ally.impl->realloc(list->ally.state, list->fixed.data, list->cap, new);
    list->cap = new;
}

/**
 * Reserves space for exactly x additional elements on top of the length of the list
 * @param list Self
 * @param additional The amount of additional elements to reserve on top of the length of the list
 */
void DynamicList_reserveExact(struct DynamicList *list, size_t additional) {
    size_t new = list->fixed.len + additional;

    if (new <= list->cap)
        return;

    list->ally.impl->realloc(list->ally.state, list->fixed.data, list->cap, new);
    list->cap = new;
}

/**
 * Shrinks the list allocation to be as big as the list.
 * @param list Self
 */
void DynamicList_shrink(struct DynamicList *list) {
    if (list->cap == list->fixed.len)
        return;

    list->ally.impl->realloc(list->ally.state, list->fixed.data, list->cap, list->fixed.len);
    list->cap = list->fixed.len;
}