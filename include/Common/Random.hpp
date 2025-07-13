#pragma once

#include <random>

#include <Common/Vector.hpp>

class Random
{
public:
    Random()
    {
        m_engine.seed(m_rd());
    }

    int generateInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(m_engine);
    }

    float generateFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(m_engine);
    }

    Vector2f generateVector(const Vector2f &min, const Vector2f &max)
    {
        float x = generateFloat(min.x, max.x);
        float y = generateFloat(min.y, max.y);
        return Vector2f(x, y);
    }

    std::mt19937 &getRandomEngine()
    {
        return m_engine;
    }

private:
    std::mt19937 m_engine;
    std::random_device m_rd;
};