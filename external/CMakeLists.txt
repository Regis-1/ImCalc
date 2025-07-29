# imgui library
set(IMGUI_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${IMGUI_LIB_DIR}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE ${IMGUI_LIB_DIR}/imgui.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_demo.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_draw.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_tables.cpp
    PRIVATE ${IMGUI_LIB_DIR}/imgui_widgets.cpp
    PRIVATE ${IMGUI_LIB_DIR}/backends/imgui_impl_sdl3.cpp
    PRIVATE ${IMGUI_LIB_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
