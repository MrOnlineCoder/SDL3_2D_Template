#pragma once

#include <GameContext.hpp>
#include <SDL3/SDL_events.h>

class State
{
public:
    State(GameContext &context) : m_context(context) {}
    virtual ~State() = default;

    virtual void onEnter() = 0;

    /// @brief Low-level input handling. For handling game related events, use higher-level input mapping.
    /// @param event
    virtual void onInput(const SDL_Event &event) {};

    virtual void onUpdate(float deltaTime) = 0;
    virtual void onRender() = 0;

    virtual void onExit() {};

protected:
    GameContext &m_context;
};