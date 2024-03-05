#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <limits> //https://stackoverflow.com/questions/8690567/setting-an-int-to-infinity-in-c
#include <iostream>
using namespace std;

// IMPORTANT: If you are using Mac, kindly change this to the full path of the test.txt file
#define INPUT_FILE "test.txt"

/**
 * Point class
 */
struct Point {
	/**
	 * X-coordinate of the point
	 */
	float x;

	/**
	 * Y-coordinate of the point
	 */
	float y;
};

struct Vector2
{
public:
	/**
	 * X component
	 */
	float x;

	/**
	 * Y component
	 */
	float y;

	/**
	 * Constructor
	 * @param newX - New x component
	 * @param newY - New y component
	 */
	Vector2(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	/**
	 * Constructor
	 */
	Vector2()
		: Vector2(0.0f, 0.0f)
	{
	}

	static Vector2 perp(Vector2 a)
	{
		Vector2 perpendicularVector(-1*a.y, a.x);
		if (perpendicularVector.x == -0)
		{
			perpendicularVector.x = 0;
		}
		if (perpendicularVector.y == -0)
		{
			perpendicularVector.y = 0;
		}
		return perpendicularVector;
	}

	static float dot(Vector2 a, Vector2 b)
	{
		float dotProduct = a.x * b.x + a.y * b.y;
		return dotProduct;
	}

	float magnitude()
	{
		float Magnitude = sqrt(x * x + y * y);
		return Magnitude;
	}

	Vector2 normalized()
	{

		Vector2 tempVec(x, y);
		float Magnitude = tempVec.magnitude();

		if (Magnitude > 0.0)
		{
			tempVec.x /= Magnitude;
			tempVec.y /= Magnitude;
			return tempVec;
		}
		else
		{
			Vector2 ret(0.0f, 0.0f);
			return ret;
		}
	}

	static Vector2 project(Vector2 a, Vector2 b)
	{
		float MagnitudeB = b.magnitude();
		float DotAB = Vector2::dot(a, b);
		float ScalarMagDot = DotAB / pow(MagnitudeB, 2);
		Vector2 Projection(ScalarMagDot * b.x, ScalarMagDot * b.y);
		return Projection;
	}
};

void CheckSize(std::vector<Vector2> temp)
{
	cout << temp.size() << endl;
}

void ListVectors(std::vector<Vector2> temp)
{
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << "Vector " << i+1 << ": " << temp[i].x << " " << temp[i].y << endl;
	}
}

std::vector<Vector2> GetShapeVectors(std::vector<Point> inputtedListOfPoints)
{
	std::vector<Vector2> listOfVectors;
	for (int i = 0; i < inputtedListOfPoints.size(); i++)
	{
		Point tempPoint1 = inputtedListOfPoints[i];
		Point tempPoint2 = inputtedListOfPoints[i+1];
		if ((i + 1) == inputtedListOfPoints.size())
		{
			tempPoint2.x = inputtedListOfPoints[0].x;
			tempPoint2.y = inputtedListOfPoints[0].y;
		}

		Vector2 newTempVector(tempPoint2.x - tempPoint1.x, tempPoint2.y - tempPoint1.y);
		listOfVectors.push_back(newTempVector);
	}
	return listOfVectors;
}

std::vector<Vector2> InitiateListOfNormalEdges(std::vector<Vector2> firstList, std::vector<Vector2> secondList)
{
	std::vector<Vector2> listOfNormalEdges;
	for (int i = 0; i < firstList.size(); i++)
	{
		Vector2 tempVector = Vector2::perp(firstList[i]);
		listOfNormalEdges.push_back(tempVector);

	}
	for (int i = 0; i < secondList.size(); i++)
	{
		Vector2 tempVector = Vector2::perp(secondList[i]);
		listOfNormalEdges.push_back(tempVector);

	}
	return listOfNormalEdges;
}

