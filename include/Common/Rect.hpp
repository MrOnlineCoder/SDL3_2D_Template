#pragma once
#include <Common/Vector.hpp>

#include <SDL3/SDL_rect.h>

template <typename T>
class Rect
{
public:
    Rect() : x(0), y(0), width(0), height(0) {}
    Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}

    Rect<T> operator+(const Rect<T> &rect)
    {
        return Rect<T>(x + rect.x, y + rect.y, width + rect.width, height + rect.height);
    }

    Rect<T> operator-(const Rect<T> &rect)
    {
        return Rect<T>(x - rect.x, y - rect.y, width - rect.width, height - rect.height);
    }

    bool isPointInside(Vector<T> point)
    {
        return point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height;
    }

    SDL_FRect toSDLFRect()
    {
        return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};
    }

    SDL_Rect toSDLRect()
    {
        return {x, y, width, height};
    }

    T x, y, width, height;
};

using IntRect = Rect<int>;
using FloatRect = Rect<float>;