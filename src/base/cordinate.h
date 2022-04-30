#ifndef __BASE__CORDINATE__
#define __BASE__CORDINATE__

#include <stdint.h>

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
    Vector2d<T> operator+(Vector2d<T> lhs, Vector2d<T> rhs);

    template <class T>
    Vector2d<T> operator-(Vector2d<T> lhs, Vector2d<T> rhs);

    template <class T>
    bool operator==(const Vector2d<T> &lhs, const Vector2d<T> &rhs);

    template <class T>
    bool operator!=(const Vector2d<T> &lhs, const Vector2d<T> &rhs);

    template <class T>
    inline Vector2d<T> &operator*(Vector2d<T> &lhs, T rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }
}

#endif // !__BASE__CORDINATE__