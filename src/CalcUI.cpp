#include "CalcUI.h"

#include <iostream>

void CalcUI::Prepare(ImGuiIO &io) {
    ImGui::SetNextWindowPos(pos_);
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));

    ImGui::Begin(id_.c_str(), nullptr, flags_);

    float contentWidth = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
    float textWidth = ImGui::CalcTextSize(displayText_.c_str()).x;
    float newCursorPos = contentWidth - textWidth;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + newCursorPos);
    ImGui::Text("%s", displayText_.c_str());

    // numeric buttons
    ImGui::BeginGroup();
    if (ImGui::Button("7", numButtonSize_))
        std::cout << "Clicked 7" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("8", numButtonSize_))
        std::cout << "Clicked 8" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("9", numButtonSize_))
        std::cout << "Clicked 9" << std::endl;

    if (ImGui::Button("4", numButtonSize_))
        std::cout << "Clicked 4" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("5", numButtonSize_))
        std::cout << "Clicked 5" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("6", numButtonSize_))
        std::cout << "Clicked 6" << std::endl;

    if (ImGui::Button("1", numButtonSize_))
        std::cout << "Clicked 1" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("2", numButtonSize_))
        std::cout << "Clicked 2" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("3", numButtonSize_))
        std::cout << "Clicked 3" << std::endl;

    if (ImGui::Button("C", numButtonSize_))
        std::cout << "Clicked C" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button("0", numButtonSize_))
        std::cout << "Clicked 0" << std::endl;
    ImGui::SameLine();
    if (ImGui::Button(".", numButtonSize_))
        std::cout << "Clicked ." << std::endl;
    ImGui::EndGroup();

    ImGui::SameLine();

    // operational buttons
    ImGui::BeginGroup();
    if (ImGui::Button("/", optButtonSize_))
        std::cout << "Clicked /" << std::endl;
    if (ImGui::Button("*", optButtonSize_))
        std::cout << "Clicked *" << std::endl;
    if (ImGui::Button("-", optButtonSize_))
        std::cout << "Clicked -" << std::endl;
    if (ImGui::Button("+", optButtonSize_))
        std::cout << "Clicked +" << std::endl;
    if (ImGui::Button("=", optButtonSize_))
        std::cout << "Clicked =" << std::endl;
    ImGui::EndGroup();

    ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
    ImGui::End();
}
