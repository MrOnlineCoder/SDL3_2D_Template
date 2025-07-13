#include <Resources/Font.hpp>

#include <Common/Logger.hpp>

Font::Font() : m_baseHandle(nullptr)
{
}

Font::~Font()
{
    for (const auto &pair : m_handles)
    {
        if (pair.second && pair.second != m_baseHandle)
        {
            TTF_CloseFont(pair.second);
        }
    }

    if (m_baseHandle)
    {
        TTF_CloseFont(m_baseHandle);
    }
}

void Font::loadFromFile(const std::string &filepath)
{
    m_baseHandle = TTF_OpenFont(filepath.c_str(), 24);

    if (!m_baseHandle)
    {
        LOG_ERROR("Unable to load base font: %s", SDL_GetError());
        return;
    }

    m_handles[{24, FontStyle::NORMAL}] = m_baseHandle;

    LOG_INFO("Font loaded from file: %s", filepath.c_str());
}

TTF_Font *Font::obtainHandle(int ptsize, FontStyle style)
{
    auto it = m_handles.find({ptsize, style});

    if (it != m_handles.end())
    {
        return it->second;
    }

    TTF_Font *newHandle = TTF_CopyFont(m_baseHandle);

    TTF_SetFontSize(newHandle, ptsize);
    TTF_SetFontStyle(newHandle, static_cast<TTF_FontStyleFlags>(style));

    m_handles[{ptsize, style}] = newHandle;
    return newHandle;
}