float CheckProjection(std::vector<Point> listOfPoints, Vector2 normalEdge, const string whatOutput)
{
	float min = std::numeric_limits<float>::infinity();
	float max = -std::numeric_limits<float>::infinity();
	

	for (int i = 0; i < listOfPoints.size(); i++)
	{
		Vector2 originToPoint(listOfPoints[i].x, listOfPoints[i].y);
		Vector2 tempPoint = Vector2::project(originToPoint, normalEdge);
		float distanceFromOrigin = sqrt(tempPoint.x * tempPoint.x + tempPoint.y * tempPoint.y);
		if (i == 0)
		{
			min = distanceFromOrigin;
		}
		else
		{
			if (distanceFromOrigin < min)
			{
				min = distanceFromOrigin;
			}
			else if (distanceFromOrigin > max)
			{
				max = distanceFromOrigin;
			}
		}
	}

	if (whatOutput == "min")
	{
		return min;
	}
	return max;
}

/**
 * @brief Checks whether the two specified convex shapes are overlapping or not
 * using the separating-axis theorem
 * @param shapeA List of points in the first convex shape
 * @param shapeB List of points in the second convex shape
 * @return Returns true if the two convex shapes are overlapping. Returns false otherwise.
 */
bool SAT(const std::vector<Point>& shapeA, const std::vector<Point>& shapeB) {
	// TODO: Implement
	std::vector<Vector2> shapeAListOfVectors = GetShapeVectors(shapeA);
	std::vector<Vector2> shapeBListOfVectors = GetShapeVectors(shapeB);
	std::vector<Vector2> listOfNormalEdge = InitiateListOfNormalEdges(shapeAListOfVectors, shapeBListOfVectors);
	std::vector<bool> listOfCheckers;
	for (int i = 0; i < listOfNormalEdge.size(); i++)
	{
		listOfCheckers.push_back(false);
	}

	for (int i = 0; i < listOfNormalEdge.size(); i++)
	{
		float minA = 0, maxA = 0, minB = 0, maxB = 0;
		minA = CheckProjection(shapeA, listOfNormalEdge[i], "min");
		maxA = CheckProjection(shapeA, listOfNormalEdge[i], "max");
		minB = CheckProjection(shapeB, listOfNormalEdge[i], "min");
		maxB = CheckProjection(shapeB, listOfNormalEdge[i], "max");

		if ((minA <= minB && minB <= maxA) | (minA <= maxB && maxB <= maxA))
		{
			listOfCheckers[i] = true;
		}
		else
		{
			listOfCheckers[i] = false;
		}
	}
	
	bool checker = true;
	for (int i = 0; i < listOfCheckers.size(); i++)
	{
		if (listOfCheckers[i] == false)
		{
			checker = false;
			break;
		}
	}
	return checker;
}

// ----------------------------------------------------------------------------------
// DO NOT TOUCH ANY CODE BEYOND THIS POINT
// ----------------------------------------------------------------------------------
#include <cstddef>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

const char* vertShaderSource = R"(#version 330
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
out vec3 outVertexColor;
uniform mat4 mvpMatrix;
void main() {
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
	outVertexColor = vertexColor;
})";
const char* fragShaderSource = R"(#version 330
in vec3 outVertexColor;
out vec4 fragColor;
void main() {
	fragColor = vec4(outVertexColor, 1.0);
})";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
struct TestCase {
	std::vector<Point> shapeA;
	std::vector<Point> shapeB;
	Point shapeAPosition;
	Point shapeBPosition;
};
struct AppData {
	std::vector<TestCase> testCases;
	GLuint vbo;
	size_t numVertices;
	int currentTestCaseIndex;
};
struct Vertex {
	GLfloat x, y, z;
	GLfloat r, g, b;
};
struct Matrix4x4 {
	GLfloat values[16];
};

