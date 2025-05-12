#ifndef SOUND_BUFFER_HPP
#define SOUND_BUFFER_HPP

#include <SDL3_mixer/SDL_mixer.h>

#include <string>

class SoundBuffer
{
public:
    SoundBuffer();
    ~SoundBuffer();

    void loadFromFile(
        const std::string &filename);

    void play(int loops = 0);

private:
    Mix_Chunk *m_chunk;
};

#endif