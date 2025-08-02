#include "Application.h"

#include <iostream>

std::unique_ptr<Application> Application::New() {
    std::unique_ptr<Application> application(new Application());
    if (application->initializeSDLWindow()) {
        application->initializeImGui();
        return application;
    }

    return nullptr;
}

Application::~Application() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

const SDL_WindowID Application::getWindowID() {
    return SDL_GetWindowID(window_);
}

SDL_Window* Application::getWindow() {
    return window_;
}

SDL_Renderer* Application::getRenderer() {
    return renderer_;
}

bool Application::initializeSDLWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::cerr << "Error: SDL_Init(): " << SDL_GetError() << "\n";
        return false;
    }

    mainScale_ = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    windowFlags_ = SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    window_ = SDL_CreateWindow(windowTitle_, 
            (int)(windowWidth_ * mainScale_), (int)(windowHeight_ * mainScale_), windowFlags_);
    if (window_ == nullptr) {
        std::cerr << "Error SDL_CreateWindow(): " << SDL_GetError() << "\n";
        return false;
    }
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    SDL_SetRenderVSync(renderer_, 1);
    if (renderer_ == nullptr) {
        std::cerr << "Error SDL_CreateRenderer(): " << SDL_GetError() << "\n";
        return false;
    }
    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window_);

    return true;
}

void Application::initializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale_);
    style.FontScaleDpi = mainScale_;

    ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer3_Init(renderer_);
}
