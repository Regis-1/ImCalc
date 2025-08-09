# imgui library
set(IMGUI_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui)
add_library(imgui)
target_include_directories(
    imgui
    PUBLIC ${IMGUI_LIB_DIR}
)

target_sources(
    imgui
    PRIVATE ${IMGUI_LIB_DIR}/imgui.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_demo.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_draw.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_tables.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_widgets.cpp
    PRIVATE ${IMGUI_LIB_DIR}/backends/imgui_impl_sdl3.cpp
    PRIVATE ${IMGUI_LIB_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

# lua library
set(LUA_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/lua)
add_library(lua)
set_target_properties(lua PROPERTIES LINKER_LANGUAGE C)
target_include_directories(
    lua
    PUBLIC ${LUA_LIB_DIR}/src
)

target_sources(
    lua
    PRIVATE ${LUA_LIB_DIR}/src/lapi.c
    PRIVATE ${LUA_LIB_DIR}/src/lcode.c
    PRIVATE ${LUA_LIB_DIR}/src/lctype.c
    PRIVATE ${LUA_LIB_DIR}/src/ldebug.c
    PRIVATE ${LUA_LIB_DIR}/src/ldo.c
    PRIVATE ${LUA_LIB_DIR}/src/ldump.c
    PRIVATE ${LUA_LIB_DIR}/src/lfunc.c
    PRIVATE ${LUA_LIB_DIR}/src/lgc.c
    PRIVATE ${LUA_LIB_DIR}/src/llex.c
    PRIVATE ${LUA_LIB_DIR}/src/lmem.c
    PRIVATE ${LUA_LIB_DIR}/src/lobject.c
    PRIVATE ${LUA_LIB_DIR}/src/lopcodes.c
    PRIVATE ${LUA_LIB_DIR}/src/lparser.c
    PRIVATE ${LUA_LIB_DIR}/src/lstate.c
    PRIVATE ${LUA_LIB_DIR}/src/lstring.c
    PRIVATE ${LUA_LIB_DIR}/src/ltable.c
    PRIVATE ${LUA_LIB_DIR}/src/ltm.c
    PRIVATE ${LUA_LIB_DIR}/src/lundump.c
    PRIVATE ${LUA_LIB_DIR}/src/lvm.c
    PRIVATE ${LUA_LIB_DIR}/src/lzio.c
    PRIVATE ${LUA_LIB_DIR}/src/lauxlib.c
    PRIVATE ${LUA_LIB_DIR}/src/lbaselib.c
    PRIVATE ${LUA_LIB_DIR}/src/lcorolib.c
    PRIVATE ${LUA_LIB_DIR}/src/ldblib.c
    PRIVATE ${LUA_LIB_DIR}/src/liolib.c
    PRIVATE ${LUA_LIB_DIR}/src/lmathlib.c
    PRIVATE ${LUA_LIB_DIR}/src/loadlib.c
    PRIVATE ${LUA_LIB_DIR}/src/loslib.c
    PRIVATE ${LUA_LIB_DIR}/src/lstrlib.c
    PRIVATE ${LUA_LIB_DIR}/src/ltablib.c
    PRIVATE ${LUA_LIB_DIR}/src/lutf8lib.c
    PRIVATE ${LUA_LIB_DIR}/src/linit.c
)
