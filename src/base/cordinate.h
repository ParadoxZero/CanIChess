#ifndef __BASE__CORDINATE__
#define __BASE__CORDINATE__

#include <cstdint>
#include <cmath>
namespace base
{

    template <class T>
    struct Vector2d
    {
        T x;
        T y;

        Vector2d(T x1, T y1) : x(x1), y(y1) {}
        Vector2d(const Vector2d &old) : x(old.x), y(old.y) {}
    };

    using Vector2Di = Vector2d<int32_t>;
    using Vector2Du = Vector2d<uint32_t>;

    struct Size2D
    {
        unsigned int x;
        unsigned int y;

        Size2D(unsigned int x1, unsigned int y1) : x(x1), y(y1) {}
        Size2D(const Size2D &old) : x(old.x), y(old.y) {}
    };

    template <class T>
    inline Vector2d<T> operator+(Vector2d<T> lhs, Vector2d<T> rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    template <class T>
    inline Vector2d<T> operator-(Vector2d<T> lhs, Vector2d<T> rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    template <class T>
    inline bool operator==(const Vector2d<T> &lhs, const Vector2d<T> &rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    template <class T>
    inline bool operator!=(const Vector2d<T> &lhs, const Vector2d<T> &rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }

    template <class T>
    inline Vector2d<T> &operator*(Vector2d<T> &lhs, T rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }

    template <class T>
    inline Vector2d<T> getDirection(const Vector2d<T> &from, const Vector2d<T> &to)
    {
        T delta_x = from.x - to.x;
        T delta_y = from.y - to.y;
        return {delta_x ? delta_x / abs(delta_x) : 0, delta_y ? delta_y / abs(delta_y) : 0};
    }
}

#endif // !__BASE__CORDINATE__