#ifndef SHADER_H
#define SHADER_H
unsigned int createVertexShader(const char *shaderSource, char infoLog[]);
unsigned int createFragmentShader(const char *shaderSource, char infoLog[]);
unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, char infoLog[]);
int loadShader(const char *fileName, char destination[]);
#endif // SHADER_H