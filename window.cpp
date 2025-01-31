#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glfwFrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *windowInit(const char *windowTitle)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
    OPEN WINDOW IN FULL-SCREEN
    */
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    GLFWwindow *window = glfwCreateWindow(videoMode->width, videoMode->height, windowTitle, primaryMonitor, NULL);

    if (!window)
    {
        std::cout << "FAILED TO CREATE GLFWwindow" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
        return NULL;
    }
    glViewport(0, 0, videoMode->width, videoMode->height);
    glfwSetFramebufferSizeCallback(window, glfwFrameBufferSizeCallback);
    return window;
}