#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include <string>

#include <unordered_map>

enum FontStyle
{
    NORMAL = TTF_STYLE_NORMAL,
    BOLD = TTF_STYLE_BOLD,
    ITALIC = TTF_STYLE_ITALIC,
    UNDERLINE = TTF_STYLE_UNDERLINE,
    STRIKETHROUGH = TTF_STYLE_STRIKETHROUGH
};

struct FontCacheHash
{
    bool operator()(const std::pair<int, FontStyle> &key) const
    {
        return std::hash<int>()(key.first) ^ std::hash<int>()(static_cast<int>(key.second));
    }
};

class Font
{
public:
    Font();
    ~Font();

    void loadFromFile(const std::string &filepath);

    TTF_Font *obtainHandle(int ptsize, FontStyle style = FontStyle::NORMAL);

private:
    TTF_Font *m_baseHandle;

    std::unordered_map<std::pair<int, FontStyle>, TTF_Font *, FontCacheHash> m_handles;
};