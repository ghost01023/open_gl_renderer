#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *windowInit(const char *windowTitle);
void glfwFrameBufferSizeCallback(GLFWwindow *window, int width, int height);

#endif // WINDOW_H