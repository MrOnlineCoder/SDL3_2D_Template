#include <Render/Sprite.hpp>

#include <GameContext.hpp>

Sprite::Sprite() : m_texture(nullptr), m_position{0, 0}, m_size{0, 0}, m_textureRect{} {}

Sprite::~Sprite()
{
}

void Sprite::render()
{
    if (m_texture)
    {
        SDL_FRect rect = m_bounds.toSDLFRect();
        SDL_FRect tRect = m_textureRect.toSDLFRect();
        SDL_RenderTexture(
            g_gameContext->renderer,
            m_texture->getHandle(),
            &tRect,
            &rect);
    }
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = &texture;

    m_bounds.width = m_texture->getSize().x;
    m_bounds.height = m_texture->getSize().y;

    m_textureRect = {0, 0, m_texture->getSize().x, m_texture->getSize().y};
}

void Sprite::setPosition(const Vector2f &pos)
{
    m_position = pos;
    m_bounds.x = pos.x;
    m_bounds.y = pos.y;
}

void Sprite::setTextureRect(const IntRect &rect)
{
    m_textureRect = rect;
    m_bounds.width = rect.width;
    m_bounds.height = rect.height;
}