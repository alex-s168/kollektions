#include "../kallok.h"
#include <stdlib.h>
#include <string.h>

struct FState {
    void *data;
    void *end;
    void *nextFree;
};

static void FincrementNextFree(struct FState *state) {
    if (*(char *)state->nextFree == 0)
        return;
}

static void *Falloc(void *stateIn, size_t size) {
    struct FState *state = stateIn;
    void *new = state->nextFree + size;
    if (new >= state->end)
        return NULL;

    
}

static void *Frealloc(void *stateIn, void *alloc, size_t old, size_t new) {
    struct FState *state = stateIn;
}

static void Ffree(void *stateIn, void *alloc, size_t size) {
    struct FState *state = stateIn;
}

AllyImpl impl = {
    .alloc = Falloc,
    .realloc = Frealloc,
    .free = Ffree
};

// A simple memory allocator that allocates elements in a fixed-length array.
// Does not have any memory-degragmentation features
Ally createFixedBasicAlloc(void *data, size_t limit) {
    struct FState *state = malloc(sizeof(struct FState));
    
    memset(data, 0, limit);

    state->data = data;
    state->end = data + limit;
    state->nextFree = data;

    Ally ally;
    ally.state = state;
    ally.impl = &impl; 

    return ally;
}

void destroyFixedBasicAlloc(Ally ally) {
    free(ally.state);
}


