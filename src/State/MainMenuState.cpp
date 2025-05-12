#include <State/MainMenuState.hpp>

#include <Common/ImGui.hpp>

MainMenuState::MainMenuState() : State(*g_gameContext)
{
}
MainMenuState::~MainMenuState() {}

void MainMenuState::onEnter()
{
}

void MainMenuState::onInput(const SDL_Event &event)
{
}

void MainMenuState::onUpdate(float deltaTime)
{
}

void MainMenuState::onRender()
{
    ImGui::Begin("Main Menu");
    if (ImGui::Button("Start Game"))
    {
        m_context.states->changeState(StateType::GAME);
    }
    if (ImGui::Button("Credits"))
    {
        m_context.states->changeState(StateType::CREDITS);
    }
    if (ImGui::Button("Exit"))
    {
        m_context.isRunning = false;
    }
    ImGui::End();
}

void MainMenuState::onExit()
{
}