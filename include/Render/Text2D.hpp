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

    SDL_Texture *m_texture;
};

#endif