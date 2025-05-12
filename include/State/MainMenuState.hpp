#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include <State/State.hpp>

#include <Render/Text2D.hpp>
#include <Render/Sprite.hpp>
#include <Common/Clock.hpp>
#include <Render/AnimatedSprite.hpp>

class MainMenuState : public State
{
public:
    MainMenuState();
    virtual ~MainMenuState();

    virtual void onEnter();
    virtual void onInput(const SDL_Event &event);
    virtual void onUpdate(float deltaTime);
    virtual void onRender();
    virtual void onExit();

private:
};

#endif