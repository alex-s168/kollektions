//
// Created by Alexander Nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_COPY_H
#define KOLLEKTIONS_COPY_H

#include "c.hpp"
#include "exception.hpp"
#include "../kallok.h"
#include "fixed_list.hpp"
#include "static_list.hpp"
#include "dynamic_list.hpp"

namespace kollektions {
    template <typename T>
    inline kollektions::DynamicList<T> DynamicList<T>::copy(kallok::Ally ally = kallok::getLIBCAlloc(),
                                                                         size_t additionalCap = 0) {
        auto list = kollektions::c::DynamicList{};
        kollektions::c::FixedList_copy(cFixed, &list, ally, additionalCap);
        return kollektions::DynamicList<T>(list);
    }
}



#endif //KOLLEKTIONS_COPY_H
