#include "CalcEngine.h"

#include <stdexcept>
#include <iostream>

namespace ce {
void CalcEngine::Reset() {
    result_.reset();
    currOp_.reset();
}

void CalcEngine::SetOperation(Operation op) {
    currOp_ = std::make_unique<Operation>(op);
}

void CalcEngine::Process(std::string &display) {
    float tmp;

    try {
        tmp = std::stof(display);
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
        display = std::to_string(result_.value());
    }
}

namespace operations {
    float AddFloats(float x, float y) {
        return x + y;
    }

    float SubFloats(float x, float y) {
        return x - y;
    }

    float MulFloats(float x, float y) {
        return x * y;
    }

    float DivFloats(float x, float y) {
        return x / y;
    }
}
}
