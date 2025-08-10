#include "CalcEngine.h"
#include "Auxiliary.h"

#include <stdexcept>
#include <iostream>

namespace ce {
CalcEngine::CalcEngine() {
    aux::LuaOpenLibs();
}

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

    float CustomFunction1(float x, float y) {
        if (aux::IsFileModified("scripts/CustomFunc1.lua", 1))
            aux::LuaDoFile("scripts/CustomFunc1.lua");

        aux::LuaCallFunction("CustomFunction1", x, y);

        float result = static_cast<float>(aux::LuaGetNumberFromTop());
        aux::LuaPopOneFromTop();

        return result;
    }

    float CustomFunction2(float x, float y) {
        if (aux::IsFileModified("scripts/CustomFunc2.lua", 2))
            aux::LuaDoFile("scripts/CustomFunc2.lua");

        aux::LuaCallFunction("CustomFunction2", x, y);

        float result = static_cast<float>(aux::LuaGetNumberFromTop());
        aux::LuaPopOneFromTop();

        return result;
    }

    float CustomFunction3(float x, float y) {
        if (aux::IsFileModified("scripts/CustomFunc3.lua", 3))
            aux::LuaDoFile("scripts/CustomFunc3.lua");

        aux::LuaCallFunction("CustomFunction3", x, y);

        float result = static_cast<float>(aux::LuaGetNumberFromTop());
        aux::LuaPopOneFromTop();

        return result;
    }

    float CustomFunction4(float x, float y) {
        if (aux::IsFileModified("scripts/CustomFunc4.lua", 4))
            aux::LuaDoFile("scripts/CustomFunc4.lua");

        aux::LuaCallFunction("CustomFunction4", x, y);

        float result = static_cast<float>(aux::LuaGetNumberFromTop());
        aux::LuaPopOneFromTop();

        return result;
    }
}
}
