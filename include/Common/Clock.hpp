#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <cstdint>

class Clock
{
public:
    Clock();

    void restart();

    float getElapsedSeconds() const;
    std::uint64_t getElapsedMilliseconds() const;

private:
    std::uint64_t m_timestamp;
};

#endif