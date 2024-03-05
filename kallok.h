//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_KALLOK_H
#define KOLLEKTIONS_KALLOK_H

#include <stddef.h>
#include "attrib.h"

#ifdef __cplusplus
namespace kallok {
extern "C" {
#endif

static size_t makeMultiple(size_t x, size_t y) {
    x += y - 1;
    x -= x % y;
    return x;
}

typedef struct {
    void (*free)(void *state, void *alloc, size_t old);

    void *(*alloc)(void *state, size_t size);

    void *(*realloc)(void *state, void *alloc, size_t old, size_t size);
} AllyImpl;

typedef struct {
    AllyImpl *impl;
    void *state;
} Ally;

#define yalloc(a, size)               a.impl->alloc(a.state, size)
#define yrealloc(a, alloc, old, size) a.impl->realloc(a.state, alloc, old, size)
#define yfree(a, alloc, old)          a.impl->free(a.state, alloc, old)

Ally getLIBCAlloc();

struct AllyStats {
    size_t allocs;
    size_t frees;
    size_t reallocs;

UNSAFE 
    Ally parent;
};
Ally getStatAlloc(Ally parent, struct AllyStats *statisticDest);
#ifdef _INC_STDIO
void outputStats(struct AllyStats *stats, FILE *dest);
#endif

typedef struct {
INTERNAL
    void *start;
    size_t len;
    void *next;
} AllyFixedBasicState;

// A simple memory allocator that allocates elements in a fixed-length array.
// Does not have any memory-defragmentation features
Ally createFixedBasicAlloc(AllyFixedBasicState *state, void *data, size_t limit);

// Allocates full OS pages
// useful for big lists
Ally getPageAlloc();

typedef struct {
INTERNAL
    AllyFixedBasicState parent;
    Ally parentAlly;
    Ally source;
} AllyDynamicBasicState;

// Based on \see createFixedBasicAlloc
// __Arena allocator__
Ally createBasicAlloc(AllyDynamicBasicState *state, Ally source);

typedef AllyDynamicBasicState AllyStandardState;

static Ally createStandardAlloc(AllyStandardState *state) {
    Ally paged = getPageAlloc();
    return createBasicAlloc(state, paged);
}

#ifdef __cplusplus
}
}
#define KALLOK_PREFIX kallok::
#else
#define KALLOK_PREFIX /* */
#endif

#include "kallok_pages.h"
#include "kallok_virtual.h"

#endif //KOLLEKTIONS_KALLOK_H
