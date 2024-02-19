//
// Created by alexander.nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_FIXED_LIST_H
#define KOLLEKTIONS_FIXED_LIST_H

#include "c.hpp"
#include "exception.hpp"

namespace kollektions {
    /**
     * A fixed-length, fixed-capacity list
     * @tparam T
     */
    template<typename T>
    class FixedList {
    public:
        kollektions::c::FixedList cFixed{
                .stride = sizeof(T)
        };

        FixedList() = delete;

        explicit FixedList(kollektions::c::FixedList list) {
            if (list.stride != sizeof(T))
                throw kollektions::IncompatibleStrideException();

            cFixed.data = list.data;
            cFixed.len = list.len;
        }

        explicit FixedList(std::vector <T> source) {
            cFixed.len = source.size();
            cFixed.data = source.data();
        }

        explicit FixedList(T *arr, size_t len) {
            cFixed.len = len;
            cFixed.data = arr;
        }

        inline int indexOf(T elem) {
            return kollektions::c::FixedList_indexOf(cFixed, elem);
        }

        inline int indexOfLast(T elem) {
            return kollektions::c::FixedList_indexOfLast(cFixed, elem);
        }

        inline T operator[](size_t index) {
            return *(T *) kollektions::c::FixedList_get(cFixed, index);
        }

        inline size_t length() {
            return cFixed.len;
        }

        inline void *data() {
            return cFixed.data;
        }
    };
}

#endif //KOLLEKTIONS_FIXED_LIST_H