void RefreshScene(AppData* data);
void GenerateRandomPolyline(std::vector<Point>& points);

Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 ret;
	ret.values[0] = a.values[0] * b.values[0] + a.values[4] * b.values[1] + a.values[8] * b.values[2] + a.values[12] * b.values[3];
	ret.values[4] = a.values[0] * b.values[4] + a.values[4] * b.values[5] + a.values[8] * b.values[6] + a.values[12] * b.values[7];
	ret.values[8] = a.values[0] * b.values[8] + a.values[4] * b.values[9] + a.values[8] * b.values[10] + a.values[12] * b.values[11];
	ret.values[12] = a.values[0] * b.values[12] + a.values[4] * b.values[13] + a.values[8] * b.values[14] + a.values[12] * b.values[15];
	ret.values[1] = a.values[1] * b.values[0] + a.values[5] * b.values[1] + a.values[9] * b.values[2] + a.values[13] * b.values[3];
	ret.values[5] = a.values[1] * b.values[4] + a.values[5] * b.values[5] + a.values[9] * b.values[6] + a.values[13] * b.values[7];
	ret.values[9] = a.values[1] * b.values[8] + a.values[5] * b.values[9] + a.values[9] * b.values[10] + a.values[13] * b.values[11];
	ret.values[13] = a.values[1] * b.values[12] + a.values[5] * b.values[13] + a.values[9] * b.values[14] + a.values[13] * b.values[15];
	ret.values[2] = a.values[2] * b.values[0] + a.values[6] * b.values[1] + a.values[10] * b.values[2] + a.values[14] * b.values[3];
	ret.values[6] = a.values[2] * b.values[4] + a.values[6] * b.values[5] + a.values[10] * b.values[6] + a.values[14] * b.values[7];
	ret.values[10] = a.values[2] * b.values[8] + a.values[6] * b.values[9] + a.values[10] * b.values[10] + a.values[14] * b.values[11];
	ret.values[14] = a.values[2] * b.values[12] + a.values[6] * b.values[13] + a.values[10] * b.values[14] + a.values[14] * b.values[15];
	ret.values[3] = a.values[3] * b.values[0] + a.values[7] * b.values[1] + a.values[11] * b.values[2] + a.values[15] * b.values[3];
	ret.values[7] = a.values[3] * b.values[4] + a.values[7] * b.values[5] + a.values[11] * b.values[6] + a.values[15] * b.values[7];
	ret.values[11] = a.values[3] * b.values[8] + a.values[7] * b.values[9] + a.values[11] * b.values[10] + a.values[15] * b.values[11];
	ret.values[15] = a.values[3] * b.values[12] + a.values[7] * b.values[13] + a.values[11] * b.values[14] + a.values[15] * b.values[15];

	return ret;
}

GLuint CreateShader(const GLuint& type, const std::string& source) {
	GLuint shader = glCreateShader(type);

	const char* sourceCStr = source.c_str();
	GLint sourceLen = source.size();
	glShaderSource(shader, 1, &sourceCStr, &sourceLen);
	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, infoLog);

		std::string errorMsg;
		if (type == GL_VERTEX_SHADER) {
			errorMsg += std::string("Failed to compile vertex shader!\n");
		}
		else if (type == GL_FRAGMENT_SHADER) {
			errorMsg += std::string("Failed to compile fragment shader!\n");
		}
		else {
			errorMsg += std::string("Failed to compile shader!\n");
		}
		errorMsg += std::string(infoLog);

		std::cout << errorMsg << std::endl;
	}

	return shader;
}

GLuint CreateShaderProgramFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	GLuint vsh = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fsh = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLuint program = glCreateProgram();
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetProgramInfoLog(program, infoLogLen, &infoLogLen, infoLog);
		throw std::runtime_error(std::string("program link error: ") + infoLog);
		return 0;
	}

	glDetachShader(program, vsh);
	glDetachShader(program, fsh);
	glDeleteShader(vsh);
	glDeleteShader(fsh);

	return program;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	AppData* appData = reinterpret_cast<AppData*>(glfwGetWindowUserPointer(window));
	int index = appData->currentTestCaseIndex;
	int numTestCases = appData->testCases.size();
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			index = ((index - 1) + numTestCases) % numTestCases;
		}
		if (key == GLFW_KEY_RIGHT) {
			index = (index + 1) % numTestCases;
		}
		appData->currentTestCaseIndex = index;
		RefreshScene(appData);
	}
}

Matrix4x4 CreateIdentity() {
	Matrix4x4 ret = {};
	ret.values[0] = 1.0f; ret.values[5] = 1.0f; ret.values[10] = 1.0f; ret.values[15] = 1.0f;
	return ret;
}

