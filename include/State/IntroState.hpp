#pragma once

#include <State/State.hpp>

#include <Render/Text2D.hpp>
#include <Render/Sprite.hpp>
#include <Common/Clock.hpp>
#include <Render/AnimatedSprite.hpp>
#include <Input/ScopedInputBinder.hpp>

class IntroState : public State
{
public:
    IntroState();
    virtual ~IntroState();

    virtual void onEnter();
    virtual void onInput(const SDL_Event &event);
    virtual void onUpdate(float deltaTime);
    virtual void onRender();
    virtual void onExit();

private:
    Text2D m_text;
    Sprite m_logo;
    Clock m_clock;
    bool m_showingLogo;
    ScopedInputBinder m_inputBinder;
};