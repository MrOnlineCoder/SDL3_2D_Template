#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <SDL3/SDL_rect.h>

template <typename T>
class Vector
{
public:
    Vector() : x(0), y(0) {}
    Vector(T x, T y) : x(x), y(y) {}

    Vector operator+(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(const Vector &other) const
    {
        return Vector(x * other.x, y * other.y);
    }

    Vector operator/(const Vector &other) const
    {
        return Vector(x / other.x, y / other.y);
    }

    Vector operator+(T scalar) const
    {
        return Vector(x + scalar, y + scalar);
    }

    Vector operator-(T scalar) const
    {
        return Vector(x - scalar, y - scalar);
    }

    Vector operator*(T scalar) const
    {
        return Vector(x * scalar, y * scalar);
    }

    Vector operator/(T scalar) const
    {
        return Vector(x / scalar, y / scalar);
    }

    Vector &operator+=(const Vector &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector &operator-=(const Vector &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector &operator*=(const Vector &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector &operator/=(const Vector &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector &operator+=(T scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector &operator-=(T scalar)
    {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vector &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector &operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Vector &other) const
    {
        return !(*this == other);
    }

    T x;
    T y;

    SDL_FRect toSDLRect()
    {
        return {x, y, 0, 0};
    }
};

typedef Vector<int> Vector2i;
typedef Vector<float> Vector2f;

#endif