#pragma once

#include <SDL3/SDL.h>

#include <Common/Vector.hpp>
#include <Resources/AssetsManager.hpp>
#include <State/StateManager.hpp>

struct GameContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Vector2f windowSize;
    Vector2f windowCenter;
    Vector2f logicalSize;

    AssetsManager *assets;
    StateManager *states;

    uint64_t ticksSinceStart;
    float secondsSinceStart;

    float deltaTime;

    bool isRunning;
};

extern GameContext *g_gameContext;