#include <Render/Text2D.hpp>

#include <Common/Logger.hpp>
#include <GameContext.hpp>

Text2D::Text2D()
    : m_font(nullptr),
      m_position(Vector2f(0.0f, 0.0f)),
      m_fillColor(Colors::White),
      m_string(""),
      m_texture(nullptr)
{
}
Text2D::~Text2D()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

void Text2D::setFont(const Font &fnt)
{
    m_font = &fnt;
    update();
}

void Text2D::setString(const std::string &str)
{
    m_string = str;
    update();
}

void Text2D::render()
{
    if (m_texture)
    {
        SDL_FRect dstRect = m_bounds.toSDLFRect();
        SDL_RenderTexture(g_gameContext->renderer, m_texture, nullptr, &dstRect);
    }
}

void Text2D::setFillColor(Color color)
{
    m_fillColor = color;
    update();
}

void Text2D::setPosition(const Vector2f &pos)
{
    m_position = pos;
    m_bounds.x = pos.x;
    m_bounds.y = pos.y;
}

void Text2D::update()
{
    if (!m_font || m_string.empty())
        return;

    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }

    SDL_Surface *surface = TTF_RenderText_Blended(
        m_font->getFont(),
        m_string.c_str(),
        m_string.size(),
        m_fillColor);

    if (!surface)
    {
        LOG_ERROR("Unable to render text: %s", SDL_GetError());
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(
        g_gameContext->renderer, surface);

    if (!m_texture)
    {
        LOG_ERROR("Unable to create texture from surface for text rendering: %s", SDL_GetError());
        return;
    }

    float tw, th;

    SDL_GetTextureSize(m_texture, &tw, &th);

    m_size = Vector2i(tw, th);

    m_bounds.width = m_size.x;
    m_bounds.height = m_size.y;

    SDL_DestroySurface(surface);
}