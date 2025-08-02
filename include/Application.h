#pragma once

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include <SDL3/SDL.h>

#include <memory>

class Application {
public:
    static std::unique_ptr<Application> New();
    ~Application();

    const SDL_WindowID getWindowID();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

private:
    Application() {};
    bool initializeSDLWindow();
    void initializeImGui();

    const unsigned int windowHeight_ = 400;
    const unsigned int windowWidth_ = 300;
    const char *windowTitle_ = "ImCalc";
    SDL_Window *window_ = nullptr;
    SDL_WindowFlags windowFlags_ = 0;
    SDL_Renderer *renderer_ = nullptr;
    float mainScale_ = 0.0f;
};
