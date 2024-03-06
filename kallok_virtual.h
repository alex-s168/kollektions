//
// Created by Alexander Nutz on 04/03/2024.
//

#ifndef KOLLEKTIONS_KALLOK_VIRTUAL_H
#define KOLLEKTIONS_KALLOK_VIRTUAL_H

#include <stddef.h>

#ifdef __cplusplus
namespace kallok {
 extern "C" {
#endif


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

typedef struct {
    void  *data;
    size_t size;

#ifdef _WIN32
    HANDLE hFile;
    HANDLE hMap;
#else
    int fd;
#endif
} VirtAlloc;

VirtAlloc virtualMap(int *err, const char *path);

void virtualUnmap(VirtAlloc alloc);

#ifdef __cplusplus
}
}
#ifndef KALLOK_PREFIX
#define KALLOK_PREFIX kallok::
#endif
#else
#ifndef KALLOK_PREFIX
#define KALLOK_PREFIX /* */
#endif
#endif


#endif //KOLLEKTIONS_KALLOK_VIRTUAL_H
