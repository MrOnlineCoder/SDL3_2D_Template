#include <State/StateManager.hpp>

#include <State/State.hpp>

#include <Common/Logger.hpp>

StateManager::StateManager()
{
    m_states.reserve(StateType::COUNT);
    m_currentState = nullptr;
}

StateManager::~StateManager()
{
    for (auto &state : m_states)
    {
        delete state;
    }
}

void StateManager::pushState(State *state)
{
    m_states.push_back(state);

    if (!m_currentState)
    {
        m_currentState = state;
        m_currentState->onEnter();
    }
}

void StateManager::changeState(StateType type)
{
    if (m_currentState)
        m_currentState->onExit();

    m_currentState = m_states[static_cast<int>(type)];

    m_currentState->onEnter();

    LOG_INFO("Changed state to %d", static_cast<int>(type));
}

void StateManager::handleInput(const SDL_Event &event)
{
    if (m_currentState)
        m_currentState->onInput(event);
}

void StateManager::update(float deltaTime)
{
    if (m_currentState)
        m_currentState->onUpdate(deltaTime);
}

void StateManager::render()
{
    if (m_currentState)
        m_currentState->onRender();
}
