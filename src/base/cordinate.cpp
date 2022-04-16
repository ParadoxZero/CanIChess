#include "cordinate.h"

namespace base
{
    Cordinate operator+(Cordinate lhs, Cordinate rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    Cordinate operator-(Cordinate lhs, Cordinate rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    bool operator==(const Cordinate& lhs, const Cordinate& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    bool operator!=(const Cordinate& lhs, const Cordinate& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }
}