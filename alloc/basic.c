//
// Created by Alexander Nutz on 04/03/2024.
//

#include "../kallok.h"

// TODO: compactify after free

static void alloc_free(void *stateIn, void *alloc, size_t old) {
    AllyDynamicBasicState *state = stateIn;
    yfree(state->parentAlly, alloc, old);
}

static void *alloc_alloc(void *stateIn, size_t new) {
    AllyDynamicBasicState *state = stateIn;
    void *a = yalloc(state->parentAlly, new);
    if (a != NULL)
        return a;
    // TODO
    // void *b = yrealloc(state->source, state->parent.data, );
    return NULL;
}

static void *alloc_realloc(void *stateIn, void *alloc, size_t old, size_t newSize) {
    AllyDynamicBasicState *state = stateIn;
    // TODO
}

static AllyImpl impl = {
    .alloc = alloc_alloc,
    .free = alloc_free,
    .realloc = alloc_realloc,
};

Ally createBasicAlloc(AllyDynamicBasicState *state, Ally source) {
    state->parentAlly = createFixedBasicAlloc(&state->parent, NULL, 0);
    state->source = source;
    return (Ally) { .state = state, .impl = &impl };
}