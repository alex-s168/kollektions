//
// Created by Alexander Nutz on 17/02/2024.
//

#ifndef KOLLEKTIONS_KOLLEKTIONS_CPP_HPP
#define KOLLEKTIONS_KOLLEKTIONS_CPP_HPP

#include <cstddef>
#include <vector>
#include <list>
#include <stdexcept>

#include "kallok_cpp.hpp"

namespace kollektions {
    namespace c {
#include "lists.h"
    }

    class IncompatibleStrideException: public std::exception
    {
        [[nodiscard]] const char * what() const noexcept override {
            return "Incompatible stride. = Incompatible types";
        }
    };

    template <typename T>
    class DynamicList;

    template <typename T>
    class FixedList {
    public:
        kollektions::c::FixedList cFixed {
            .stride = sizeof(T)
        };

        FixedList() = delete;

        explicit FixedList(kollektions::c::FixedList list) {
            if (list.stride != sizeof(T))
                throw kollektions::IncompatibleStrideException();

            cFixed.data = list.data;
            cFixed.len = list.len;
        }

        explicit FixedList(std::vector<T> source) {
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
            return * (T *) kollektions::c::FixedList_get(cFixed, index);
        }

        inline kollektions::DynamicList<T> copy(kallok::Ally ally = kallok::getLIBCAlloc(),
                                                size_t additionalCap = 0) {
            auto list = kollektions::c::DynamicList {};
            kollektions::c::FixedList_copy(cFixed, &list, ally, additionalCap);
            return kollektions::DynamicList<T>(list);
        }

        inline size_t length() {
            return cFixed.len;
        }

        inline void *data() {
            return cFixed.data;
        }
    };

    template <typename T>
    class DynamicList: public kollektions::FixedList<T> {
    public:
        kollektions::c::DynamicList cDyn {};

        explicit DynamicList(kollektions::c::DynamicList list):
        kollektions::FixedList<T>(list.fixed) {
            if (list.fixed.stride != sizeof(T))
                throw kollektions::IncompatibleStrideException();
            cDyn.fixed = list.fixed;
            cDyn.cap = list.cap;
            cDyn.ally = list.ally;
        }

//        explicit DynamicList(kallok::Ally allocator = kallok::getLIBCAlloc(),
//                             size_t initCap = 0):
//        kollektions::FixedList<T>(cDyn.fixed) {
//            kollektions::c::DynamicList_init(&cDyn, sizeof(T), allocator, initCap);
//        }

        static kollektions::DynamicList<T> create(
                kallok::Ally allocator = kallok::getLIBCAlloc(),
                size_t initCap = 0) {
            auto list = kollektions::DynamicList<T>({ .fixed = { .stride = sizeof(T) } });
            kollektions::c::DynamicList_init(&list.cDyn, sizeof(T), allocator, initCap);
            return list;
        }

        ~DynamicList() {
            kollektions::c::DynamicList_clear(&cDyn);
        }

        inline void add(T element) {
            kollektions::c::DynamicList_add(&cDyn, &element);
        }

        inline void addAll(T *data, size_t len) {
            kollektions::c::DynamicList_addAll(&cDyn, data, len);
        }

        inline void addAll(std::vector<T> elements) {
            addAll(elements.data(), elements.size());
        }

        inline void addAll(kollektions::FixedList<T> elements) {
            addAll(elements.data(), elements.length());
        }

        void removeAt(size_t index) {
            if (index >= this->length())
                throw std::out_of_range("Given index out of range!");

            kollektions::c::DynamicList_removeAt(&cDyn, index);
        }

        void removeRange(size_t first, size_t last) {
            if (last < first) {
                size_t temp = first;
                first = last;
                last = temp;
            }

            if (last >= this->length())
                throw std::out_of_range("Given index out of range!");

            kollektions::c::DynamicList_removeRange(&cDyn, first, last);
        }

        inline void insertAt(size_t index, T data) {
            if (index > this->length())
                throw std::out_of_range("Given index out of range!");

            kollektions::c::DynamicList_insertAt(&cDyn, index, data);
        }

        inline void insertAllAt(size_t index, T *data, size_t len) {
            if (index > this->length())
                throw std::out_of_range("Given index out of range!");

            kollektions::c::DynamicList_insertAllAt(&cDyn, index, data, len);
        }

        inline void insertAllAt(size_t index, std::vector<T> elements) {
            insertAllAt(index, elements.data(), elements.size());
        }

        inline void insertAllAt(size_t index, kollektions::FixedList<T> elements) {
            insertAllAt(index, elements.data(), elements.length());
        }

        /**
         * Reserves space for at least x additional elements on top of the length of the list
         * @param additional The amount of additional elements to reserve on top of the length of the list
         */
        inline void reserve(size_t additional) {
            kollektions::c::DynamicList_reserve(&cDyn, additional);
        }

        /**
         * Reserves space for exactly x additional elements on top of the length of the list
         * @param additional The amount of additional elements to reserve on top of the length of the list
         */
        inline void reserveExact(size_t additional) {
            kollektions::c::DynamicList_reserveExact(&cDyn, additional);
        }

        /**
         * Shrinks the list allocation to be as big as the list.
         */
         inline void shrink() {
             kollektions::c::DynamicList_shrink(&cDyn);
         }
    };
}


#endif //KOLLEKTIONS_KOLLEKTIONS_CPP_HPP
