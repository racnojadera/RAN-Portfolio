#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>

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

	bool operator<(Point p)
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};

/**
 * AABB
 */
struct AABB {
	/**
	 * Minimum and maximum points of the AABB
	 */
	Point min, max;
};

/**
 * Circle
 */
struct Circle {
	/**
	 * Circle center
	 */
	Point center;

	/**
	 * Circle radius
	 */
	float radius;
};

/**
 * @brief Constructs an AABB from the provided points.
 * @param[in] inputPoints Input points
 * @return AABB of the provided points
 */
AABB ConstructAABB(const std::vector<Point>& inputPoints) {
	AABB ret = {};

	ret.min = inputPoints[0];
	ret.max = inputPoints[inputPoints.size()-1];
		
	// TODO: Implement

	for (int i = 1; i < inputPoints.size(); i++)
	{
		if ((inputPoints[i].x <= ret.min.x))
		{
			ret.min.x = inputPoints[i].x;
		}
		if (inputPoints[i].y <= ret.min.y)
		{
			ret.min.y = inputPoints[i].y;
		}
	}

	for (int i = 0; i < inputPoints.size(); i++)
	{
		if ((inputPoints[i].x >= ret.max.x))
		{
			ret.max.x = inputPoints[i].x;
		}
		if (inputPoints[i].y >= ret.max.y)
		{
			ret.max.y = inputPoints[i].y;
		}
	}
	return ret;
}

/**
 * @brief Constructs a bounding circle from the provided points.
 * @param[in] inputPoints List of points
 * @return Bounding circle of the provided points
 */
Circle ConstructBoundingCircle(const std::vector<Point>& inputPoints) {
	Circle ret = {};

	// TODO: Implement
	AABB minmax = ConstructAABB(inputPoints);
	Point midPoint;
	ret.center.x = (minmax.min.x + minmax.max.x) / 2;
	ret.center.y = (minmax.min.y + minmax.max.y) / 2;

	ret.radius = 0;

	for (int i = 0; i < inputPoints.size(); i++)
	{
		Point checkingPoint = inputPoints[i];
		float checkRadius = sqrt(pow(checkingPoint.x - ret.center.x, 2) + pow(checkingPoint.y - ret.center.y, 2));
		if (checkRadius >= ret.radius)
		{
			ret.radius = checkRadius;
		}
	}

	return ret;
}

//https://math.stackexchange.com/questions/2121112/how-do-i-visualize-if-three-points-represent-a-right-or-left-turn
bool rightTurn(const Point& pointA, const Point& pointB, const Point& pointC)
{
	return (((pointC.x - pointA.x) * (pointB.y - pointA.y) - (pointC.y - pointA.y) * (pointB.x - pointA.x)) > 0);
}

/**
 * @brief Constructs a convex hull from the specified input points.
 * @param[in] inputPoints Input points
 * @param[out] outputPoints Points that are part of the convex hull of the input list of points
 */
//https://github.com/rafael-plaza/ConvexHull/blob/master/main.cpp
//https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
//https://sites.google.com/site/indy256/algo_cpp/convex_hull
void ConstructConvexHull(const std::vector<Point>& inputPoints, std::vector<Point>& outputPoints) {
	// TODO: Implement code for constructing the convex hull of the given points.
	// outputPoints is passed by reference, so you cna directly add the points in the convex hull to outputPoints
	// (i.e., no need to return a new vector containing the points in the convex hull)
	std::vector<Point> upperHull;
	std::vector<Point> lowerHull;
	std::vector<Point> sortInputs = inputPoints;

	sort(sortInputs.begin(), sortInputs.end());
	
	upperHull.push_back(sortInputs[0]);
	upperHull.push_back(sortInputs[1]);
	for (int i = 2; i < sortInputs.size(); i++)
	{
		Point pointA = upperHull[upperHull.size() - 2];
		Point pointB = upperHull[upperHull.size() - 1];
		Point pointC = sortInputs[i];
		while (upperHull.size() > 1 && !rightTurn(pointA, pointB, pointC))
		{
			upperHull.pop_back();
			pointA = upperHull[upperHull.size() - 2];
			pointB = upperHull[upperHull.size() - 1];
			pointC = sortInputs[i];
		}
		upperHull.push_back(sortInputs[i]);
	}
	for (int i = 0; i < upperHull.size(); i++)
	{
		outputPoints.push_back(upperHull[i]);
	}

	lowerHull.push_back(sortInputs[sortInputs.size() - 1]);
	lowerHull.push_back(sortInputs[sortInputs.size() - 2]);
	for (int i = 2; i < sortInputs.size(); i++)
	{
		Point pointA = lowerHull[lowerHull.size() - 2];
		Point pointB = lowerHull[lowerHull.size() - 1];
		Point pointC = sortInputs[sortInputs.size() - i - 1];
		while (lowerHull.size() > 1 && !rightTurn(pointA, pointB, pointC))
		{
			lowerHull.pop_back();
			pointA = lowerHull[lowerHull.size() - 2];
			pointB = lowerHull[lowerHull.size() - 1];
			pointC = sortInputs[sortInputs.size() - i - 1];
		}
		lowerHull.push_back(sortInputs[sortInputs.size() - i - 1]);
	}
	for (int i = 0; i < lowerHull.size(); i++)
	{
		outputPoints.push_back(lowerHull[i]);
	}
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
	GLuint vbo;
	std::vector<Point> points;
	size_t numVertices;
};
struct Vertex {
	GLfloat x, y, z;
	GLfloat r, g, b;
};
struct Matrix4x4 {
	GLfloat values[16];
};

