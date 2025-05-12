#include <Resources/SoundBuffer.hpp>

#include <Common/Logger.hpp>

SoundBuffer::SoundBuffer()
{
    m_chunk = nullptr;
}
SoundBuffer::~SoundBuffer()
{
    if (m_chunk)
    {
        Mix_FreeChunk(m_chunk);
    }
}

void SoundBuffer::loadFromFile(
    const std::string &filename)
{
    m_chunk = Mix_LoadWAV(filename.c_str());

    if (!m_chunk)
    {
        LOG_ERROR("Unable to load sound: %s", SDL_GetError());
        return;
    }

    Mix_VolumeChunk(m_chunk, MIX_MAX_VOLUME);
}

void SoundBuffer::play(int loops)
{
    if (m_chunk)
    {
        Mix_PlayChannel(
            -1,
            m_chunk,
            loops);
    }
}