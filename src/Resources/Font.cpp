#include <Resources/Font.hpp>

#include <Common/Logger.hpp>

Font::Font() : m_font(nullptr), m_style(FontStyle::NORMAL)
{
}

Font::~Font()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
    }
}

void Font::loadFromFile(const std::string &filepath, int ptsize)
{
    m_font = TTF_OpenFont(filepath.c_str(), 24);

    if (!m_font)
    {
        LOG_ERROR("Unable to load font: %s", SDL_GetError());
        return;
    }
}

void Font::setSize(unsigned int ptsize)
{
    if (m_font)
    {
        TTF_SetFontSize(m_font, ptsize);
    }
}

void Font::setStyle(int style)
{
    if (m_font)
    {
        TTF_SetFontStyle(m_font, style);
        m_style = style;
    }
}
