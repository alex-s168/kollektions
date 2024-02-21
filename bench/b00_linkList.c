#include "../linked_list.h"

int main() {
    struct DoubleLinkedList list;
    DoubleLinkedList_init(&list, sizeof(size_t), getLIBCAlloc());

    size_t i = 1000;
    while (i --> 0)
        DoubleLinkedList_add(&list, &i);

    DoubleLinkedList_clear(&list);

    return 0;
}
