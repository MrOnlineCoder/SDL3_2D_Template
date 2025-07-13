#pragma once

#include <SDL3/SDL_render.h>

class Color
{
public:
    Color() : r(0), g(0), b(0), a(255) {}
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : r(r), g(g), b(b), a(a) {}

    unsigned char r, g, b, a;

    operator SDL_Color() const
    {
        return {r, g, b, a};
    }

    static Color fromAlpha(unsigned char alpha)
    {
        return Color(0, 0, 0, alpha);
    }

    static Color fromHex(unsigned int hex)
    {
        return Color(
            (hex >> 16) & 0xFF,
            (hex >> 8) & 0xFF,
            hex & 0xFF,
            255);
    }

    Color mixWith(const Color &other, float factor) const
    {
        unsigned char newR = static_cast<unsigned char>(r + (other.r - r) * factor);
        unsigned char newG = static_cast<unsigned char>(g + (other.g - g) * factor);
        unsigned char newB = static_cast<unsigned char>(b + (other.b - b) * factor);
        unsigned char newA = static_cast<unsigned char>(a + (other.a - a) * factor);
        return Color(newR, newG, newB, newA);
    }

    Color withAlpha(unsigned char alpha) const
    {
        return Color(r, g, b, alpha);
    }
};

namespace Colors
{
    static const Color White(255, 255, 255);
    static const Color Black(0, 0, 0);
    static const Color Red(255, 0, 0);
    static const Color Green(0, 255, 0);
    static const Color Blue(0, 0, 255);
    static const Color Yellow(255, 255, 0);
    static const Color Magenta(255, 0, 255);
    static const Color Cyan(0, 255, 255);
    static const Color Transparent(0, 0, 0, 0);
}