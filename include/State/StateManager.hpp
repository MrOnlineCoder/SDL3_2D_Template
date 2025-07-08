#pragma once

#include <SDL3/SDL_events.h>

#include <vector>

enum StateType
{
    INTRO = 0,
    MAIN_MENU,
    GAME,
    CREDITS,

    COUNT
};

class State;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void pushState(State *state);
    void changeState(StateType type);

    void handleInput(const SDL_Event &event);
    void update(float deltaTime);
    void render();

private:
    std::vector<State *> m_states;
    State *m_currentState;
};
