
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main() {\n"
								 "gl_Position = vec4(aPos, 1.0f);\n"
								 "}";

const char *fragmentShaderSource = "#version 330 core\n"
								   "out vec4 FragColor;\n"
								   "uniform float time;\n"
								   "void main() {\n"
								   "float intensity = sin(time);\n"
								   "FragColor = vec4(0.9f, 0.8f, 0.9f, 1.0f);\n"
								   "}";

void glfwFrameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

	// INITIATE GLFW, GLAD AND SET UP CONTEXT WINDOW FOR RENDERING
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*
	OPEN WINDOW IN FULL-SCREEN
	*/
	GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
	GLFWwindow *window = glfwCreateWindow(video_mode->width, video_mode->height, "Learning OpenGL", primary_monitor, NULL);

	if (!window)
	{
		std::cout << "FAILED TO CREATE GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 700);
	glfwSetFramebufferSizeCallback(window, glfwFrameBufferSizeCallback);

	////////////////////////////////////////////////
	////////////////////////////////////////////////
	////////////////////////////////////////////////

	// DEFINE AND RENDER FIRST TRIANGLE
	float triangle_1_vertices[] = {
		-0.7f, 0.9f, 1.0f,
		0.9f, 0.9f, 1.0f,
		0.0f, -0.9f, 1.0f};

	float triangle_2_vertices[] = {
		-0.9f, 0.5f, 0.0f,
		-0.6f, 0.5f, 0.0f, // FIRST TRIANGLE
		-0.75f, 0.0f, 0.0f};

	// ERROR AND INFO LOGS
	int success;
	char infoLog[1024];
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR::COMPILE::VERTEX_SHADER" << std::endl;
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	else
	{
		std::cout << "VETEX_SHADER COMPILED SUCCESSFULLY!" << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR::COMPILE::FRAGMENT_SHADER" << std::endl;
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	else
	{
		std::cout << "FRAGMENT_SHADER COMPILED SUCCESSFULLY!" << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cout << "SHADER PROGRAM LINKING FAILED!" << std::endl;
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	else
	{
		std::cout << "SHADER PROGRAM WAS LINKED SUCCESSFULLY!" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ARRAY BUFFERS IN GPU
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle_1_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle_2_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		processInput(window);
		glfwPollEvents();
	}

	return 0;
}

void glfwFrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, 800, 700);
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
