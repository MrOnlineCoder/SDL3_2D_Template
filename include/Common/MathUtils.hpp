#pragma once

#include <math.h>

namespace MathUtils
{
    inline float toRadians(float degrees)
    {
        return degrees * M_PI / 180.0f;
    }

    inline float toDegrees(float radians)
    {
        return radians * 180.0f / M_PI;
    }
}