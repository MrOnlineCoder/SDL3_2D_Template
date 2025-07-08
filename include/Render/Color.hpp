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
};

namespace Colors
{
    const Color White(255, 255, 255);
    const Color Black(0, 0, 0);
    const Color Red(255, 0, 0);
    const Color Green(0, 255, 0);
    const Color Blue(0, 0, 255);
    const Color Yellow(255, 255, 0);
    const Color Magenta(255, 0, 255);
    const Color Cyan(0, 255, 255);
    const Color Transparent(0, 0, 0, 0);
}