#ifndef KOLLEKTIONS_LISTS_H
#define KOLLEKTIONS_LISTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kallok.h"
#include "fixed_list.h"
#include "dynamic_list.h"
#include "linked_list.h"

/**
 * @param list Self
 * @param dest A uninitialized list
 * @param ally The allocator to use
 * @param additionalCap The additional initial capacity of the new list. (initCap = additionalCap + old.len)
 */
void FixedList_copy(struct FixedList list,
                    struct DynamicList *dest,
                    KALLOK_PREFIX Ally ally,
                    size_t additionalCap);

/**
 * @param list Self
 * @param dest A uninitialized list
 * @param ally The allocator to use
 * @param additionalCap The additional initial capacity of the new list. (initCap = additionalCap + old.len)
 */
void DynamicList_copy(struct DynamicList list,
                      struct DynamicList *dest,
                      KALLOK_PREFIX Ally ally,
                      size_t additionalCap);

#ifdef __cplusplus
}
#endif

#endif //KOLLEKTIONS_LISTS_H
