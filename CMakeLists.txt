cmake_minimum_required(VERSION 3.22)

project(physics LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(pybind11)

option(PHYSICS_BUILD_TESTS "Build C++ tests" ON)
option(PHYSICS_GENERATE_STUBS "Generate Python stubs for bindings" OFF)

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

install(DIRECTORY python/
        DESTINATION .
)

add_subdirectory(bindings)

# Тесты
if(PHYSICS_BUILD_TESTS)
    enable_testing()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()