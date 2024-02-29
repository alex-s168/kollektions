//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_KALLOK_H
#define KOLLEKTIONS_KALLOK_H

#include <stddef.h>

#ifdef __cplusplus
namespace kallok {
extern "C" {
#endif

typedef struct {
    void (*free)(void *state, void *alloc, size_t old);

    void *(*alloc)(void *state, size_t size);

    void *(*realloc)(void *state, void *alloc, size_t old, size_t size);
} AllyImpl;

typedef struct {
    AllyImpl *impl;
    void *state;
} Ally;

Ally getLIBCAlloc();

struct AllyStats {
    Ally parent;
    size_t allocs;
    size_t frees;
    size_t reallocs;
};
Ally getStatAlloc(Ally parent, struct AllyStats *statisticDest);
#ifdef _INC_STDIO
void outputStats(struct AllyStats *stats, FILE *dest);
#endif

// A simple memory allocator that allocates elements in a fixed-length array.
// Does not have any memory-degragmentation features
Ally createFixedBasicAlloc(void *data, size_t limit);
void destroyFixedBasicAlloc(Ally ally);

#ifdef __cplusplus
}
}
#define KALLOK_PREFIX kallok::
#else
#define KALLOK_PREFIX /* */
#endif

#include "kallok_pages.h"

#endif //KOLLEKTIONS_KALLOK_H
