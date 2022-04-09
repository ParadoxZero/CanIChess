#pragma once

#include <stdint.h>

namespace base {
    struct Cordinate
    {
        int8_t x;
        int8_t y;
    };

    Cordinate& operator+(Cordinate lhs, Cordinate rhs);
    Cordinate& operator-(Cordinate lhs, Cordinate rhs);
}