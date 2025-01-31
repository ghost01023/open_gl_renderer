#include "window.h"
#include "shader.h"

#include <glad/glad.h>
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
	loadShader("fragment_2.frag", fragmentShaderYellowSource);
	unsigned int fragmentShaderYellow = createFragmentShader(fragmentShaderYellowSource, infoLog);
	// std::cout << fragmentShaderYellowSource << std::endl;
	unsigned int shaderProgramYellow = createShaderProgram(vertexShader, fragmentShaderYellow, infoLog);
	checkOpenGLError("After createShaderProgram for yellowFragmentShader");
	// std::cout << shaderProgram << " " << shaderProgramYellow << std::endl;
	if (!shaderProgramYellow)
	{
		return EXIT_FAILURE;
	}

	// FREE MEMORY AFTER SHADER SOURCE USE
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TRIANGLES TO BE RENDERED
	float triangle_1_vertices[] = {
		-0.3f, 0.5f, 1.0f,
		0.3f, 0.5f, 1.0f,
		-0.3f, -0.5f, 1.0f};

	// ELEMENT ARRAY BUFFER DATA
	//  unsigned int elements[] = {
	//  	0, 1, 2, 1, 2, 3};

	float triangle_2_vertices[] = {
		0.3f, 0.5f, 1.0f,
		-0.3f, -0.5f, 1.0f,
		0.3f, -0.5f, 1.0f};
	// ARRAY BUFFERS IN GPU
	unsigned int VBO1 = createArrayBufferObject(triangle_1_vertices, 9, GL_STATIC_DRAW);
	unsigned int VBO2 = createArrayBufferObject(triangle_2_vertices, 9, GL_STATIC_DRAW);
	std::cout << VBO1 << " -> " << sizeof(triangle_1_vertices) << std::endl;
	std::cout << VBO2 << " -> " << sizeof(triangle_2_vertices) << std::endl;
	// createArrayBufferObject(triangle_2_vertices, 9, GL_STATIC_DRAW);

	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	while (!glfwWindowShouldClose(window))
	{
		// float time = glfwGetTime(); // RENDER DYNAMICALLY COLORED TRIANGLE
		// checkOpenGLError("Something during the render loop");
		// GLuint timeUniformLocation = glGetUniformLocation(shaderProgram, "u_time");
		// glUniform1f(timeUniformLocation, time);
		glClearColor(0.1, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramYellow);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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