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

    void Run();

private:
    Application() {};
    bool InitializeSDLWindow();
    void InitializeImGui();
    bool ProcessEvents(SDL_Event &e, const SDL_WindowID &wID);

    const unsigned int windowHeight_ = 210;
    const unsigned int windowWidth_ = 160;
    const char *windowTitle_ = "ImCalc";
    SDL_Window *window_ = nullptr;
    SDL_WindowFlags windowFlags_ = 0;
    SDL_Renderer *renderer_ = nullptr;
    float mainScale_ = 0.0f;
    ImGuiIO io_;
};
