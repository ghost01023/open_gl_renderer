#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

unsigned int createVertexShader(const char *vertexShaderSource, char infoLog[])
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR::COMPILE::VERTEX_SHADER" << std::endl;
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << infoLog << std::endl;
        return 0;
    }
    else
    {
        std::cout << "VETEX_SHADER COMPILED SUCCESSFULLY!" << std::endl;
    }
    return vertexShader;
}

unsigned int createFragmentShader(const char *shaderSource, char infoLog[])
{
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderSource, NULL);
    glCompileShader(fragmentShader);
    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR::COMPILE::FRAGMENT_SHADER" << std::endl;
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << infoLog << std::endl;
        return 0;
    }
    else
    {
        std::cout << "FRAGMENT_SHADER COMPILED SUCCESSFULLY!" << std::endl;
    }
    return fragmentShader;
}

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, char infoLog[])
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::cout << "SHADER_PROGRAM LINKING FAILED!" << std::endl;
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << infoLog << std::endl;
        return 0;
    }
    else
    {
        std::cout << "SHADER PROGRAM WAS LINKED SUCCESSFULLY!" << std::endl;
    }
    return shaderProgram;
}

int loadShader(const char *fileName, char destination[])
{
    char fileRelativePath[25];
    destination[0] = '\0';
    fileRelativePath[0] = '\0';
    strcat(fileRelativePath, "../shaders/");
    strcat(fileRelativePath, fileName);
    char shaderSourceBuffer[10];
    FILE *fptr = fopen(fileRelativePath, "r");
    if (fptr == NULL)
    {
        std::cout << "Failed to open shader file: " << fileName << std::endl;
        return 0;
    }
    while (fgets(shaderSourceBuffer, 10, fptr))
    {
        strcat(destination, shaderSourceBuffer);
    }
    // std::cout << destination << std::endl;
    return 1;
}