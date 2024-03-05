// Quick note: GLAD needs to be included first before GLFW.
// Otherwise, GLAD will complain about gl.h being already included.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ---------------
// Function declarations
// ---------------

/// <summary>
/// Creates a shader program based on the provided file paths for the vertex and fragment shaders.
/// </summary>
/// <param name="vertexShaderFilePath">Vertex shader file path</param>
/// <param name="fragmentShaderFilePath">Fragment shader file path</param>
/// <returns>OpenGL handle to the created shader program</returns>
GLuint CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

/// <summary>
/// Creates a shader based on the provided shader type and the path to the file containing the shader source.
/// </summary>
/// <param name="shaderType">Shader type</param>
/// <param name="shaderFilePath">Path to the file containing the shader source</param>
/// <returns>OpenGL handle to the created shader</returns>
GLuint CreateShaderFromFile(const GLuint& shaderType, const std::string& shaderFilePath);

/// <summary>
/// Creates a shader based on the provided shader type and the string containing the shader source.
/// </summary>
/// <param name="shaderType">Shader type</param>
/// <param name="shaderSource">Shader source string</param>
/// <returns>OpenGL handle to the created shader</returns>
GLuint CreateShaderFromSource(const GLuint& shaderType, const std::string& shaderSource);

/// <summary>
/// Function for handling the event when the size of the framebuffer changed.
/// </summary>
/// <param name="window">Reference to the window</param>
/// <param name="width">New width</param>
/// <param name="height">New height</param>
void FramebufferSizeChangedCallback(GLFWwindow* window, int width, int height);

/// <summary>
/// Struct containing data about a vertex
/// </summary>
struct Vertex
{
	GLfloat x, y, z;	// Position
	GLubyte r, g, b;	// Color
	GLfloat u, v;		// UV coordinates
};

//camera
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

//smoother scrolling
float runningTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = glfwGetTime();

//keylistener
void processKeyboardInput(GLFWwindow* window);

// Tells GLFW to listen to mouse direction
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool mouseInit = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 400;

