//
// Created by Alexander Nutz on 17/02/2024.
//

#include "../static_list.h"

#include <assert.h>

int main() {
    int list_data[10];
    struct StaticList list;
    StaticList_init(&list, sizeof(int), list_data, 10);

    StaticList_add(&list, &(int) { 1 });
    StaticList_add(&list, &(int) { 2 });
    StaticList_add(&list, &(int) { 3 });
    StaticList_add(&list, &(int) { 4 });
    StaticList_add(&list, &(int) { 5 });

    StaticList_removeRange(&list, 1, 2);

    assert(list.fixed.len == 3);

    int ix = FixedList_indexOf(list.fixed, &(int) { 4 });
    assert(ix == 1);

#define assertElem(i, v) assert(*(int *)FixedList_get(list.fixed, i) == v)

    assertElem(0, 1);
    assertElem(1, 4);
    assertElem(2, 5);

    return 0;
}
