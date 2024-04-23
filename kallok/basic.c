//
// Created by Alexander Nutz on 04/03/2024.
//

#include "kallok.h"
#include <string.h>

// TODO: compactify after free
// TODO: wtf

static void alloc_free(void *stateIn, void *alloc, size_t old) {
    AllyDynamicBasicState *state = stateIn;
    yfree(state->parentAlly, alloc, old);
}

static void *alloc_alloc(void *stateIn, size_t new) {
    AllyDynamicBasicState *state = stateIn;
    
    void *a = yalloc(state->parentAlly, new);
    if (a != NULL)
        return a;

    {
        void *r = yrealloc(state->source,
                           state->parent.start,
                           state->parent.len,
                           state->parent.len + new + 32); // TODO: WE CAN'T JUST ASSUME 32 BYTES  !  ! !!!
        if (r == NULL)
            return NULL; 
        memcpy(r, state->parent.start, state->parent.len);
        yfree(state->source, state->parent.start, state->parent.len);
        state->parent.start = r;
        state->parent.len += new + 32;                                       // ^ ^ ^ ^
    }

    return yalloc(state->parentAlly, new);
}

static void *alloc_realloc(void *stateIn, void *alloc, size_t old, size_t newSize) {
    AllyDynamicBasicState *state = stateIn;
    
    void *a = yrealloc(state->parentAlly, alloc, old, newSize);
    if (a != NULL)
        return a;

    void *b = alloc_alloc(stateIn, newSize);
    if (b == NULL)
        return NULL;
    memcpy(b, alloc, old);
    alloc_free(stateIn, alloc, old);
    return b;
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
