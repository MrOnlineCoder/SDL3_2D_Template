#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_events.h>

#include <Common/Vector.hpp>

using InputMapKey = std::string;
using InputBindingId = std::uint32_t;
using InputActionCallback = std::function<void(bool)>;
using InputAxisCallback = std::function<void(float)>;

enum class InputDeviceAxis
{
    NONE = 0,
    MOUSE_X,
    MOUSE_Y,
    MOUSE_WHEEL,
    GAMEPAD_LEFT_STICK_X,
    GAMEPAD_LEFT_STICK_Y,
    GAMEPAD_RIGHT_STICK_X,
    GAMEPAD_RIGHT_STICK_Y,
    GAMEPAD_LEFT_TRIGGER,
    GAMEPAD_RIGHT_TRIGGER,
};

enum class InputActionTrigger
{
    TRIGGER_OFFSET = SDL_SCANCODE_COUNT + 1,
    MOUSE_LEFT_CLICK,
    MOUSE_RIGHT_CLICK,
    MOUSE_MIDDLE_CLICK,
    GAMEPAD_BUTTON_A,
    GAMEPAD_BUTTON_B,
    GAMEPAD_BUTTON_X,
    GAMEPAD_BUTTON_Y,
    GAMEPAD_BUTTON_LEFT_BUMPER,
    GAMEPAD_BUTTON_RIGHT_BUMPER,
};

struct InputBindingEntry
{
    InputBindingId id;
    InputMapKey mapKey;
    InputActionCallback actionCallback;
    InputAxisCallback axisCallback;

    bool isAction() const
    {
        return !!actionCallback;
    }

    bool isAxis() const
    {
        return !!axisCallback;
    }
};

struct InputMapEntry
{
    InputDeviceAxis axis;
    std::uint32_t trigger;

    bool isAxis() const
    {
        return axis != InputDeviceAxis::NONE;
    }

    bool isKeyboardTrigger() const
    {
        return trigger > 0 && trigger < static_cast<std::uint32_t>(InputActionTrigger::TRIGGER_OFFSET);
    }

    bool isGamepadTrigger() const
    {
        return trigger >= static_cast<std::uint32_t>(InputActionTrigger::GAMEPAD_BUTTON_A) &&
               trigger <= static_cast<std::uint32_t>(InputActionTrigger::GAMEPAD_BUTTON_RIGHT_BUMPER);
    }
};

class InputManager
{
public:
    InputManager();

    void addAxis(InputMapKey key, InputDeviceAxis axis);
    void addAction(InputMapKey key, SDL_Scancode scancode);
    void addAction(InputMapKey key, InputActionTrigger trigger);

    InputBindingId bindAction(InputMapKey key, InputActionCallback actionCallback);
    InputBindingId bindAxis(InputMapKey key, InputAxisCallback axisCallback);

    void removeBinding(InputBindingId id);

    void handleInputEvent(const SDL_Event &event);

private:
    void invokeAction(InputMapKey key, bool pressed);
    void invokeAxis(InputMapKey key, float value);

    std::unordered_map<InputMapKey, InputMapEntry> m_inputMappings;
    std::vector<InputBindingEntry> m_inputBindings;

    InputBindingId m_nextBindingId;
};