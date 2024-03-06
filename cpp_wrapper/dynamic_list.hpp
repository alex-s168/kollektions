//
// Created by alexander.nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_DYNAMIC_LIST_H
#define KOLLEKTIONS_DYNAMIC_LIST_H

#include "c.hpp"
#include "exception.hpp"
#include "fixed_list.hpp"
#include "../kallok_cpp.hpp"

namespace kollektions {
    /**
     * A dynamic-capacity, dynamic-length list
     * @tparam T
     */
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

        static kollektions::DynamicList<T> create(
                kallok::Ally allocator = kallok::getLIBCAlloc(),
                size_t initCap = 0) {
            auto list = kollektions::DynamicList<T>({
                                                            .fixed = { .stride = sizeof(T) }
                                                    });
            kollektions::c::DynamicList_init(&list.cDyn,
                                             sizeof(T),
                                             allocator,
                                             initCap);
            return list;
        }

        ~DynamicList() {
            kollektions::c::DynamicList_clear(&cDyn);
        }

        inline size_t capacity() {
            return cDyn.cap;
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

#endif //KOLLEKTIONS_DYNAMIC_LIST_H
