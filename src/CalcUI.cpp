#include "CalcUI.h"

#include <iostream>

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

void CalcUI::SetOperation(Operation op) {
    currOp_ = std::make_unique<Operation>(op);
}

void CalcUI::ProcessOperation() {
    if (currOp_ == nullptr)
        return;

    float tmp;

    try {
        tmp = std::stof(displayText_);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Error: Invalid argument while processing an operation." << std::endl;
        return;
    }
    catch (const std::out_of_range &e) {
        std::cerr << "Error: Given argument exceeded range of the data type." << std::endl;
        return;
    }

    if (!result_.has_value()) {
        result_ = tmp;
    }
    else {
        result_ = (*currOp_)(result_.value(), tmp);
        displayText_ = std::to_string(result_.value());
    }

    shouldClear_ = true;
}

float AddFloats(float x, float y) {
    return x + y;
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

    if (ImGui::Button("C", numButtonSize_))
        PopFromDisplayText();
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
        std::cout << "Clicked /" << std::endl;
    if (ImGui::Button("*", optButtonSize_))
        std::cout << "Clicked *" << std::endl;
    if (ImGui::Button("-", optButtonSize_))
        std::cout << "Clicked -" << std::endl;
    if (ImGui::Button("+", optButtonSize_)) {
        std::cout << "Clicked +" << std::endl;
        SetOperation(AddFloats);
        ProcessOperation();
    }
    if (ImGui::Button("=", optButtonSize_)) {
        std::cout << "Clicked =" << std::endl;
        ProcessOperation();
        result_.reset();
        currOp_.reset();
    }
    ImGui::EndGroup();

    ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
    ImGui::End();
}
