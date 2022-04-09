#include "cordinate.h"

namespace base
{
    Cordinate& operator+(Cordinate lhs, Cordinate rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    Cordinate& operator-(Cordinate lhs, Cordinate rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }
}