Matrix4x4 CreateOrtho(float left, float right, float bottom, float top, float near, float far) {
	Matrix4x4 ret =
	{
		2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
		0.0f, 0.0f, -2.0f / (far - near), 0.0f,
		-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f
	};

	return ret;
}

void AppendConvexShapeVertices(const std::vector<Point>& points, std::vector<Vertex>& vertices, float zOrder = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
	if (points.size() < 2) {
		return;
	}
	for (size_t i = 2; i < points.size(); ++i) {
		vertices.push_back( { points[0].x, points[0].y, zOrder, r, g, b } );
		vertices.push_back( { points[i - 1].x, points[i - 1].y, zOrder, r, g, b } );
		vertices.push_back( { points[i].x, points[i].y, zOrder, r, g, b } );
	}
}

void RefreshScene(AppData* data) {
	size_t index = data->currentTestCaseIndex;
	bool isOverlapping = SAT(data->testCases[index].shapeA, data->testCases[index].shapeB);
	float r = 1.0f, g = isOverlapping ? 0.0f : 1.0f, b = isOverlapping ? 0.0f : 1.0f;

	std::vector<Vertex> vertices;
	AppendConvexShapeVertices(data->testCases[index].shapeA, vertices, 0.0f, r, g, b);
	AppendConvexShapeVertices(data->testCases[index].shapeB, vertices, 0.0f, r, g, b);
	
	glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	data->numVertices = vertices.size();
}

void MoveShape(std::vector<Point>& points, float dx, float dy, float distance) {
	float mag = dx * dx + dy * dy;
	if (mag > 0.0f) {
		mag = sqrtf(mag); dx /= mag; dy /= mag;
	}
	for (size_t i = 0; i < points.size(); ++i) {
		points[i].x += dx * distance;
		points[i].y += dy * distance;
	}
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	AppData appData = {};
	std::ifstream file(INPUT_FILE);
	if (file.fail()) {
		std::cout << "Failed to read test file!" << std::endl;
		return 1;
	}

	int numCases;
	file >> numCases;
	for (int i = 0; i < numCases; ++i) {
		appData.testCases.emplace_back();
		int numA, numB;
		file >> numA;
		for (int j = 0; j < numA; ++j) {
			Point p;
			file >> p.x >> p.y;
			appData.testCases.back().shapeA.push_back(p);	
		}
		file >> numB;
		for (int j = 0; j < numB; ++j) {
			Point p;
			file >> p.x >> p.y;
			appData.testCases.back().shapeB.push_back(p);
		}
	}

	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "Cannot initialize GLFW!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Separating Axis Theorem", nullptr, nullptr);
	if (!window) {
		std::cerr << "Cannot create window.";
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetKeyCallback(window, KeyCallback);

	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, x)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));
	glBindVertexArray(0);

	GLuint program = CreateShaderProgramFromSource(vertShaderSource, fragShaderSource);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	appData.vbo = vbo;
	glfwSetWindowUserPointer(window, &appData);

	RefreshScene(&appData);

	Matrix4x4 projMatrix = CreateOrtho(0.0f, WINDOW_WIDTH * 1.0f, 0.0f, WINDOW_HEIGHT * 1.0f, -100.0f, 100.0f);
	float prevTime = glfwGetTime(), speed = 200.0f;
	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		float dx = 0.0f, dy = 0.0f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { dy += 1.0f; }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { dy -= 1.0f; }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { dx -= 1.0f; }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { dx += 1.0f; }
		MoveShape(appData.testCases[appData.currentTestCaseIndex].shapeA, dx, dy, speed * deltaTime);
		RefreshScene(&appData);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);

		glBindVertexArray(vao);
		glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_FALSE, projMatrix.values);
		glDrawArrays(GL_TRIANGLES, 0, appData.numVertices);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program); program = 0;
	glDeleteVertexArrays(1, &vao); vao = 0;
	glDeleteBuffers(1, &vbo); vbo = 0;
	glfwDestroyWindow(window);window = nullptr;
	glfwTerminate();

	return 0;
}
