//
// Created by Alexander Nutz on 29/02/2024.
//

/**
 * Library to allocate OS pages on Windows and Linux.
 * Can also make pages executable for JITs.
 */

#ifndef KALLOK_PAGES_H
#define KALLOK_PAGES_H

#include <stddef.h>

#ifdef __cplusplus
namespace kallok {
 extern "C" {
#endif

struct Page {
    void   *ptr;
    size_t  size;
};

/**
 * Allocate a readable and writable page
 */
struct Page alloc_pages(size_t bytes);

/**
 * Make a section in the page executable and readonly
 */
void make_exec(void *ptr, size_t size) ;

/**
 * Frees the whole page
 */
void free_page(struct Page page);

size_t page_size();

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

#endif //KALLOK_PAGES_H
