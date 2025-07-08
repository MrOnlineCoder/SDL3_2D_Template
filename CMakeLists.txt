set(PROJECT_NAME game)

cmake_minimum_required(VERSION 3.16)
project(${PROJECT_NAME})

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_SOURCE_DIR_TIMEOUT 300)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CLANG_CXX_LANGUAGE_STANDARD "c++17")
set(CMAKE_BUILD_TYPE Debug)

enable_language(OBJC)

set(SOURCES 
    src/Main.cpp
    src/Application.cpp
    src/GameContext.cpp
    src/Resources/Texture.cpp
    src/Resources/SoundBuffer.cpp
    src/Resources/Font.cpp
    src/Render/Text2D.cpp
    src/Render/Sprite.cpp
    src/Resources/AssetsManager.cpp
    src/State/IntroState.cpp
    src/State/StateManager.cpp
    src/Common/Clock.cpp
    src/Render/AnimatedSprite.cpp
    src/Resources/Music.cpp
    src/State/MainMenuState.cpp
    src/Input/InputManager.cpp
    src/Input/ScopedInputBinder.cpp)

FetchContent_Declare(
    SDL3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
    GIT_TAG "release-3.2.12"
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_image
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image"
    GIT_TAG "main"
)
FetchContent_MakeAvailable(SDL3_image)

set(SDLMIXER_MOD OFF CACHE BOOL "" FORCE)
set(SDLMIXER_MIDI OFF CACHE BOOL "" FORCE)
set(SDLMIXER_VENDORED ON CACHE BOOL "" FORCE)
set(SDLMIXER_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDLMIXER_GME OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3_mixer
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_mixer"
    GIT_TAG "main"
)
FetchContent_MakeAvailable(SDL3_mixer)

set(SDLTTF_VENDORED ON CACHE BOOL "")
set(SDLTTF_FREETYPE_VENDORED OFF CACHE BOOL "")
set(SDLTTF_PLUTOSVG OFF CACHE BOOL "" FORCE)
set(SDLTTF_SAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SDL3_ttf
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf"
    GIT_TAG "main"
)
FetchContent_MakeAvailable(SDL3_ttf)

FetchContent_Declare(
  imgui
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG "v1.91.9b"
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  box2d
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  GIT_REPOSITORY https://github.com/erincatto/box2d
  GIT_TAG "v3.1.0"
)

FetchContent_MakeAvailable(box2d)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


set(IMGUI_DIR ${imgui_SOURCE_DIR})

set(IMGUI_SOURCES
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
  ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
  ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR}/backends)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf nlohmann_json::nlohmann_json)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/assets"
            "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/assets"
    )