/// <summary>
/// Main function.
/// </summary>
/// <returns>An integer indicating whether the program ended successfully or not.
/// A value of 0 indicates the program ended succesfully, while a non-zero value indicates
/// something wrong happened during execution.</returns>
int main()
{
	// Initialize GLFW
	int glfwInitStatus = glfwInit();
	if (glfwInitStatus == GLFW_FALSE)
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return 1;
	}

	// Tell GLFW that we prefer to use OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW that we prefer to use the modern OpenGL
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Tell GLFW to create a window
	float windowWidth = 800;
	float windowHeight = 800;
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GDEV 32 Laboratory Exercise 1", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	// Tell GLFW to use the OpenGL context that was assigned to the window that we just created
	glfwMakeContextCurrent(window);

	// Register the callback function that handles when the framebuffer size has changed
	glfwSetFramebufferSizeCallback(window, FramebufferSizeChangedCallback);

	// Tell GLAD to load the OpenGL function pointers
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		return 1;
	}

	// --- Vertex specification ---

	Vertex vertices[99];

	//Front			Position				Color				UV
	vertices[0] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left
	vertices[1] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f };	// Lower-right
	vertices[2] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right

	vertices[3] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right
	vertices[4] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-left
	vertices[5] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left

	//Right			Position				Color				UV
	vertices[6] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left
	vertices[7] = { 0.5f, -0.5f, 0.5f,		255, 255, 255,		1.0f, 0.0f };	// Lower-right
	vertices[8] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right

	vertices[9] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right
	vertices[10] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-left
	vertices[11] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left

	//Back			Position				Color				UV
	vertices[12] = { -0.5f, -0.5f, 0.5f,	255, 255, 255,		1.0f, 0.0f };	// Lower-left
	vertices[13] = { 0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-right
	vertices[14] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-right

	vertices[15] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-right
	vertices[16] = { -0.5f, 0.5f, 0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-left
	vertices[17] = { -0.5f, -0.5f, 0.5f,	255, 255, 255,		1.0f, 0.0f };	// Lower-left

	//Left			Position				Color				UV
	vertices[18] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f };	// Lower-left
	vertices[19] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-right
	vertices[20] = { -0.5f, 0.5f, 0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-right

	vertices[21] = { -0.5f, 0.5f, 0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-right
	vertices[22] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-left
	vertices[23] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f };	// Lower-left

	//Up			Position				Color				UV
	vertices[24] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left
	vertices[25] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 0.0f };	// Lower-right
	vertices[26] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f };	// Upper-right

	vertices[27] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f };	// Upper-right
	vertices[28] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 1.0f };	// Upper-left
	vertices[29] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left

	//Down			Position				Color				UV
	vertices[30] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left
	vertices[31] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, 0.0f };	// Lower-right
	vertices[32] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right

	vertices[33] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 1.0f };	// Upper-right
	vertices[34] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f };	// Upper-left
	vertices[35] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f };	// Lower-left

	//rubiks cube
	//front face
	vertices[36] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.25f, 0.67f };	// Lower-left
	vertices[37] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		0.50f, 0.67f };	// Lower-right
	vertices[38] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		0.50f, 0.33f };	// Upper-right

	vertices[39] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		0.50f, 0.33f };	// Upper-right
	vertices[40] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.25f, 0.33f };	// Upper-left
	vertices[41] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.25f, 0.67f };	// Lower-left

	//right face
	vertices[42] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		0.50f, 0.67f };	// Lower-left//
	vertices[43] = { 0.5f, -0.5f, 0.5f,		255, 255, 255,		0.75f, 0.67f };	// Lower-right//
	vertices[44] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.75f, 0.33f };	// Upper-right//

	vertices[45] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.75f, 0.33f };	// Upper-right//
	vertices[46] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		0.50f, 0.33f };	// Upper-left//
	vertices[47] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		0.50f, 0.67f };	// Lower-left//

	//left face
	vertices[48] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.67f };	// Lower-left//
	vertices[49] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.25f, 0.67f };	// Lower-right//
	vertices[50] = { -0.5f, 0.5f, -0.5f,			255, 255, 255,		0.25f, 0.33f };	// Upper-right//

	vertices[51] = { -0.5f, 0.5f, -0.5f,			255, 255, 255,		0.25f, 0.33f };	// Upper-right//
	vertices[52] = { -0.5f, 0.5f, 0.5f,		255, 255, 255,		0.0f, 0.33f };	// Upper-left//
	vertices[53] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.67f };	// Lower-left//

	//bottom face
	vertices[54] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.25f, 1.00f };	// Lower-left//
	vertices[55] = { 0.5f, -0.5f, 0.5f,		255, 255, 255,		0.50f, 1.00f };	// Lower-right//
	vertices[56] = { 0.5f, -0.5f, -0.5f,			255, 255, 255,		0.50f, 0.67f };	// Upper-right//

	vertices[57] = { 0.5f, -0.5f, -0.5f,			255, 255, 255,		0.50f, 0.67f };	// Upper-right//
	vertices[58] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.25f, 0.67f };	// Upper-left//
	vertices[59] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.25f, 1.00f };	// Lower-left//

	//top face
	vertices[60] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.25f, 0.33f };	// Lower-left//
	vertices[61] = { 0.5f, 0.5f, -0.5f,		255, 255, 255,		0.50f, 0.33f };	// Lower-right//
	vertices[62] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.50f, 0.0f };	// Upper-right//

	vertices[63] = { 0.5f, 0.5f, 0.5f,		255, 255, 255,		0.50f, 0.0f };	// Upper-right//
	vertices[64] = { -0.5f, 0.5f, 0.5f,	255, 255, 255,		0.25f, 0.0f };	// Upper-left//
	vertices[65] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.25f, 0.33f };	// Lower-left//

	//back face
	vertices[66] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.75f, 0.67f };	// Lower-left
	vertices[67] = { 0.5f, -0.5f, 0.5f,		255, 255, 255,		1.0f, 0.67f };	// Lower-right
	vertices[68] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 0.33f };	// Upper-right

	vertices[69] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 0.33f };	// Upper-right
	vertices[70] = { -0.5f, 0.5f, 0.5f,		255, 255, 255,		0.75f, 0.33f };	// Upper-left
	vertices[71] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.75f, 0.67f };	// Lower-left

	// Create a vertex buffer object (VBO), and upload our vertices data to the VBO
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create a vertex array object that contains data on how to map vertex attributes
	// (e.g., position, color) to vertex shader properties.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertex attribute 0 - Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

	// Vertex attribute 1 - Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, r)));

	// Vertex attribute 2 - UV coordinate
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, u)));

	glBindVertexArray(0);

	// Create a shader program
	GLuint program = CreateShaderProgram("main.vsh", "main.fsh");

	// Tell OpenGL the dimensions of the region where stuff will be drawn.
	// For now, tell OpenGL to use the whole screen
	glViewport(0, 0, windowWidth, windowHeight);

	// Create a variable that will contain the ID for our texture,
	// and use glGenTextures() to generate the texture itself
	GLuint texwood;
	glGenTextures(1, &texwood);
	GLuint texrubiks;
	glGenTextures(1, &texrubiks);
	GLuint texbrick;
	glGenTextures(1, &texbrick);

	// --- Load our image using stb_image ---

	// Im image-space (pixels), (0, 0) is the upper-left corner of the image
	// However, in u-v coordinates, (0, 0) is the lower-left corner of the image
	// This means that the image will appear upside-down when we use the image data as is
	// This function tells stbi to flip the image vertically so that it is not upside-down when we use it
	stbi_set_flip_vertically_on_load(true);

	// 'imageWidth' and imageHeight will contain the width and height of the loaded image respectively
	int imageWidth, imageHeight, numChannels;

	// Read the image data and store it in an unsigned char array
	unsigned char* imageData = stbi_load("woodfloor.jpg", &imageWidth, &imageHeight, &numChannels, 0);

	// Make sure that we actually loaded the image before uploading the data to the GPU
	if (imageData != nullptr)
	{
		// Our texture is 2D, so we bind our texture to the GL_TEXTURE_2D target
		glBindTexture(GL_TEXTURE_2D, texwood);

		// Set the filtering methods for magnification and minification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Set the wrapping method for the s-axis (x-axis) and t-axis (y-axis)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload the image data to GPU memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

		// If we set minification to use mipmaps, we can tell OpenGL to generate the mipmaps for us
		//glGenerateMipmap(GL_TEXTURE_2D);

		// Once we have copied the data over to the GPU, we can delete
		// the data on the CPU side, since we won't be using it anymore
		stbi_image_free(imageData);
		imageData = nullptr;
	}
	else
	{
		std::cerr << "Failed to load image" << std::endl;
	}

	// Read the image data and store it in an unsigned char array
	imageData = stbi_load("rubiks.jpg", &imageWidth, &imageHeight, &numChannels, 0);

	// Make sure that we actually loaded the image before uploading the data to the GPU
	if (imageData != nullptr)
	{
		// Our texture is 2D, so we bind our texture to the GL_TEXTURE_2D target
		glBindTexture(GL_TEXTURE_2D, texrubiks);

		// Set the filtering methods for magnification and minification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Set the wrapping method for the s-axis (x-axis) and t-axis (y-axis)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload the image data to GPU memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

		// If we set minification to use mipmaps, we can tell OpenGL to generate the mipmaps for us
		//glGenerateMipmap(GL_TEXTURE_2D);

		// Once we have copied the data over to the GPU, we can delete
		// the data on the CPU side, since we won't be using it anymore
		stbi_image_free(imageData);
		imageData = nullptr;
	}
	else
	{
		std::cerr << "Failed to load image" << std::endl;
	}

	// Read the image data and store it in an unsigned char array
	imageData = stbi_load("brickwall.jpg", &imageWidth, &imageHeight, &numChannels, 0);

	// Make sure that we actually loaded the image before uploading the data to the GPU
	if (imageData != nullptr)
	{
		// Our texture is 2D, so we bind our texture to the GL_TEXTURE_2D target
		glBindTexture(GL_TEXTURE_2D, texbrick);

		// Set the filtering methods for magnification and minification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Set the wrapping method for the s-axis (x-axis) and t-axis (y-axis)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload the image data to GPU memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

		// If we set minification to use mipmaps, we can tell OpenGL to generate the mipmaps for us
		//glGenerateMipmap(GL_TEXTURE_2D);

		// Once we have copied the data over to the GPU, we can delete
		// the data on the CPU side, since we won't be using it anymore
		stbi_image_free(imageData);
		imageData = nullptr;
	}
	else
	{
		std::cerr << "Failed to load image" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use the shader program that we created
		glUseProgram(program);

		// Use the vertex array object that we created
		glBindVertexArray(vao);

		// Make our sampler in the fragment shader use texture unit 0
		GLint texUniformLocation = glGetUniformLocation(program, "tex");
		glUniform1i(texUniformLocation, 0);

		float currentFrame = glfwGetTime();
		runningTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float time = 1;

		processKeyboardInput(window);

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 perspectiveMatrix = glm::mat4(1.0f);
		glm::mat4 mvpMat = glm::mat4(1.0f);
		GLint uniformLocation = glGetUniformLocation(program, "mvpMat");

		viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		perspectiveMatrix = glm::perspective(1.5708f, 1.0f, 0.001f, 100.0f);

		// floor
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texbrick);

		glm::mat4 modelMatrix1 = glm::mat4(1.0f);
		modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0.0f, 0.0f, 0.0f));
		modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(20.0f, 20.0f, 20.0f));
		mvpMat = perspectiveMatrix * viewMatrix * modelMatrix1;
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mvpMat));
		glDrawArrays(GL_TRIANGLES, 0, 30);

		glBindTexture(GL_TEXTURE_2D, texwood);
		glDrawArrays(GL_TRIANGLES, 30, 6);

		//rubiks
		glBindTexture(GL_TEXTURE_2D, texrubiks);

		glm::mat4 modelMatrix2 = glm::mat4(1.0f);
		modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0.0f, 0.0f, 0.0f));
		modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(2.0f, 2.0f, 2.0f));
		mvpMat = perspectiveMatrix * viewMatrix * modelMatrix2;
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mvpMat));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		// Tell GLFW to swap the screen buffer with the offscreen buffer
		glfwSwapBuffers(window);

		// Tell GLFW to process window events (e.g., input events, window closed events, etc.)
		glfwPollEvents();
	}

	// --- Cleanup ---

	// Make sure to delete the shader program
	glDeleteProgram(program);

	// Delete the VBO that contains our vertices
	glDeleteBuffers(1, &vbo);

	// Delete the vertex array object
	glDeleteVertexArrays(1, &vao);

	// Remember to tell GLFW to clean itself up before exiting the application
	glfwTerminate();

	return 0;
}

