#pragma once

#include <string>
#include <Common/Vector.hpp>
#include <SDL3/SDL_render.h>

class Texture
{
public:
    Texture();
    bool loadFromFile(const std::string &filepath);
    bool loadFromSurface(SDL_Surface *surface);

    ~Texture();

    SDL_Texture *getHandle() const { return m_texture; }

    const Vector2i &getSize() const { return m_size; }

private:
    SDL_Texture *m_texture;
    Vector2i m_size;
};