void RefreshScene(AppData* data);

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

void GeneratePoints(const int& numPoints, std::vector<Point>& points) {
	points.clear();

	static std::random_device randDevice;
	std::default_random_engine randEngine(randDevice());

	float xOffset = 80.0f;
	float yOffset = 60.0f;
	for (int i = 0; i < numPoints; ++i)
	{
		std::uniform_real_distribution<float> r(0.0f, 1.0f);
		float x = xOffset + (WINDOW_WIDTH - xOffset * 2) * r(randEngine);
		float y = yOffset + (WINDOW_HEIGHT - yOffset * 2) * r(randEngine);

		points.push_back({x, y});
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	AppData* appData = reinterpret_cast<AppData*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_SPACE) {
			appData->points.clear();
			GeneratePoints(100, appData->points);	
		}
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

void AppendLineVertices(const Point& p0, const Point& p1, float width, std::vector<Vertex>& vertices, float zOrder = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
	float vx = p1.x - p0.x, vy = p1.y - p0.y;
	float vm = vx * vx + vy * vy;
	if (fabsf(vm) > 1e-9f) {
		vm = sqrtf(vm);
		vx = vx / vm; vy = vy / vm;
	}
	float nx = -vy, ny = vx;

	Vertex v0 = { p0.x + nx * width / 2.0f, p0.y + ny * width / 2.0f, zOrder, r, g, b };
	Vertex v1 = { p0.x - nx * width / 2.0f, p0.y - ny * width / 2.0f, zOrder, r, g, b };
	Vertex v2 = { p1.x - nx * width / 2.0f, p1.y - ny * width / 2.0f, zOrder, r, g, b };
	Vertex v3 = { p1.x + nx * width / 2.0f, p1.y + ny * width / 2.0f, zOrder, r, g, b };

	vertices.push_back( v0 ); vertices.push_back( v1 ); vertices.push_back( v2 );
	vertices.push_back( v2 ); vertices.push_back( v3 ); vertices.push_back( v0 );
}

void AppendCircleVertices(const Point& center, float radius, std::vector<Vertex>& vertices, float zOrder = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
	int numSections = 180;
	float anglePerSection = 360.0f / numSections * M_PI / 180.0f;
	for (int i = 1; i <= numSections; ++i) {
		float x0 = center.x + radius * cosf(anglePerSection * (i - 1));
		float y0 = center.y + radius * sinf(anglePerSection * (i - 1));
		float x1 = center.x + radius * cosf(anglePerSection * i);
		float y1 = center.y + radius * sinf(anglePerSection * i);
		vertices.push_back( { center.x, center.y, zOrder, r, g, b } );
		vertices.push_back( { x0, y0, zOrder, r, g, b } );
		vertices.push_back( { x1, y1, zOrder, r, g, b } );
	}
}

void RefreshScene(AppData* data) {
	std::vector<Vertex> vertices;

	// Points
	for (size_t i = 0; i < data->points.size(); ++i) {
		AppendCircleVertices( data->points[i], 4.0f, vertices );
	}

	// Bounding box
	AABB boundingBox = ConstructAABB(data->points);
	Point lowerLeft = boundingBox.min, lowerRight = { boundingBox.max.x, boundingBox.min.y }, upperRight = boundingBox.max, upperLeft = { boundingBox.min.x, boundingBox.max.y };
	AppendLineVertices(lowerLeft, lowerRight, 2.0f, vertices, 0.0f, 1.0f, 0.0f, 0.0f);
	AppendLineVertices(lowerRight, upperRight, 2.0f, vertices, 0.0f, 1.0f, 0.0f, 0.0f);
	AppendLineVertices(upperRight, upperLeft, 2.0f, vertices, 0.0f, 1.0f, 0.0f, 0.0f);
	AppendLineVertices(upperLeft, lowerLeft, 2.0f, vertices, 0.0f, 1.0f, 0.0f, 0.0f);

	// Bounding circle
	Circle boundingCircle = ConstructBoundingCircle(data->points);

	int numSections = 180;
	float anglePerSection = (360.0f / numSections) * M_PI / 180.0f;
	for (int i = 1; i <= numSections; ++i)
	{
		float x0 = boundingCircle.radius * cosf(anglePerSection * (i - 1));
		float y0 = boundingCircle.radius * sinf(anglePerSection * (i - 1));
		float x1 = boundingCircle.radius * cosf(anglePerSection * i);
		float y1 = boundingCircle.radius * sinf(anglePerSection * i);

		AppendLineVertices({ boundingCircle.center.x + x0, boundingCircle.center.y + y0 }, { boundingCircle.center.x + x1, boundingCircle.center.y + y1 }, 2.0f, vertices, 0.0f, 0.0f, 1.0f, 0.0f);
	}

	// Convex hull
	std::vector<Point> convexHull;
	ConstructConvexHull(data->points, convexHull);
	for (size_t i = 0; i < convexHull.size(); ++i) {
		AppendLineVertices(convexHull[i], convexHull[(i + 1) % convexHull.size()], 2.0f, vertices, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	data->numVertices = vertices.size();
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	AppData appData = {};

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

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bounding Regions", nullptr, nullptr);
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

	GeneratePoints(100, appData.points);
	RefreshScene(&appData);

	Matrix4x4 projMatrix = CreateOrtho(0.0f, WINDOW_WIDTH * 1.0f, 0.0f, WINDOW_HEIGHT * 1.0f, -100.0f, 100.0f);
	float prevTime = glfwGetTime(), speed = 200.0f;
	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - prevTime;
		prevTime = currentTime;

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
