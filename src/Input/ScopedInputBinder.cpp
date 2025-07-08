#include <Input/ScopedInputBinder.hpp>

#include <GameContext.hpp>

ScopedInputBinder::ScopedInputBinder()
{
}

ScopedInputBinder::~ScopedInputBinder()
{
    reset();
}

void ScopedInputBinder::bindAction(InputMapKey key, InputActionCallback callback)
{
    m_bindings.push_back(
        g_gameContext->input.bindAction(key, std::move(callback)));
}

void ScopedInputBinder::bindAxis(InputMapKey key, InputAxisCallback callback)
{
    m_bindings.push_back(
        g_gameContext->input.bindAxis(key, std::move(callback)));
}

void ScopedInputBinder::reset()
{
    for (auto bindingId : m_bindings)
    {
        g_gameContext->input.removeBinding(bindingId);
    }
    m_bindings.clear();
}