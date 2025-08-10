#pragma once

#include "lua.hpp"
#include <string>

namespace aux {
bool IsFileModified(const std::string &filePath, const unsigned int fileIdx);
void LuaOpenLibs();
void LuaDoFile(const std::string &filePath);
void LuaCallFunction(const std::string &funcName, float &x, float &y);
lua_Number LuaGetNumberFromTop();
void LuaPopOneFromTop();
}
