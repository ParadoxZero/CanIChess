#include "cordinate.h"

namespace base
{
    Vector2d operator+(Vector2d lhs, Vector2d rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    Vector2d operator-(Vector2d lhs, Vector2d rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    bool operator==(const Vector2d& lhs, const Vector2d& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    bool operator!=(const Vector2d& lhs, const Vector2d& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }
}