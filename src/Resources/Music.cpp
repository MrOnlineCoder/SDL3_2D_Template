#include <Resources/Music.hpp>

Music::Music() : m_music(nullptr)
{
}

Music::~Music()
{
    if (m_music != nullptr)
    {
        Mix_FreeMusic(m_music);
    }
}

bool Music::openFromFile(const std::string &filename)
{
    m_music = Mix_LoadMUS(filename.c_str());
    return m_music != nullptr;
}

void Music::play()
{
    Mix_PlayMusic(m_music, -1);
}

void Music::pause()
{
    Mix_PauseMusic();
}

void Music::stop()
{
    Mix_HaltMusic();
}