#include <State/IntroState.hpp>
#include <Input/InputKeys.hpp>

IntroState::IntroState() : State(*g_gameContext), m_showingLogo(false)
{
    m_text.setString("STUDIO PRESENTS");
    m_text.setFont(
        m_context.assets->getMainFont());
    m_text.setPosition(
        m_context.windowCenter - m_text.getSize().x / 2);
    m_text.setFillColor(Colors::White);

    m_inputBinder.bindAction(
        InputKeys::SKIP_INTRO,
        [this](bool pressed)
        {
            if (pressed)
            {
                m_context.states->changeState(StateType::MAIN_MENU);
            }
        });
}

IntroState::~IntroState()
{
}

void IntroState::onEnter()
{
}

void IntroState::onInput(const SDL_Event &event)
{
}

void IntroState::onUpdate(float deltaTime)
{
    if (m_showingLogo)
    {
        if (m_clock.getElapsedSeconds() > 3.0f)
        {
            m_context.states->changeState(StateType::MAIN_MENU);
        }
    }
    else
    {
        if (m_clock.getElapsedSeconds() > 1.0f)
        {
            m_showingLogo = true;
            m_context.assets->playSound("intro");
            m_clock.restart();
        }
    }
}

void IntroState::onRender()
{
    if (m_showingLogo)
        m_text.render();
}

void IntroState::onExit()
{
    m_inputBinder.reset();
}