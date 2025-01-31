#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

unsigned int createVertexShader(const char *shaderSource, char infoLog[]);
unsigned int createFragmentShader(const char *shaderSource, char infoLog[]);
unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, char infoLog[]);
unsigned int createArrayBufferObject(GLfloat vetrtices[], int length, GLenum drawType);
int loadShader(const char *fileName, char destination[]);
void checkOpenGLError(const char *location);
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
	glViewport(0, 0, video_mode->width, video_mode->height);
	glfwSetFramebufferSizeCallback(window, glfwFrameBufferSizeCallback);

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

	// TRIANGLES TO BE RENDERED
	float triangle_1_vertices[] = {
		0.0f, 0.5f, 1.0f,
		-0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f};

	float triangle_2_vertices[] = {
		-0.9f, 0.5f, 0.0f,
		-0.1f, 0.5f, 0.0f,
		-0.75f, 0.0f, 0.0f};

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

	// FREE MEMORY AFTER SHADER SOURCE USE
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// ARRAY BUFFERS IN GPU
	unsigned int VBO = createArrayBufferObject(triangle_1_vertices, 9, GL_STATIC_DRAW);
	createArrayBufferObject(triangle_2_vertices, 9, GL_STATIC_DRAW);
	// std::cout << VBO << " & " << VBO2 << std::endl;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime(); // RENDER DYNAMICALLY COLORED TRIANGLE
		GLuint timeUniformLocation = glGetUniformLocation(shaderProgram, "u_time");
		glUniform1f(timeUniformLocation, time);
		glClearColor(0.1, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		processInput(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	return 0;
}

void glfwFrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
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

unsigned int createArrayBufferObject(GLfloat vertices[], int length, GLenum drawType)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), vertices, drawType);
	checkOpenGLError("During create arrayBufferObject");
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
	return 1;
}