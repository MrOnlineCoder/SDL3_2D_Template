#ifndef TEXT2D_HPP
#define TEXT2D_HPP

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

    void setFont(const Font &fnt);

    void setString(const std::string &str);

    void render();

    void setFillColor(Color color);

    void setPosition(const Vector2f &pos);

    void setOrigin(const Vector2f &origin);

    void useCenterOrigin() { setOrigin({m_bounds.width / 2, m_bounds.height / 2}); }

    const Vector2f &getPosition() const { return m_position; }
    const Vector2i &getSize() const { return m_size; }
    const FloatRect &getBounds() const { return m_bounds; }

private:
    void update();

    const Font *m_font;
    Vector2f m_position;
    Vector2i m_size;
    FloatRect m_bounds;
    Color m_fillColor;
    std::string m_string;
    Vector2f m_origin;

    SDL_Texture *m_texture;
};

#endif