#pragma once

#include <string>
#include <memory>
#include <optional>
#include <functional>

namespace ce {
using Operation = std::function<float(float, float)>;
using OperationPtr = std::unique_ptr<Operation>;

class CalcEngine {
public:
    CalcEngine();

    void SetOperation(Operation op); 
    void Process(std::string &display);
    void Reset();

private:
    std::optional<float> result_ = {};
    OperationPtr currOp_;
};

namespace operations {
    float AddFloats(float x, float y);
    float SubFloats(float x, float y);
    float MulFloats(float x, float y);
    float DivFloats(float x, float y);
    float CustomFunction1(float x, float y);
    float CustomFunction2(float x, float y);
    float CustomFunction3(float x, float y);
    float CustomFunction4(float x, float y);
}
}
