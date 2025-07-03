cmake_minimum_required(VERSION 3.10)

# Project name and settings
project(OpenGLProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add warning and error flags to the compiler
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
endif()

find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)
add_subdirectory(external/glad)


# Include directories for glad and glfw
# include_directories("C:/msys64/mingw64/include")

# Add the glad implementation file to the project
# add_library(glad STATIC "C:/msys64/mingw64/lib/glad/glad.c")

# Add the executable target
add_executable(OpenGLApp src/main.cpp src/shader.cpp src/window.cpp)

# Link the libraries
target_link_libraries(OpenGLApp glad glfw3 GL dl)
