#include "../kash.h"
#include <stdint.h>

// non-cryptographic hash function
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash

#define FNV1A(type, prime, offset, dest, value, valueSize) { \
    type hash = offset;                                      \
    for (size_t i = 0; i < valueSize; i ++) {                \
        unsigned char byte = ((unsigned char *)value)[i];    \
        hash ^= byte;                                        \
        hash *= prime;                                       \
    }                                                        \
    *(type *)dest = hash;                                    \
}

#pragma GCC optimize
__attribute((hot))
void hash_fnv1a_32_hash(void *dest, void *value, size_t valueSize)
    FNV1A(uint32_t, 0x01000193, 0x811c9dc5, dest, value, valueSize)

#pragma GCC optimize
__attribute((hot))
void hash_fnv1a_64_hash(void *dest, void *value, size_t valueSize)
    FNV1A(uint64_t, 0x100000001B3, 0xcbf29ce484222325, dest, value, valueSize)

#pragma GCC optimize
__attribute((hot))
void hash_fnv1a_128_hash(void *dest, void *value, size_t valueSize)
    FNV1A(__uint128_t, 0x1000000000000000000013B, 0x6c62272e07bb014262b821756295c58d, dest, value, valueSize)

HashAlgo hash_fnv1a_32() {
    return (HashAlgo) { .fn = hash_fnv1a_32_hash, .hashSize = 4 };
}

HashAlgo hash_fnv1a_64() {
    return (HashAlgo) { .fn = hash_fnv1a_64_hash, .hashSize = 8 };
}

HashAlgo hash_fnv1a_128() {
    return (HashAlgo) { .fn = hash_fnv1a_128_hash, .hashSize = 16 };
}