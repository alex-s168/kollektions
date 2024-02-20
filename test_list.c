//
// Created by Alexander Nutz on 17/02/2024.
//

#include "static_list.h"

#include <stdio.h>

int main() {
    int list_data[10];
    struct StaticList list;
    StaticList_init(&list, sizeof(int), list_data, 10);

    StaticList_add(&list, (int[]) { 1 });
    StaticList_add(&list, (int[]) { 2 });
    StaticList_add(&list, (int[]) { 3 });
    StaticList_add(&list, (int[]) { 4 });
    StaticList_add(&list, (int[]) { 5 });

    StaticList_removeRange(&list, 1, 2);

    int ix = FixedList_indexOf(list.fixed, (int[]) { 4 });
    printf("index of 4: %i\n\nList contents:\n", ix);

    for (size_t i = 0; i < list.fixed.len; i ++) {
        int *x = FixedList_get(list.fixed, i);
        printf(" %i\n", *x);
    }
}