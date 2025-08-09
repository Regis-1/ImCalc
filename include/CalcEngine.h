#pragma once

/*
 * Idea for scripting...
 *
 * function CustomF1(x, y)
 *  local tmp = 0;
 *  for y:
 *   tmp = tmp + x
 * end
 *
 * function CustomF2(x, y)
 *  MulFloats(x, DivFloats(y, 100))
 * end
 */

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
}
}
