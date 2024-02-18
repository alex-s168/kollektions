//
// Created by Alexander Nutz on 17/02/2024.
//

#include <iostream>

#include "kollektions_cpp.hpp"

int main() {
    auto list = kollektions::DynamicList<int>::create();
    list.add(1);
    list.add(2);
    list.removeAt(0);
    for (size_t i = 0; i < list.length(); i ++) {
        std::cout << list[i] << " ";
    }

    return 0;
}
