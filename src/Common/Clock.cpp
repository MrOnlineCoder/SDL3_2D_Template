#include <Common/Clock.hpp>

#include <SDL3/SDL_timer.h>

Clock::Clock() : m_timestamp(0)
{
    restart();
}

void Clock::restart()
{
    m_timestamp = SDL_GetTicks();
}

float Clock::getElapsedSeconds() const
{
    return static_cast<float>(getElapsedMilliseconds()) / 1000.0f;
}

std::uint64_t Clock::getElapsedMilliseconds() const
{
    return SDL_GetTicks() - m_timestamp;
}