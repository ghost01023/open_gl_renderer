#include "window.h"
#include <glad/gl.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

unsigned int createArrayBufferObject(GLfloat vertices[], int length, GLenum drawType);

void checkOpenGLError(const char *location);
void processInput(GLFWwindow *window);

int main()
{
	// INITIATE GLFW, GLAD AND SET UP CONTEXT WINDOW FOR RENDERING
	GLFWwindow *window = windowInit("Learning OpenGL");

	int success;
	// LOAD VERTEX AND FRAGMENT SHADER FILE

	char vertexShaderSource[1000];
	success = loadShader("vertex.vert", vertexShaderSource);
	if (!success)
	{
		return EXIT_FAILURE;
	}
	char fragmentShaderSource[1000];
	success = loadShader("fragment.frag", fragmentShaderSource);
	if (!success)
	{
		return EXIT_FAILURE;
	}

	// MAINLY FUNCTIONS AS AN ERROR LOG
	char infoLog[1024];
	unsigned int vertexShader = createVertexShader(vertexShaderSource, infoLog);
	if (!vertexShader)
	{
		return EXIT_FAILURE;
	}
	unsigned int fragmentShader = createFragmentShader(fragmentShaderSource, infoLog);
	if (!fragmentShader)
	{
		return EXIT_FAILURE;
	}
	unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader, infoLog);
	if (!shaderProgram)
	{
		return EXIT_FAILURE;
	}

	char fragmentShaderYellowSource[1000];
	success = loadShader("fragment_yellow.frag", fragmentShaderYellowSource);
	if (!success)
	{
		return EXIT_FAILURE;
	}
	unsigned int fragmentShaderYellow = createFragmentShader(fragmentShaderYellowSource, infoLog);
	unsigned int shaderProgramYellow = createShaderProgram(vertexShader, fragmentShaderYellow, infoLog);
	checkOpenGLError("After createShaderProgram for yellowFragmentShader");
	if (!shaderProgramYellow)
	{
		return EXIT_FAILURE;
	}

	// FREE MEMORY AFTER SHADER SOURCE USE
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);

	// TRIANGLES TO BE RENDERED
	float triangle_1_vertices[] = {
		-0.3f, 0.5f, 1.0f, -0.3f, 0.5f, 1.0f,
		0.3f, 0.5f, 1.0f, -0.3f, 0.5f, 1.0f,
		-0.3f, -0.5f, 1.0f, -0.3f, 0.5f, 1.0f};

	float triangle_2_vertices[] = {
		0.3f, 0.5f, 1.0f, 0.3f, 0.5f, 1.0f,
		-0.3f, -0.5f, 1.0f, 0.3f, 0.5f, 1.0f,
		0.3f, -0.5f, 1.0f, 0.3f, 0.5f, 1.0f};

	// ARRAY BUFFERS IN GPU
	glBindVertexArray(VAO[0]);
	unsigned int VBO1 = createArrayBufferObject(triangle_1_vertices, 18, GL_STATIC_DRAW);
	glBindVertexArray(VAO[1]);
	unsigned int VBO2 = createArrayBufferObject(triangle_2_vertices, 18, GL_STATIC_DRAW);
	std::cout << VBO1 << " -> " << sizeof(triangle_1_vertices) << std::endl;
	std::cout << VBO2 << " -> " << sizeof(triangle_2_vertices) << std::endl;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_LINE_SMOOTH);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glPointSize(7.0);
		// glLineWidth(4.5)
		glBindVertexArray(VAO[0]);
		glUseProgram(shaderProgram);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramYellow);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		processInput(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		std::cout << "Detected key press of value 0" << std::endl;
	}
}

unsigned int createArrayBufferObject(GLfloat vertices[], int length, GLenum drawType)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), vertices, drawType);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0); // ATTRIB POINTER FOR LOCATION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return VBO;
};

void checkOpenGLError(const char *location)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "Error encountered at " << location << ": " << error << std::endl;
	}
}

//