#pragma once

#include <Resources/Font.hpp>
#include <Common/Vector.hpp>
#include <Common/Rect.hpp>
#include <Render/Color.hpp>

#include <string>

class Text2D
{
public:
    Text2D();
    ~Text2D();

    void setFont(Font &fnt);

    void setString(const std::string &str);

    void render();

    void setFillColor(Color color);

    void setPosition(const Vector2f &pos);

    void setOrigin(const Vector2f &origin);

    void setFontSize(int size);

    void useCenterOrigin() { setOrigin({m_bounds.width / 2, m_bounds.height / 2}); }

    const Vector2f &getPosition() const { return m_position; }
    const Vector2i &getSize() const { return m_size; }
    const FloatRect &getBounds() const { return m_bounds; }

private:
    void update();

    Font *m_font;
    int m_fontSize;
    Vector2f m_position;
    Vector2i m_size;
    FloatRect m_bounds;
    Color m_fillColor;
    std::string m_string;
    Vector2f m_origin;

    SDL_Texture *m_texture;
};
