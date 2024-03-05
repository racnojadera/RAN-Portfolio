#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
GLuint CreateShaderFromFile(const GLuint& shaderType, const std::string& shaderFilePath);
GLuint CreateShaderFromSource(const GLuint& shaderType, const std::string& shaderSource);

void FramebufferSizeChangedCallback(GLFWwindow* window, int width, int height);

struct Vertex
{
	GLfloat x, y, z;
	GLubyte r, g, b;
	GLfloat nx, ny, nz;
};


int main()
{
	int glfwInitStatus = glfwInit();
	if (glfwInitStatus == GLFW_FALSE);
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float windowWidth = 800;
	float windowHeight = 800;
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GDEV 32 Laboratory Exercise 3", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeChangedCallback);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
	}
	// --- Vertex specification ---
	Vertex vertices[42];

	//Front
	vertices[0] = { -0.5f, -0.5f, 0.5f,			255, 255, 255,		-1.0f, -1.0f, 1.0f };   // Lower-left
	vertices[1] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };    // Lower-right
	vertices[2] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[3] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[4] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[5] = { -0.5f, -0.5f, 0.5f,			255, 255, 255,		-1.0f, -1.0f, 1.0f };   // Lower-left

	//Right
	vertices[6] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };    // Lower-left
	vertices[7] = { 0.5f, -0.5f, -0.5f,			255, 255, 255,		1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[8] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[9] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[10] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };		// Upper-left
	vertices[11] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };	// Lower-left

	//Back
	vertices[12] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[13] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, -1.0f, -1.0f };	// Lower-right
	vertices[14] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[15] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[16] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[17] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left

	//Left
	vertices[18] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[19] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		-1.0f, -1.0f, 1.0f };	// Lower-right
	vertices[20] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };    // Upper-right
	vertices[21] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };	// Upper-right
	vertices[22] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[23] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left

	//Up
	vertices[24] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[25] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };		// Upper-right
	vertices[26] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[27] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[28] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[29] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };	// Upper-left

	// Bottom
	vertices[30] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[31] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[32] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };    // Lower-right
	vertices[33] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };	 // Lower-right
	vertices[34] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		-1.0f, -1.0f, 1.0f };	 // Lower-left
	vertices[35] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };   // Lower-left

	//Floor
	vertices[36] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[37] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };		// Upper-right
	vertices[38] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[39] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[40] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[41] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };	// Upper-left

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertex attribute 0 - Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

	// Vertex attribute 1 - Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, r)));
	
	// Vertex attribute 2 - Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, nx)));

	glBindVertexArray(0);

	GLuint program = CreateShaderProgram("main.vsh", "main.fsh");

	//(comment)(depthmapshader)(line262)
	
	glViewport(0, 0, windowWidth, windowHeight);
	//(comment)(everythinghere)(lines275-525)
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vao);


	}

	// --- Cleanup ---
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return 0;
}

GLuint CreateShaderFromFile(const GLuint& shaderType, const std::string& shaderFilePath)
{
	std::ifstream shaderFile(shaderFilePath);
	if (shaderFile.fail())
	{
		std::cerr << "Unable to open shader file: " << shaderFilePath << std::endl;
		return 0;
	}

	std::string shaderSource;
	std::string temp;
	while (std::getline(shaderFile, temp))
	{
		shaderSource += temp + "\n";
	}
	shaderFile.close();
	return CreateShaderFromSource(shaderType, shaderSource);
}

GLuint CreateShaderFromSource(const GLuint& shaderType, const std::string& shaderSource)
{
	GLuint shader = glCreateShader(shaderType);

	const char* shaderSourceCStr = shaderSource.c_str();
	GLint shaderSourceLen = static_cast<GLint>(shaderSource.length());
	glShaderSource(shader, 1, &shaderSourceCStr, &shaderSourceLen);
	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, infoLog);
		std::cerr << "shader compilation error: " << infoLog << std::endl;
	}
	return shader;
}

void FramebufferSizeChangedCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}