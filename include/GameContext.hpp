#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include <SDL3/SDL.h>

#include <Common/Vector.hpp>
#include <Resources/AssetsManager.hpp>
#include <State/StateManager.hpp>

struct GameContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    AssetsManager *assets;
    StateManager *states;
    uint64_t ticksSinceStart;
    float secondsSinceStart;
    Vector2f windowSize;
    Vector2f windowCenter;

    float deltaTime;

    bool isRunning;
};

extern GameContext *g_gameContext;

#endif