#pragma once

#include <stdint.h>

namespace base {
    struct Cordinate
    {
        int8_t x;
        int8_t y;

         Cordinate(uint8_t x1, uint8_t y1) : x(x1), y(y1){}
    };

    Cordinate& operator+(Cordinate lhs, Cordinate rhs);
    Cordinate& operator-(Cordinate lhs, Cordinate rhs);
    bool operator==(const Cordinate& lhs, const Cordinate& rhs);
}