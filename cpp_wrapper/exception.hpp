//
// Created by alexander.nutz on 19/02/2024.
//

#ifndef KOLLEKTIONS_EXCEPTION_H
#define KOLLEKTIONS_EXCEPTION_H

namespace kollektions {
    class IncompatibleStrideException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
                return "Incompatible stride. = Incompatible types";
        }
    };

    class OutOfCapacityException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
                return "Out of capacity!";
        }
    };
}

#endif //KOLLEKTIONS_EXCEPTION_H
