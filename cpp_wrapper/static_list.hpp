//
// Created by alexander.nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_STATIC_LIST_H
#define KOLLEKTIONS_STATIC_LIST_H

#include "c.hpp"
#include "exception.hpp"
#include "fixed_list.hpp"

namespace kollektions {
    /**
     * A fixed-capacity, dynamic-length list.
     * @tparam T
     */
    template<typename T>
    class StaticList : public kollektions::FixedList<T> {
        kollektions::c::StaticList cStat{};

        explicit StaticList(kollektions::c::StaticList list) :
                kollektions::FixedList<T>(list.fixed) {
            if (list.fixed.stride != sizeof(T))
                throw kollektions::IncompatibleStrideException();
            cStat.fixed = list.fixed;
            cStat.cap = list.cap;
            cStat.ally = list.ally;
        }

        static kollektions::StaticList<T> from(
                T *data,
                size_t cap,
                size_t len = 0) {
            auto list = kollektions::StaticList<T>({
                .fixed = {.stride = sizeof(T)}
            });
            kollektions::c::StaticList_init(&list.cStat,
                                            sizeof(T),
                                            data,
                                            cap);
            list.cStat.fixed.len = len;
            return list;
        }

        static inline kollektions::StaticList<T> from(std::vector <T> array) {
            return from(array.data(), array.size(), array.size());
        }

        static inline kollektions::StaticList<T> from(kollektions::FixedList<T> list) {
            return from(list.data(), list.length(), list.length());
        }

        inline size_t capacity() {
            return cStat.cap;
        }

        inline void add(T element) {
            if (kollektions::c::StaticList_add(&cDyn, &element) == 0)
                throw kollektions::OutOfCapacityException();
        }

        inline void addAll(T *data, size_t len) {
            if (kollektions::c::StaticList_addAll(&cDyn, data, len) == 0)
                throw kollektions::OutOfCapacityException();
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

            kollektions::c::StaticList_removeAt(&cDyn, index);
        }

        void removeRange(size_t first, size_t last) {
            if (last < first) {
                size_t temp = first;
                first = last;
                last = temp;
            }

            if (last >= this->length())
                throw std::out_of_range("Given index out of range!");

            kollektions::c::StaticList_removeRange(&cDyn, first, last);
        }

        inline void insertAt(size_t index, T data) {
            if (index > this->length())
                throw std::out_of_range("Given index out of range!");

            if (this->length() == this->capacity())
                throw kollektions::OutOfCapacityException();

            kollektions::c::StaticList_insertAt(&cDyn, index, data);
        }

        inline void insertAllAt(size_t index, T *data, size_t len) {
            if (index > this->length())
                throw std::out_of_range("Given index out of range!");

            if (this->length() + len > this->capacity())
                throw kollektions::OutOfCapacityException();

            kollektions::c::StaticList_insertAllAt(&cDyn, index, data, len);
        }

        inline void insertAllAt(size_t index, std::vector<T> elements) {
            insertAllAt(index, elements.data(), elements.size());
        }

        inline void insertAllAt(size_t index, kollektions::FixedList<T> elements) {
            insertAllAt(index, elements.data(), elements.length());
        }
    };
}

#endif //KOLLEKTIONS_STATIC_LIST_H
