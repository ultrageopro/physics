cmake_minimum_required(VERSION 3.22)

project(physics LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(pybind11)

add_library(physics
    src/physics/formulas/mech.cpp
    src/physics/object/object.cpp
    src/physics/formulas/gravity.cpp
)

target_include_directories(physics PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()
add_subdirectory(tests)
add_subdirectory(bindings)