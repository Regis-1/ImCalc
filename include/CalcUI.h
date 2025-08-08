#pragma once

#include "imgui.h"
#include "CalcEngine.h"

#include <string>

class CalcUI {
public:
    void Prepare(ImGuiIO &io);

private:
    void AddToDisplayText(const char c);
    void PopFromDisplayText();
    bool HasDisplayTextDot();
    void HandleOperation(ce::Operation op);

    ce::CalcEngine calcEngine_;

    const ImVec2 numButtonSize_ = ImVec2(32.0f, 32.0f);
    const ImVec2 optButtonSize_ = ImVec2(25.0f, 25.0f);
    const ImVec2 pos_ = ImVec2(0.0f, 0.0f);
    const ImGuiWindowFlags flags_ = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    const std::string id_ = "CalcUI";
    std::string displayText_ = "0";
    const float holdThreshold_ = 0.3f;
    float holdDuration_ = 0.0f;
    bool isHolding_ = false;
    bool shouldClear_ = false;
};
