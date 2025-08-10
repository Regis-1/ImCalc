#include "CalcUI.h"

void CalcUI::AddToDisplayText(const char c) {
    if (shouldClear_) {
        displayText_ = "0";
        shouldClear_ = false;
    }

    if (displayText_ == "0" && c != '.')
        displayText_.pop_back();

    displayText_.push_back(c);
}

void CalcUI::PopFromDisplayText() {
    displayText_.pop_back();

    if (displayText_.size() == 0)
        displayText_ = "0";
}

bool CalcUI::HasDisplayTextDot() {
    return displayText_.find('.') != std::string::npos;
}

void CalcUI::HandleOperation(ce::Operation op) {
    calcEngine_.Process(displayText_);
    calcEngine_.SetOperation(op);
    shouldClear_ = true;
}

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
        AddToDisplayText('7');
    ImGui::SameLine();
    if (ImGui::Button("8", numButtonSize_))
        AddToDisplayText('8');
    ImGui::SameLine();
    if (ImGui::Button("9", numButtonSize_))
        AddToDisplayText('9');

    if (ImGui::Button("4", numButtonSize_))
        AddToDisplayText('4');
    ImGui::SameLine();
    if (ImGui::Button("5", numButtonSize_))
        AddToDisplayText('5');
    ImGui::SameLine();
    if (ImGui::Button("6", numButtonSize_))
        AddToDisplayText('6');

    if (ImGui::Button("1", numButtonSize_))
        AddToDisplayText('1');
    ImGui::SameLine();
    if (ImGui::Button("2", numButtonSize_))
        AddToDisplayText('2');
    ImGui::SameLine();
    if (ImGui::Button("3", numButtonSize_))
        AddToDisplayText('3');

    ImGui::Button("C", numButtonSize_);
    if (ImGui::IsItemActive()) {
        holdDuration_ += ImGui::GetIO().DeltaTime;
        if (holdDuration_ >= holdThreshold_ && !isHolding_)
            isHolding_ = true;
    }
    else {
        if (ImGui::IsItemDeactivated() && !isHolding_)
            PopFromDisplayText();
        else if(ImGui::IsItemDeactivated() && isHolding_)
            displayText_ = "0";

        isHolding_ = false;
        holdDuration_ = 0.0f;
    }

    ImGui::SameLine();
    if (ImGui::Button("0", numButtonSize_))
        AddToDisplayText('0');
    ImGui::SameLine();
    if (ImGui::Button(".", numButtonSize_)){
        if (!HasDisplayTextDot())
            AddToDisplayText('.');
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    // operational buttons
    ImGui::BeginGroup();
    if (ImGui::Button("/", optButtonSize_))
        HandleOperation(ce::operations::DivFloats);
    if (ImGui::Button("*", optButtonSize_))
        HandleOperation(ce::operations::MulFloats);
    if (ImGui::Button("-", optButtonSize_))
        HandleOperation(ce::operations::SubFloats);
    if (ImGui::Button("+", optButtonSize_))
        HandleOperation(ce::operations::AddFloats);
    if (ImGui::Button("=", optButtonSize_)) {
        calcEngine_.Process(displayText_);
        calcEngine_.Reset();
        shouldClear_ = true;
    }
    ImGui::EndGroup();

    ImGui::Separator();

    ImGui::BeginGroup();
    if (ImGui::Button("Cf1", cfsButtonSize_))
        HandleOperation(ce::operations::CustomFunction1);
    ImGui::SameLine();
    if (ImGui::Button("Cf2", cfsButtonSize_))
        HandleOperation(ce::operations::CustomFunction2);
    ImGui::SameLine();
    if (ImGui::Button("Cf3", cfsButtonSize_))
        HandleOperation(ce::operations::CustomFunction3);
    ImGui::SameLine();
    if (ImGui::Button("Cf4", cfsButtonSize_))
        HandleOperation(ce::operations::CustomFunction4);
    ImGui::EndGroup();

    ImGui::End();
}
