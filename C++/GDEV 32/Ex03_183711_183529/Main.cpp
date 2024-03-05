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

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraPosition = glm::vec3(0.0f, 1.5f, -3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = 400.0, lastY = 400.0;
float pitch = 0.0f;
float yaw = 90.0f;
bool mouseInit = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processKeyboardInput(GLFWwindow* window);

float runningTime = 0.0f;
double lastFrame = 0;

struct Vertex
{
	GLfloat x, y, z;	// Position
	GLubyte r, g, b;	// Color
	GLfloat nx, ny, nz; // Normal
};

int main()
{
	int glfwInitStatus = glfwInit();
	if (glfwInitStatus == GLFW_FALSE)
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
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "GDEV 32 Laboratory Exercise 3", nullptr, nullptr);
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
		return 1;
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
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
	vertices[25] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 1.0f };		// Lower-right
	vertices[26] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[27] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[28] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[29] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		-1.0f, 1.0f, 1.0f };	// Lower-left

	//Bottom
	vertices[30] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Upper-left
	vertices[31] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[32] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };    // Upper-right
	vertices[33] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, -1.0f, 1.0f };    // Upper-right
	vertices[34] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		-1.0f, -1.0f, 1.0f };   // Upper-left
	vertices[35] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		-1.0f, -1.0f, -1.0f };  // Lower-left

	//Floor
	vertices[36] = {-0.5f, 0.0f, 0.5f, 			208, 213, 247, 		-1.0f, 1.0f, 1.0f};     // Lower-left
	vertices[37] = {0.5f, 0.0f, 0.5f, 			208, 213, 247, 		1.0f, 1.0f, 1.0f};      // Lower-right
	vertices[38] = {0.5f, 0.0f, -0.5f, 			208, 213, 247, 		1.0f, 1.0f, -1.0f};     // Upper-right
	vertices[39] = {0.5f, 0.0f, -0.5f, 			208, 213, 247, 		1.0f, 1.0f, -1.0f};	    // Upper-right
	vertices[40] = {-0.5f, 0.0f, -0.5f, 		208, 213, 247, 		-1.0f, 1.0f, -1.0f};    // Upper-left
	vertices[41] = {-0.5f, 0.0f, 0.5f, 			208, 213, 247, 		-1.0f, 1.0f, 1.0f};	    // Lower-left
	// --- Vertex specification end ---

	// --- VBO VAO --- 
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertex attribute 0 - Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));

	// Vertex attribute 1 - Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));

	// Vertex attribute 2 - Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, nx)));

	glBindVertexArray(0);
	GLuint program = CreateShaderProgram("main.vsh", "main.fsh");

	GLuint depthVAO;
	glGenVertexArrays(1, &depthVAO);
	glBindVertexArray(depthVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glBindVertexArray(0);
	GLuint depthShader = CreateShaderProgram("depthmain.vsh", "depthmain.fsh");

	glViewport(0, 0, windowWidth, windowHeight);
	
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	float time = 0;

	GLuint depthFBO;
	glGenFramebuffers(1, &depthFBO);

	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error! Framebuffer not complete!" << std::endl;
	}



	while (!glfwWindowShouldClose(window))
	{
		processKeyboardInput(window);

		time = glfwGetTime();
		runningTime = float(time - lastFrame);

		float aspectRatio = windowWidth / windowHeight;
		glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		glm::mat4 perspectiveProjMatrix = glm::perspective(glm::radians(80.0f), aspectRatio, 0.1f, 100.0f);



		// --- FIRST PASS (SHADOW PASS) ---
		glUseProgram(depthShader);
		glBindVertexArray(depthVAO);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

		glm::mat4 dirLightProjMatrix = glm::ortho(-20.0f, 20.0f, -10.0f, 10.0f, -20.0f, 20.0f);
		glm::mat4 dirLightViewMatrix = glm::lookAt(glm::vec3(-0.1f, 3.0f, -0.1f), glm::vec3(0.6f, 0.0f, 0.6f),  glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSrcMatrix = dirLightProjMatrix * dirLightViewMatrix;
		
		GLint dirLightProjMatrixUniformLocation = glGetUniformLocation(depthShader, "dirLightProjMatrix");
		glUniformMatrix4fv(dirLightProjMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(dirLightProjMatrix));
		GLint dirLightViewMatrixUniformLocation = glGetUniformLocation(depthShader, "dirLightViewMatrix");
		glUniformMatrix4fv(dirLightViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(dirLightViewMatrix));
		
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
		glClear(GL_DEPTH_BUFFER_BIT); 
		
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 cube1 = glm::mat4(1.0f);
		glm::mat4 cube2 = glm::mat4(1.0f);
		glm::mat4 cube3 = glm::mat4(1.0f);



		cube1 = glm::translate(cube1, glm::vec3(-2.0f, 1.5f, 3.0f));
		cube1 = glm::rotate(cube1, glm::radians(25.0f*time), glm::vec3(0.0f, 1.0f, 0.0f));
		cube1 = glm::scale(cube1, glm::vec3(1.5f, 1.5f, 1.5f));

		cube2 = glm::translate(cube2, glm::vec3(0.0f, 0.5f*sin(time), 0.0f));
		cube2 = glm::translate(cube2, glm::vec3(2.0f, 1.5f, 3.0f));
		cube2 = glm::rotate(cube2, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		cube3 = glm::translate(cube3, glm::vec3(0.0f, 1.0f, -1.0f));
		cube3 = glm::scale(cube3, glm::vec3(0.5f, 0.5f, 0.5f));
		


		GLint depthModelMatrixUniformLocation = glGetUniformLocation(depthShader, "modelMatrix");
		glUniformMatrix4fv(depthModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube1));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniformMatrix4fv(depthModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniformMatrix4fv(depthModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube3));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		

		// --- SECOND PASS ---
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vao);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthTex);
		GLint depthTexUniformLocation = glGetUniformLocation(depthTex, "depth");
		glUniform1i(depthTexUniformLocation, 0);
		
		GLint lightSrcMatrixUniformLocation = glGetUniformLocation(program, "lightSrcMatrix");
		GLint modelMatrixUniformLocation = glGetUniformLocation(program, "modelMatrix");
		GLint viewMatrixUniformLocation = glGetUniformLocation(program, "viewMatrix");
		GLint projectionMatrixUniformLocation = glGetUniformLocation(program, "projMatrix");

		glUniformMatrix4fv(lightSrcMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(lightSrcMatrix));
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(perspectiveProjMatrix));
		
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube1));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cube3));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 36, 6);

		GLint camPositionUniformLocation = glGetUniformLocation(program, "camPosition");
		GLint lightSrcUniformDirection = glGetUniformLocation(program, "light.direction");
		GLint lightSrcUniformAmbient = glGetUniformLocation(program, "light.ambient");
		GLint lightSrcUniformDiffuse = glGetUniformLocation(program, "light.diffuse");
		GLint lightSrcUniformSpecular = glGetUniformLocation(program, "light.specular");
		GLint materialUniformDiffuse = glGetUniformLocation(program, "material.diffuse");
		GLint materialUniformSpecular = glGetUniformLocation(program, "material.specular");
		GLint materialUniformShiny = glGetUniformLocation(program, "material.shininess");
		
		glUniform3fv(camPositionUniformLocation, 1, glm::value_ptr(cameraPosition));
		glUniform3fv(lightSrcUniformDirection, 1, glm::value_ptr(glm::vec3(0.3f, -1.5f, 0.3f)));
		glUniform3fv(lightSrcUniformAmbient, 1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
		glUniform3fv(lightSrcUniformDiffuse, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(lightSrcUniformSpecular, 1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
		glUniform3fv(materialUniformDiffuse, 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.7f)));
		glUniform3fv(materialUniformSpecular, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniform1f(materialUniformShiny, 16.0f);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();

		glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(perspectiveProjMatrix));
		lastFrame = time;
	}

	// --- Cleanup ---
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return 0;
}



GLuint CreateShaderProgram(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
	GLuint vertexShader = CreateShaderFromFile(GL_VERTEX_SHADER, vertexShaderFilePath);
	GLuint fragmentShader = CreateShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderFilePath);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDetachShader(program, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(fragmentShader);

	// Check shader program link status
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetProgramInfoLog(program, infoLogLen, &infoLogLen, infoLog);
		std::cerr << "program link error: " << infoLog << std::endl;
	}

	return program;
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

void processKeyboardInput(GLFWwindow* window)
{	
	float cameraSpeed = 5.0f * runningTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (mouseInit)
	{
		lastX = xPos;
		lastY = yPos;
		mouseInit = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.9f)
		pitch = 89.9f;
	if (pitch < -89.9f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}