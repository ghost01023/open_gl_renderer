cmake_minimum_required(VERSION 3.10)

# Project name and settings
project(OpenGLProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for glad and glfw
include_directories("C:/msys64/mingw64/include")

# Add the glad implementation file to the project
add_library(glad STATIC "C:/msys64/mingw64/lib/glad/glad.c")

# Add the executable target
add_executable(OpenGLApp main.cpp)

# Link the libraries
target_link_libraries(OpenGLApp glad glfw3 opengl32 gdi32)
