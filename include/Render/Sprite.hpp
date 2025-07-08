#pragma once

#include <Common/Vector.hpp>
#include <Resources/Texture.hpp>
#include <Common/Rect.hpp>

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void setTexture(const Texture &texture);

    void setPosition(const Vector2f &pos);

    const Vector2f &getSize() const { return m_size; }

    const Vector2f &getPosition() const { return m_position; }

    const FloatRect &getBounds() const { return m_bounds; }

    void setTextureRect(const IntRect &rect);

    void move(const Vector2f &offset)
    {
        m_position += offset;
        m_bounds.x += offset.x;
        m_bounds.y += offset.y;
    }

    void render();

private:
    Vector2f m_position;
    Vector2f m_size;
    FloatRect m_bounds;
    IntRect m_textureRect;
    const Texture *m_texture;
};