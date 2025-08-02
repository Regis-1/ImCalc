#include "Application.h"
#include <iostream>

bool processEvents(SDL_Event &e, const SDL_WindowID &wID) {
    while (SDL_PollEvent(&e)) {
        ImGui_ImplSDL3_ProcessEvent(&e);
        if (e.type == SDL_EVENT_QUIT)
            return true;
        if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && e.window.windowID == wID)
            return true;
    }

    return false;
}

void createImCalcWindow(ImGuiIO &io, ImGuiWindowFlags &wf) {
    ImVec2 buttonSize = ImVec2(30.0f, 30.0f);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
    ImGui::Begin("MainWindow", nullptr, wf);
    if (ImGui::Button("7", buttonSize))
        std::cout << "Clicked 7" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("8", buttonSize))
        std::cout << "Clicked 8" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("9", buttonSize))
        std::cout << "Clicked 9" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("/", buttonSize))
        std::cout << "Clicked /" << std::endl;

    if (ImGui::Button("4", buttonSize))
        std::cout << "Clicked 4" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("5", buttonSize))
        std::cout << "Clicked 5" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("6", buttonSize))
        std::cout << "Clicked 6" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("*", buttonSize))
        std::cout << "Clicked *" << std::endl;

    if (ImGui::Button("1", buttonSize))
        std::cout << "Clicked 1" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("2", buttonSize))
        std::cout << "Clicked 2" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("3", buttonSize))
        std::cout << "Clicked 3" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("-", buttonSize))
        std::cout << "Clicked -" << std::endl;

    if (ImGui::Button("C", buttonSize))
        std::cout << "Clicked C" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("0", buttonSize))
        std::cout << "Clicked 0" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("=", buttonSize))
        std::cout << "Clicked =" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("+", buttonSize))
        std::cout << "Clicked +" << std::endl;

    ImGui::Text("Application average %.3f ms/frame\n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

int main(int, char**) {
    std::unique_ptr<Application> app = Application::New();
    if (app == nullptr)
        return -1;

    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGuiWindowFlags imGuiFlags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    bool done = false;
    const SDL_WindowID windowID = app->getWindowID();
    SDL_Event event;
    while (!done) {
        // input and event processing
        done = processEvents(event, windowID);

        if (SDL_GetWindowFlags(app->getWindow()) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // setting data and updating
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        createImCalcWindow(io, imGuiFlags);

        // rendering
        ImGui::Render();
        SDL_SetRenderScale(app->getRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(app->getRenderer(), 0.5f, 0.5f, 0.5f, 1.0f);
        SDL_RenderClear(app->getRenderer());
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), app->getRenderer());
        SDL_RenderPresent(app->getRenderer());
    }

    return 0;
}
