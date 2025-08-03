#pragma once

#include "imgui.h"

#include <string>

class CalcUI {
public:
    void Prepare(ImGuiIO &io);

private:
    void AddToDisplayText(const char c);
    void PopFromDisplayText();
    bool HasDisplayTextDot();

    const std::string id_ = "CalcUI";
    const ImVec2 numButtonSize_ = ImVec2(32.0f, 32.0f);
    const ImVec2 optButtonSize_ = ImVec2(25.0f, 25.0f);
    const ImVec2 pos_ = ImVec2(0.0f, 0.0f);
    const ImGuiWindowFlags flags_ = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    std::string displayText_ = "0";
};
