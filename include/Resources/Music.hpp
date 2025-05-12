#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SDL3_mixer/SDL_mixer.h>

#include <string>

class Music
{
public:
    Music();
    ~Music();

    bool openFromFile(const std::string &filename);

    void play();
    void pause();
    void stop();

private:
    Mix_Music *m_music;
};

#endif