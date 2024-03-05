#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>


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

int isSpacePressed = 0;
int isRPressed = 0;

bool isPyramid = true;

float runningTime = 0.0f;
double lastFrame = 0;

bool shiftPressed = false;
float dayNightCycle = 0.0f;
float cycleLength = 5.0f;
float dayNightCycleLastModified = 0.0f;

float xAxis = 0.0f;
float yAxis = 0.0f;

float objectXLength = 1.5f;
float objectYLength = 1.5f;
float objectZLength = 1.5f;

struct Vertex
{
	GLfloat x, y, z;	// Position
	GLubyte r, g, b;	// Color
	GLfloat u, v;       // UV coordinates
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
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "GDEV 32 Final Project", nullptr, nullptr);
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
	Vertex vertices[90];

	//Labels		Position					Color				UV					Normal
	//Room
	//Front
	vertices[0] = { -0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, 1.0f };   // Lower-left
	vertices[1] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, 0.0f,			1.0f, -1.0f, 1.0f };    // Lower-right
	vertices[2] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[3] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[4] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 1.0f,			-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[5] = { -0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, 1.0f };   // Lower-left

	//Right
	vertices[6] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, -1.0f, 1.0f };    // Lower-left
	vertices[7] = { 0.5f, -0.5f, -0.5f,			255, 255, 255,		1.0f, 0.0f,			1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[8] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[9] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[10] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 1.0f,			1.0f, 1.0f, 1.0f };		// Upper-left
	vertices[11] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, -1.0f, 1.0f };	// Lower-left

	//Back
	vertices[12] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[13] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f,			1.0f, -1.0f, -1.0f };	// Lower-right
	vertices[14] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[15] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[16] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f,			-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[17] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left

	//Left
	vertices[18] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[19] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		1.0f, 0.0f,			-1.0f, -1.0f, 1.0f };	// Lower-right
	vertices[20] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f,			-1.0f, 1.0f, 1.0f };    // Upper-right
	vertices[21] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f,			-1.0f, 1.0f, 1.0f };	// Upper-right
	vertices[22] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f,			-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[23] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left

	//Up
	vertices[24] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[25] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, 1.0f, 1.0f };		// Lower-right
	vertices[26] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[27] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[28] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[29] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f };	// Lower-left

	//Floor
	vertices[30] = {-0.5f, 0.0f, 0.5f, 			208, 213, 247, 		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f};     // Lower-left
	vertices[31] = {0.5f, 0.0f, 0.5f, 			208, 213, 247, 		0.0f, 0.0f,			1.0f, 1.0f, 1.0f};      // Lower-right
	vertices[32] = {0.5f, 0.0f, -0.5f, 			208, 213, 247, 		0.0f, 0.0f,			1.0f, 1.0f, -1.0f};     // Upper-right
	vertices[33] = {0.5f, 0.0f, -0.5f, 			208, 213, 247, 		0.0f, 0.0f,			1.0f, 1.0f, -1.0f};	    // Upper-right
	vertices[34] = {-0.5f, 0.0f, -0.5f, 		208, 213, 247, 		0.0f, 0.0f,			-1.0f, 1.0f, -1.0f};    // Upper-left
	vertices[35] = {-0.5f, 0.0f, 0.5f, 			208, 213, 247, 		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f};	    // Lower-left

	//Pyramid
	//Front
	vertices[36] = {0.0f, 0.5f, 0.0f, 			255, 255, 255, 		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f};
	vertices[37] = {-0.5f, -0.5f, 0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		-1.0f, 1.0f, 1.0f};
	vertices[38] = {0.5f, -0.5f, 0.5f, 			255, 255, 255, 		1.0f, 0.0f, 		1.0f, 1.0f, 1.0f};

	// Right
	vertices[39] = {0.0f, 0.5f, 0.0f, 			255, 255, 255,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f};
	vertices[40] = {0.5f, -0.5f, 0.5f, 			255, 255, 255, 		0.0f, 0.0f, 		1.0f, 1.0f, 1.0f};
	vertices[41] = {0.5f, -0.5f, -0.5f, 		255, 255, 255, 		1.0f, 0.0f, 		1.0f, 1.0f, -1.0f};

	// Back
	vertices[42] = {0.0f, 0.5f, 0.0f, 			255, 255, 255, 		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f};
	vertices[43] = {0.5f, -0.5f, -0.5f,			255, 255, 255, 		0.0f, 0.0f, 		1.0f, 1.0f, -1.0f};
	vertices[44] = {-0.5f, -0.5f, -0.5f, 		255, 255, 255, 		1.0f, 0.0f, 		1.0f, 1.0f, -1.0f};

	// Left
	vertices[45] = {0.0f, 0.5f, 0.0f, 			255, 255, 255, 		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f};
	vertices[46] = {-0.5f, -0.5f, -0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		-1.0f, 1.0f, -1.0f};
	vertices[47] = {-0.5f, -0.5f, 0.5f, 		255, 255, 255, 		1.0f, 0.0f, 		-1.0f, 1.0f, 1.0f};

	// Bottom
	vertices[48] = {-0.5f, -0.5f, 0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		0.0f, -1.0f, 0.0f}; 	// Upper-left
	vertices[49] = {0.5f, -0.5f, 0.5f, 			255, 255, 255, 		1.0f, 0.0f, 		1.0f, -1.0f, 1.0f}; 	// Lower-right
	vertices[50] = {-0.5f, -0.5f, -0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		1.0f, -1.0f, -1.0f};	// Lower-right
	vertices[51] = {-0.5f, -0.5f, -0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		1.0f, -1.0f, -1.0f}; 	// Lower-right
	vertices[52] = {0.5f, -0.5f, -0.5f, 		255, 255, 255, 		0.0f, 0.0f, 		-1.0f, -1.0f, -1.0f}; 	// Upper-Left
	vertices[53] = {0.5f, -0.5f, 0.5f, 			255, 255, 255, 		1.0f, 0.0f, 		-1.0f, -1.0f, 1.0f}; 	// Lower-left

	//Cube
	//Front
	vertices[54] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, 1.0f };   // Lower-left
	vertices[55] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, 0.0f, 		1.0f, -1.0f, 1.0f };    // Lower-right
	vertices[56] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[57] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f,			1.0f, 1.0f, 1.0f };     // Upper-right
	vertices[58] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 1.0f, 		-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[59] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, 1.0f };   // Lower-left

	//Right
	vertices[60] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, -1.0f, 1.0f };    // Lower-left
	vertices[61] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f, 		1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[62] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[63] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[64] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 1.0f, 		1.0f, 1.0f, 1.0f };		// Upper-left
	vertices[65] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			1.0f, -1.0f, 1.0f };	// Lower-left

	//Back
	vertices[66] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[67] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f, 		1.0f, -1.0f, -1.0f };	// Lower-right
	vertices[68] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[69] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[70] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f, 		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[71] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left

	//Left
	vertices[72] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left
	vertices[73] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		1.0f, 0.0f, 		-1.0f, -1.0f, 1.0f };	// Lower-right
	vertices[74] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 		-1.0f, 1.0f, 1.0f };    // Upper-right
	vertices[75] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 		-1.0f, 1.0f, 1.0f };	// Upper-right
	vertices[76] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f, 		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[77] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left

	//Up
	vertices[78] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f };    // Upper-left
	vertices[79] = { 0.5f, 0.5f, 0.5f,			255, 255, 255,		1.0f, 0.0f, 		1.0f, 1.0f, 1.0f };		// Lower-right
	vertices[80] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };    // Upper-right
	vertices[81] = { 0.5f, 0.5f, -0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, 1.0f, -1.0f };	// Upper-right
	vertices[82] = { -0.5f, 0.5f, -0.5f,		255, 255, 255,		0.0f, 1.0f, 		-1.0f, 1.0f, -1.0f };   // Upper-left
	vertices[83] = { -0.5f, 0.5f, 0.5f,			255, 255, 255,		0.0f, 0.0f,			-1.0f, 1.0f, 1.0f };	// Lower-left

	//Bottom
	vertices[84] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Upper-left
	vertices[85] = { 0.5f, -0.5f, -0.5f,		255, 255, 255,		1.0f, 0.0f, 		1.0f, -1.0f, -1.0f };   // Lower-right
	vertices[86] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, -1.0f, 1.0f };    // Upper-right
	vertices[87] = { 0.5f, -0.5f, 0.5f,			255, 255, 255,		1.0f, 1.0f, 		1.0f, -1.0f, 1.0f };    // Upper-right
	vertices[88] = { -0.5f, -0.5f, 0.5f,		255, 255, 255,		0.0f, 1.0f, 		-1.0f, -1.0f, 1.0f };   // Upper-left
	vertices[89] = { -0.5f, -0.5f, -0.5f,		255, 255, 255,		0.0f, 0.0f,			-1.0f, -1.0f, -1.0f };  // Lower-left
	// --- vertices end ---

	
	//skybox
	float skyboxVertices[] =
	{
		//   Coordinates
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

	unsigned int skyboxIndices[] =
	{
		1, 2, 6,
		6, 5, 1,
		0, 4, 7,
		7, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 3, 2,
		2, 1, 0,
		0, 1, 5,
		5, 4, 0,
		3, 7, 6,
		6, 2, 3
	};

	// --- VBO VAO --- 
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLuint skyboxShader = CreateShaderProgram("skybox.vsh", "skybox.fsh");

	std::string facesCubemap[6] =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}

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

	// Vertex attribute 2 - UV coordinate
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, u)));

	// Vertex attribute 3 - Normal
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, nx)));

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

		//rendering the shadows
		glUseProgram(depthShader);
		glBindVertexArray(depthVAO);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

		glm::mat4 dirLightProjMatrix = glm::ortho(-20.0f, 20.0f, -10.0f, 10.0f, -20.0f, 20.0f);
		glm::mat4 dirLightViewMatrix = glm::lookAt(glm::vec3(0.0f, 7.0f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSrcMatrix = dirLightProjMatrix * dirLightViewMatrix;
		
		GLint dirLightProjMatrixUniformLocation = glGetUniformLocation(depthShader, "dirLightProjMatrix");
		glUniformMatrix4fv(dirLightProjMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(dirLightProjMatrix));
		GLint dirLightViewMatrixUniformLocation = glGetUniformLocation(depthShader, "dirLightViewMatrix");
		glUniformMatrix4fv(dirLightViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(dirLightViewMatrix));
		
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
		glClear(GL_DEPTH_BUFFER_BIT); 
		
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 centerObject = glm::mat4(1.0f);

		centerObject = glm::translate(centerObject, glm::vec3(xAxis, 1.5f, yAxis));
		centerObject = glm::rotate(centerObject, glm::radians(25.0f*time), glm::vec3(0.0f, 1.0f, 0.0f));
		centerObject = glm::scale(centerObject, glm::vec3(objectXLength, objectYLength, objectZLength));
		
		GLint depthModelMatrixUniformLocation = glGetUniformLocation(depthShader, "modelMatrix");
		glUniformMatrix4fv(depthModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(centerObject));
		if(isPyramid)
		{
			glDrawArrays(GL_TRIANGLES, 36, 18);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 54, 36);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		


		//rendering the objects
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
		
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(centerObject));
		if(isPyramid)
		{
			glDrawArrays(GL_TRIANGLES, 36, 18);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 54, 36);
		}

		glBindTexture(GL_TEXTURE_2D, depthTex);
		glUniform1i(depthTexUniformLocation, 0);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 30, 6);

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

		//rendering the skybox
		glDepthFunc(GL_LEQUAL);
		glUseProgram(skyboxShader);
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp)));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		GLint skyboxDayNightUniform = glGetUniformLocation(skyboxShader, "dayNightCycle");

		//cycleLength is 1 to 10, 1 being slowest and 10 being fastest
		float dayNight = 0.3f + abs(cos((time-dayNightCycleLastModified)*(cycleLength/5.0f))*0.7);
		glUniform1f(skyboxDayNightUniform, dayNight);

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);

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
	
	//change object
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && isSpacePressed == 0)
	{
		if(isPyramid)
		{
			isPyramid = false;
		}
		else
		{
			isPyramid = true;
		}
		isSpacePressed++;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		isSpacePressed = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
	{
		isRPressed = 0;
	}

	//move object
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		yAxis += cameraSpeed*0.4f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		yAxis -= cameraSpeed*0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		xAxis += cameraSpeed*0.4f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		xAxis -= cameraSpeed*0.4f;

	if ((glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) && isRPressed == 0)
	{
		if(!isPyramid)
		{
			objectXLength = rand() % 2 + 1;
			objectYLength = rand() % 2 + 1;
			objectZLength = rand() % 2 + 1;
		}
		else if(isPyramid)
		{
			objectXLength = 1.5f;
			objectYLength = 1.5f;
			objectZLength = 1.5f;
		}
		isRPressed++;
	}

	//skybox day night cycle change
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		shiftPressed = true;
	} else
	{
		shiftPressed = false;
	}

	if ((glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE) && (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE))
	{
		dayNightCycle = 0;
	}

	if (shiftPressed)
	{
		if(dayNightCycle == 0)
		{
			if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			{
				if (cycleLength > 1.0f)
					cycleLength -= 1.0f;
					dayNightCycleLastModified = glfwGetTime();
				dayNightCycle++;
			}
			if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			{
				if (cycleLength < 10.0f)
					cycleLength += 1.0f;
					dayNightCycleLastModified = glfwGetTime();
				dayNightCycle++;
			}
		}
		
	}
		

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