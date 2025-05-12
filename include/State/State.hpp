#ifndef STATE_HPP
#define STATE_HPP

#include <GameContext.hpp>
#include <SDL3/SDL_events.h>

class State
{
public:
    State(GameContext &context) : m_context(context) {}
    virtual ~State() = default;

    virtual void onEnter() = 0;
    virtual void onInput(const SDL_Event &event) = 0;
    virtual void onUpdate(float deltaTime) = 0;
    virtual void onRender() = 0;
    virtual void onExit() = 0;

protected:
    GameContext &m_context;
};

#endif