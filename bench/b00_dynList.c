#include "../lists.h"

int main() {
    Ally ally = getLIBCAlloc();

    struct DynamicList list;
    DynamicList_init(&list, sizeof(size_t), ally, 0);

    size_t i = 1000;
    while (i --> 0)
        DynamicList_add(&list, &i);

    DynamicList_clear(&list);

    return 0;
}
