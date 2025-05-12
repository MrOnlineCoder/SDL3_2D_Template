#ifndef FONT_HPP
#define FONT_HPP

#include <SDL3_ttf/SDL_ttf.h>

#include <string>

enum FontStyle
{
    NORMAL = TTF_STYLE_NORMAL,
    BOLD = TTF_STYLE_BOLD,
    ITALIC = TTF_STYLE_ITALIC,
    UNDERLINE = TTF_STYLE_UNDERLINE,
    STRIKETHROUGH = TTF_STYLE_STRIKETHROUGH
};

class Font
{
public:
    Font();
    ~Font();

    void loadFromFile(const std::string &filepath, int ptsize = 18);

    TTF_Font *getFont() const { return m_font; }

    void setSize(unsigned int ptsize);
    void setStyle(int style);

private:
    int m_style;
    TTF_Font *m_font;
};

#endif