/// <summary>
/// Creates a shader program based on the provided file paths for the vertex and fragment shaders.
/// </summary>
/// <param name="vertexShaderFilePath">Vertex shader file path</param>
/// <param name="fragmentShaderFilePath">Fragment shader file path</param>
/// <returns>OpenGL handle to the created shader program</returns>
GLuint CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
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
	if (linkStatus != GL_TRUE) {
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetProgramInfoLog(program, infoLogLen, &infoLogLen, infoLog);
		std::cerr << "program link error: " << infoLog << std::endl;
	}

	return program;
}

/// <summary>
/// Creates a shader based on the provided shader type and the path to the file containing the shader source.
/// </summary>
/// <param name="shaderType">Shader type</param>
/// <param name="shaderFilePath">Path to the file containing the shader source</param>
/// <returns>OpenGL handle to the created shader</returns>
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

/// <summary>
/// Creates a shader based on the provided shader type and the string containing the shader source.
/// </summary>
/// <param name="shaderType">Shader type</param>
/// <param name="shaderSource">Shader source string</param>
/// <returns>OpenGL handle to the created shader</returns>
GLuint CreateShaderFromSource(const GLuint& shaderType, const std::string& shaderSource)
{
	GLuint shader = glCreateShader(shaderType);

	const char* shaderSourceCStr = shaderSource.c_str();
	GLint shaderSourceLen = static_cast<GLint>(shaderSource.length());
	glShaderSource(shader, 1, &shaderSourceCStr, &shaderSourceLen);
	glCompileShader(shader);

	// Check compilation status
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

/// <summary>
/// Function for handling the event when the size of the framebuffer changed.
/// </summary>
/// <param name="window">Reference to the window</param>
/// <param name="width">New width</param>
/// <param name="height">New height</param>
void FramebufferSizeChangedCallback(GLFWwindow* window, int width, int height)
{
	// Whenever the size of the framebuffer changed (due to window resizing, etc.),
	// update the dimensions of the region to the new size
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
	direction.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}