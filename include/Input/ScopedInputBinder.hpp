#pragma once

#include <Input/InputManager.hpp>

#include <vector>

class ScopedInputBinder
{
public:
    ScopedInputBinder();
    ~ScopedInputBinder();

    void bindAction(InputMapKey key, InputActionCallback callback);
    void bindAxis(InputMapKey key, InputAxisCallback callback);

    void reset();

private:
    std::vector<InputBindingId> m_bindings;
};