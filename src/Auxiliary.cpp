#include "Auxiliary.h"
#include <filesystem>
#include <iostream>
#include <chrono>
#include <functional>

std::unique_ptr<lua_State, void(*)(lua_State*)> L(luaL_newstate(), [](lua_State* L) { lua_close(L); });

time_t lastCheckTimes[4];

namespace aux {
bool IsFileModified(const std::string &filePath, const unsigned int fileIdx) {
    try {
        std::filesystem::path file(filePath);
        if (!std::filesystem::exists(file)) {
            std::cerr << "File does not exist!" << std::endl;
            return false;
        }

        auto fileTime = std::filesystem::last_write_time(file);

        auto lastWriteTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            fileTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
        );

        if (lastWriteTime > std::chrono::system_clock::from_time_t(lastCheckTimes[fileIdx-1])) {
            lastCheckTimes[fileIdx-1] = std::chrono::system_clock::to_time_t(lastWriteTime);
            return true;
        }

    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }

    return false;
}

void LuaOpenLibs() {
    luaL_openlibs(L.get());
}

void LuaDoFile(const std::string &filePath) {
    if (luaL_dofile(L.get(), filePath.c_str()) != LUA_OK) {
        std::cerr << "Error: Execution of lua code: " << lua_tostring(L.get(), -1) << std::endl;
    }
}

void LuaCallFunction(const std::string &funcName, float &x, float &y) {
    lua_getglobal(L.get(), funcName.c_str());
    if (!lua_isfunction(L.get(), -1)) {
        std::cerr << "Error: " << funcName << " is not a valid function." << std::endl;
        return;
    }

    lua_pushnumber(L.get(), x);
    lua_pushnumber(L.get(), y);

    if (lua_pcall(L.get(), 2, 1, 0) != LUA_OK) {
        std::cerr << "Error while calling " << funcName << ": " << lua_tostring(L.get(), -1) << std::endl;
        return;
    }
}

lua_Number LuaGetNumberFromTop() {
    return lua_tonumber(L.get(), -1);
}

void LuaPopOneFromTop() {
    lua_pop(L.get(), 1);
}
}
