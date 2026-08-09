cmake_minimum_required(VERSION 3.14)
project(RectRaycaster CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Build target
add_executable(RectRaycaster ${SOURCES})

# GCC Optimizations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(RectRaycaster PRIVATE -Ofast -mavx2)
endif()

# Raylib Dependency
find_package(raylib 4.0 REQUIRED)
target_link_libraries(RectRaycaster PRIVATE raylib)
