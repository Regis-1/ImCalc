#include "Application.h"
#include "CalcUI.h"

#include <iostream>

std::unique_ptr<Application> Application::New() {
    std::unique_ptr<Application> application(new Application());
    if (application->InitializeSDLWindow()) {
        application->InitializeImGui();
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

void Application::Run() {
    CalcUI calcUI;
    bool done = false;
    const SDL_WindowID windowID = SDL_GetWindowID(window_);
    SDL_Event event;
    while (!done) {
        // input and event processing
        done = ProcessEvents(event, windowID);

        if (SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // setting data and updating
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        io_ = ImGui::GetIO();
        calcUI.Prepare(io_);

        // rendering
        ImGui::Render();
        SDL_SetRenderScale(renderer_, io_.DisplayFramebufferScale.x, io_.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(renderer_, 0.5f, 0.5f, 0.5f, 1.0f);
        SDL_RenderClear(renderer_);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
        SDL_RenderPresent(renderer_);
    }
}

bool Application::InitializeSDLWindow() {
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

void Application::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale_);
    style.FontScaleDpi = mainScale_;

    ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer3_Init(renderer_);

    io_ = ImGui::GetIO();
    io_.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io_.FontGlobalScale = 1.5f;

}

bool Application::ProcessEvents(SDL_Event &e, const SDL_WindowID &wID) {
    while (SDL_PollEvent(&e)) {
        ImGui_ImplSDL3_ProcessEvent(&e);
        if (e.type == SDL_EVENT_QUIT)
            return true;
        if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && e.window.windowID == wID)
            return true;
    }

    return false;
}
