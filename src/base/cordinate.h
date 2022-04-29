#ifndef __BASE__CORDINATE__
#define __BASE__CORDINATE__

#include <stdint.h>

namespace base {
    struct Vector2d
    {
        int32_t x;
        int32_t y;

        Vector2d(int32_t x1, int32_t y1) : x(x1), y(y1) {}
        Vector2d(const Vector2d& old) :x(old.x), y(old.y) { }
    };

    struct Size2D
    {
        unsigned int x;
        unsigned int y;

        Size2D(unsigned int x1, unsigned int y1) : x(x1), y(y1) {}
        Size2D(const Size2D& old) :x(old.x), y(old.y) { }
    };

    Vector2d operator+(Vector2d lhs, Vector2d rhs);
    Vector2d operator-(Vector2d lhs, Vector2d rhs);
    bool operator==(const Vector2d& lhs, const Vector2d& rhs);
    bool operator!=(const Vector2d& lhs, const Vector2d& rhs);

    template<class T>
    inline Vector2d& operator*(Vector2d& lhs, T rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }
}

#endif // !__BASE__CORDINATE__