//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_KALLOK_H
#define KOLLEKTIONS_KALLOK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

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

#ifdef __cplusplus
}
#define KALLOK_PREFIX kallok::
#else
#define KALLOK_PREFIX /* */
#endif

#endif //KOLLEKTIONS_KALLOK_H
