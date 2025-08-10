cmake_minimum_required(VERSION 3.22)

set(SCRIPTS_DIR ${CMAKE_CURRENT_LIST_DIR}/scripts)
set(TARGET_SCRIPTS_DIR ${CMAKE_BINARY_DIR}/)

project(
    imcalc
    DESCRIPTION "Simple, customizable calculator"
    LANGUAGES CXX
    VERSION 0.1
)

enable_language(CXX)
enable_language(C)

# find installed SDL3 library
find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE src/main.cpp
    PRIVATE src/Application.cpp
    PRIVATE src/CalcUI.cpp
    PRIVATE src/CalcEngine.cpp
    PRIVATE src/Auxiliary.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include
)

# include found SDL3 library
target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
    PRIVATE imgui
    PRIVATE lua
)

# include embedded libraries
add_subdirectory(external)

file(COPY ${SCRIPTS_DIR} DESTINATION ${TARGET_SCRIPTS_DIR})
