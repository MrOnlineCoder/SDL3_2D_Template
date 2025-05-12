#include <Resources/Texture.hpp>

#include <GameContext.hpp>
#include <Common/Logger.hpp>

#include <SDL3_image/SDL_image.h>

Texture::Texture() : m_texture(nullptr), m_size(0, 0)
{
}

bool Texture::loadFromFile(const std::string &filepath)
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }

    m_texture = IMG_LoadTexture(g_gameContext->renderer, filepath.c_str());

    if (!m_texture)
    {
        LOG_ERROR("Unable to load image: %s", SDL_GetError());
        return false;
    }

    float tw, th;

    SDL_GetTextureSize(
        m_texture,
        &tw, &th);

    m_size = Vector2i(tw, th);

    return true;
}

bool Texture::loadFromSurface(SDL_Surface *surface)
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }

    m_texture = SDL_CreateTextureFromSurface(g_gameContext->renderer, surface);

    if (!m_texture)
    {
        LOG_ERROR("Unable to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_size = Vector2i(surface->w, surface->h);

    return true;
}

Texture::~Texture()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}