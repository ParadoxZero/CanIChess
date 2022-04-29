#include "cordinate.h"

namespace base
{
    template<class T>
    Vector2d<T> operator+(Vector2d<T> lhs, Vector2d<T> rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    template<class T>
    Vector2d<T> operator-(Vector2d<T> lhs, Vector2d<T> rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    template<class T>
    bool operator==(const Vector2d<T>& lhs, const Vector2d<T>& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    template<class T>
    bool operator!=(const Vector2d<T>& lhs, const Vector2d<T>& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }
}