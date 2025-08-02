cmake_minimum_required(VERSION 3.22)

project(
    imcalc
    DESCRIPTION "Simple, customizable calculator"
    LANGUAGES CXX
)

# find installed SDL3 library
find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE src/main.cpp
    PRIVATE src/Application.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include
)

# include found SDL3 library
target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
)

# include embedded libraries
add_subdirectory(external)
