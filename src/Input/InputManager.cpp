#include <Input/InputManager.hpp>

#include <Common/Logger.hpp>

#include <unordered_set>

InputManager::InputManager()
{
    m_inputBindings.reserve(64);
    m_inputMappings.reserve(16);

    m_nextBindingId = 0;
}

void InputManager::addAxis(InputMapKey key, InputDeviceAxis axis)
{
    InputMapEntry entry;
    entry.axis = axis;
    entry.trigger = 0;

    m_inputMappings[key] = entry;

    LOG_INFO("Added input axis mapping: %s -> %d", key.c_str(), static_cast<int>(axis));
}

void InputManager::addAction(InputMapKey key, SDL_Scancode scancode)
{
    InputMapEntry entry;
    entry.axis = InputDeviceAxis::NONE;
    entry.trigger = static_cast<std::uint32_t>(scancode);

    m_inputMappings[key] = entry;

    LOG_INFO("Added input action mapping: %s -> %d", key.c_str(), static_cast<int>(scancode));
}

void InputManager::addAction(InputMapKey key, InputActionTrigger trigger)
{
    InputMapEntry entry;
    entry.axis = InputDeviceAxis::NONE;
    entry.trigger = static_cast<std::uint32_t>(trigger);

    m_inputMappings[key] = entry;
}

InputBindingId InputManager::bindAction(InputMapKey key, InputActionCallback actionCallback)
{
    InputBindingEntry entry = {};
    entry.id = m_nextBindingId++;
    entry.mapKey = key;
    entry.actionCallback = actionCallback;

    m_inputBindings.push_back(entry);

    LOG_INFO("Bound action to key: %s with ID: %u", key.c_str(), entry.id);

    return entry.id;
}

InputBindingId InputManager::bindAxis(InputMapKey key, InputAxisCallback axisCallback)
{
    InputBindingEntry entry = {};
    entry.id = m_nextBindingId++;
    entry.mapKey = key;
    entry.axisCallback = axisCallback;

    m_inputBindings.push_back(entry);

    LOG_INFO("Bound axis to key: %s with ID: %u", key.c_str(), entry.id);

    return entry.id;
}

void InputManager::removeBinding(InputBindingId id)
{
    auto it = m_inputBindings.begin();
    while (it != m_inputBindings.end())
    {
        if (it->id == id)
        {
            it = m_inputBindings.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }

    LOG_INFO("Removed input binding with ID: %u", id);
}

static InputActionTrigger toInputTrigger(SDL_GamepadButton button)
{
    switch (button)
    {
    case SDL_GAMEPAD_BUTTON_SOUTH:
        return InputActionTrigger::GAMEPAD_BUTTON_A;
    case SDL_GAMEPAD_BUTTON_EAST:
        return InputActionTrigger::GAMEPAD_BUTTON_B;
    case SDL_GAMEPAD_BUTTON_NORTH:
        return InputActionTrigger::GAMEPAD_BUTTON_Y;
    case SDL_GAMEPAD_BUTTON_WEST:
        return InputActionTrigger::GAMEPAD_BUTTON_X;

    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
        return InputActionTrigger::GAMEPAD_BUTTON_LEFT_BUMPER;
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
        return InputActionTrigger::GAMEPAD_BUTTON_RIGHT_BUMPER;
    default:
        return InputActionTrigger::TRIGGER_OFFSET; // Invalid trigger
    }
}

void InputManager::handleInputEvent(const SDL_Event &event)
{
    if (m_inputMappings.empty() && m_inputBindings.empty())
    {
        return;
    }

    const bool isKeyboardEvent = event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP;
    const bool isMouseButtonEvent = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP;
    const bool isMouseMotionEvent = event.type == SDL_EVENT_MOUSE_MOTION;
    const bool isMouseWheelEvent = event.type == SDL_EVENT_MOUSE_WHEEL;
    const bool isGamepadButtonEvent = event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || event.type == SDL_EVENT_GAMEPAD_BUTTON_UP;

    const bool isAxisEvent = isMouseMotionEvent || isMouseWheelEvent;
    const bool isActionEvent = isKeyboardEvent || isMouseButtonEvent || isGamepadButtonEvent;

    if (!isAxisEvent && !isActionEvent)
    {
        return;
    }

    for (const auto &mapping : m_inputMappings)
    {
        const auto &mappingKey = mapping.first;
        const auto &mappingEntry = mapping.second;

        if (isMouseMotionEvent && mappingEntry.isAxis())
        {
            if (mappingEntry.axis == InputDeviceAxis::MOUSE_X)
            {
                invokeAxis(mappingKey, event.motion.x);
            }
            else if (mappingEntry.axis == InputDeviceAxis::MOUSE_Y)
            {
                invokeAxis(mappingKey, event.motion.y);
            }
        }

        if (isKeyboardEvent && mappingEntry.isKeyboardTrigger())
        {
            if (mappingEntry.trigger == static_cast<std::uint32_t>(event.key.scancode))
            {
                invokeAction(mappingKey, event.type == SDL_EVENT_KEY_DOWN);
            }
        }

        if (isMouseButtonEvent && !mappingEntry.isAxis())
        {
            const bool wasPressed = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            if (event.button.button == SDL_BUTTON_LEFT && mappingEntry.trigger == static_cast<std::uint32_t>(InputActionTrigger::MOUSE_LEFT_CLICK))
            {
                invokeAction(mappingKey, wasPressed);
            }
            else if (event.button.button == SDL_BUTTON_RIGHT && mappingEntry.trigger == static_cast<std::uint32_t>(InputActionTrigger::MOUSE_RIGHT_CLICK))
            {
                invokeAction(mappingKey, wasPressed);
            }
            else if (event.button.button == SDL_BUTTON_MIDDLE && mappingEntry.trigger == static_cast<std::uint32_t>(InputActionTrigger::MOUSE_MIDDLE_CLICK))
            {
                invokeAction(mappingKey, wasPressed);
            }
        }

        if (isGamepadButtonEvent && mappingEntry.isGamepadTrigger())
        {
            InputActionTrigger targetTrigger = toInputTrigger(static_cast<SDL_GamepadButton>(event.gbutton.button));

            if (mappingEntry.trigger == static_cast<std::uint32_t>(targetTrigger))
            {
                invokeAction(mappingKey, event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN);
            }
        }
    }
}

void InputManager::invokeAction(InputMapKey key, bool pressed)
{
    for (const auto &binding : m_inputBindings)
    {
        if (binding.mapKey == key && binding.isAction())
        {
            binding.actionCallback(pressed);
        }
    }
}
void InputManager::invokeAxis(InputMapKey key, float value)
{
    for (const auto &binding : m_inputBindings)
    {
        if (binding.mapKey == key && binding.isAxis())
        {
            binding.axisCallback(value);
        }
    }
}