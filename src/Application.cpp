#include <Application.hpp>
#include <GameContext.hpp>
#include <Common/Logger.hpp>
#include <Common/Debug.hpp>
#include <Resources/Texture.hpp>
#include <Resources/SoundBuffer.hpp>
#include <Render/Text2D.hpp>
#include <Render/Sprite.hpp>

#include <State/IntroState.hpp>
#include <State/MainMenuState.hpp>

#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <imgui_impl_sdlrenderer3.h>
#include <imgui_impl_sdl3.h>
#include <imgui.h>

Application::Application()
{
    ASSERT(g_gameContext == nullptr);

    g_gameContext = new GameContext();
    g_gameContext->secondsSinceStart = 0;
    g_gameContext->ticksSinceStart = 0;
    g_gameContext->deltaTime = 0;
    g_gameContext->isRunning = true;

    if (!SDL_Init(
            SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_ERROR("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0)
    {
        LOG_ERROR("Unable to initialize SDL_mixer: %s", SDL_GetError());
        return;
    }

    SDL_AudioSpec audioSpec;
    audioSpec.channels = MIX_DEFAULT_CHANNELS;
    audioSpec.format = MIX_DEFAULT_FORMAT;
    audioSpec.freq = MIX_DEFAULT_FREQUENCY;

    if (!Mix_OpenAudio(
            0, &audioSpec))
    {
        LOG_ERROR("Unable to open audio: %s", SDL_GetError());
        return;
    }

    if (!TTF_Init())
    {
        LOG_ERROR("Unable to initialize SDL_ttf: %s", SDL_GetError());
        return;
    }

    auto displayMode = SDL_GetCurrentDisplayMode(
        SDL_GetPrimaryDisplay());

    g_gameContext->window = SDL_CreateWindow(
        "Game",
        displayMode->w,
        displayMode->h,
        SDL_WINDOW_FULLSCREEN);

    if (!g_gameContext->window)
    {
        LOG_ERROR("Unable to create window: %s", SDL_GetError());
        return;
    }

    LOG_INFO("Created full-screen window (%dx%d)",
             displayMode->w,
             displayMode->h);

    g_gameContext->windowSize = {(float)displayMode->w, (float)displayMode->h};
    g_gameContext->windowCenter = g_gameContext->windowSize / 2.0f;

    g_gameContext->renderer = SDL_CreateRenderer(
        g_gameContext->window,
        NULL);

    if (!g_gameContext->renderer)
    {
        LOG_ERROR("Unable to create renderer: %s", SDL_GetError());
        return;
    }

    const char *rendererName = SDL_GetRendererName(g_gameContext->renderer);

    initImGui();

    LOG_INFO("Using renderer: %s", rendererName);

    loadAssets();
    loadStates();

    LOG_INFO("Initialization successful");
}

void Application::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL3_InitForSDLRenderer(g_gameContext->window, g_gameContext->renderer);

    ImGui_ImplSDLRenderer3_Init(g_gameContext->renderer);
}

void Application::loadAssets()
{
    LOG_INFO("Loading assets...");

    g_gameContext->assets = new AssetsManager();

    g_gameContext->assets->loadMainFont("fonts/retganon.ttf");
    g_gameContext->assets->loadSound("intro", "sounds/intro.mp3");

    LOG_INFO("Assets loaded");
}

void Application::loadStates()
{
    g_gameContext->states = new StateManager();

    // type = StateType::Intro
    g_gameContext->states->pushState(new IntroState());

    // type = StateType::MainMenu
    g_gameContext->states->pushState(new MainMenuState());
}

void Application::run()
{
    LOG_INFO("Starting main loop");
    SDL_Event event;

    uint64_t lastTicks = SDL_GetTicks();

    while (g_gameContext->isRunning)
    {
        g_gameContext->ticksSinceStart = SDL_GetTicks();
        g_gameContext->secondsSinceStart = g_gameContext->ticksSinceStart / 1000.0f;
        lastTicks = g_gameContext->ticksSinceStart;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                break;
            }

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_ESCAPE)
                {
                    break;
                }
            }

            ImGui_ImplSDL3_ProcessEvent(&event);

            g_gameContext->states->handleInput(event);
        }

        g_gameContext->states->update(
            g_gameContext->deltaTime);

        SDL_SetRenderDrawColor(
            g_gameContext->renderer,
            0,
            0,
            0,
            255);
        SDL_RenderClear(g_gameContext->renderer);

        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        g_gameContext->states->render();

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g_gameContext->renderer);

        SDL_RenderPresent(
            g_gameContext->renderer);

        SDL_Delay(
            1000 / 60);

        g_gameContext->deltaTime = (SDL_GetTicks() - lastTicks) / 1000.0f;
        lastTicks = SDL_GetTicks();
    }
}

Application::~Application()
{
    LOG_INFO("Destroying application and resources...");

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(g_gameContext->window);
    SDL_DestroyRenderer(g_gameContext->renderer);

    delete g_gameContext->states;
    delete g_gameContext->assets;

    delete g_gameContext;
    g_gameContext = nullptr;

    Mix_HaltMusic();
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    LOG_INFO("Shutdown complete");
}