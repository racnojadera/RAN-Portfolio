#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

const float ANGLE_INCREMENT = 1.0f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// TODO: Task 1

/**
 * Struct containing data for a 3D vector
 */
struct Vector3
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
	 * Z component
	 */
	float z;

	/**
	 * Constructor
	 * @param newX - New x component
	 * @param newY - New y component
	 * @param newZ - New z component
	 */
	Vector3(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	/**
	 * Constructor
	 */
	Vector3()
		: Vector3(0.0f, 0.0f, 0.0f)
	{
	}

	Vector3 negative()
	{
		Vector3 Negative(x * (-1.0f), y * (-1.0f), z * (-1.0f));
		return Negative;
	}

	float magnitude()
	{
		float Magnitude = sqrt(x * x + y * y + z * z);
		return Magnitude;
	}

	float squaredMagnitude()
	{
		float SquaredMagnitude = x * x + y * y + z * z;
		return SquaredMagnitude;
	}

	Vector3 normalized()
	{
		Vector3 original(x, y, z);
		float Magnitude = original.magnitude();

		if (Magnitude > 0)
		{
			Vector3 NormalizedVector(x / Magnitude, y / Magnitude, z / Magnitude);
			return NormalizedVector;
		}
		Vector3 ret(0,0,0);
		return ret;
	}

	static Vector3 add(Vector3 a, Vector3 b)
	{
		Vector3 Sum(a.x + b.x, a.y + b.y, a.z + b.z);
		return Sum;
	}

	static Vector3 subtract(Vector3 a, Vector3 b)
	{
		Vector3 Difference(a.x - b.x, a.y - b.y, a.z - b.z);
		return Difference;
	}

	static Vector3 multiply(Vector3 a, float s)
	{
		Vector3 Product(a.x * s, a.y * s, a.z * s);
		return Product;
	}

	static float dot(Vector3 a, Vector3 b)
	{
		float dotProduct = a.x * b.x + a.y * b.y + a.z * b.z;
		return dotProduct;
	}

	static Vector3 cross(Vector3 a, Vector3 b)
	{
		Vector3 CrossProduct((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
		return CrossProduct;
	}

	static Vector3 project(Vector3 a, Vector3 b)
	{
		float MagnitudeB = b.magnitude();
		float DotAB = Vector3::dot(a, b);
		float ScalarMagDot = DotAB / pow(MagnitudeB, 2);
		Vector3 Projection(ScalarMagDot * b.x, ScalarMagDot * b.y, ScalarMagDot * b.z);
		return Projection;
	}

	static Vector3 reflect(Vector3 a, Vector3 b)
	{
		Vector3 ProjectionAB = Vector3::project(a, b);
		Vector3 Reflection((a.x - 2 * ProjectionAB.x), (a.y - 2 * ProjectionAB.y), (a.z - 2 * ProjectionAB.z));
		return Reflection;
	}
};

/**
 * Quaternion struct
 */
struct Quaternion
{
	/**
	 * Scalar part
	 */
	float s;

	/**
	 * Vector part
	 */
	Vector3 v;

	/**
	 * Constructor
	 * @param S - New scalar component
	 * @param X - New value for the vector part's x-component
	 * @param Y - New value for the vector part's y-component
	 * @param Z - New value for the vector part's z-component
	 */
	Quaternion(float S, float X, float Y, float Z)
		: s(S), v(X, Y, Z)
	{
	}

	/**
	 * Constructor
	 * @param S - New scalar component
	 * @param V - New vector component
	 */
	Quaternion(float S, const Vector3& V)
		: s(S), v(V)
	{
	}

	/**
	 * Constructor
	 */
	Quaternion()
		: Quaternion(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	/**
	 * Copy constructor
	 */
	Quaternion(const Quaternion& other)
		: Quaternion(other.s, other.v)
	{
	}

	/**
	 * Adds the two quaternions provided (a + b)
	 */
	static Quaternion add(const Quaternion& a, const Quaternion& b)
	{
		// TODO: Task 3
		Quaternion QuaternionAdd((a.s+b.s), Vector3::add(a.v,b.v));
		return QuaternionAdd;
	}

	/**
	 * Subtracts the two quaternions (a - b)
	 */
	static Quaternion subtract(const Quaternion& a, const Quaternion& b)
	{
		// TODO: Task 4
		Quaternion QuaternionSubtract((a.s-b.s), Vector3::subtract(a.v,b.v));
		return QuaternionSubtract;
	}

	/**
	 * Multiplies a quaternion by a scalar
	 */
	static Quaternion multiply(const Quaternion& q, float s)
	{
		// TODO: Task 5
		Quaternion QuaternionMultiply(q.s*s, Vector3::multiply(q.v, s));
		return QuaternionMultiply;
	}

	/**
	 * Multiplies the two quaternions (ab)
	 */
	static Quaternion multiply(const Quaternion& a, const Quaternion& b)
	{
		// TODO: Task 6
		float QSComponent = (a.s * b.s) - Vector3::dot(a.v, b.v);
		Vector3 QVComponent1 = Vector3::multiply(b.v, a.s);
		Vector3 QVComponent2 = Vector3::multiply(a.v, b.s);
		Vector3 QVComponent3 = Vector3::cross(a.v, b.v);
		Vector3 QVComponent12 = Vector3::add(QVComponent1, QVComponent2);
		Vector3 QVComponent123 = Vector3::add(QVComponent12, QVComponent3);
		Quaternion QuaternionMultiply(QSComponent, QVComponent123);
		return QuaternionMultiply;
	}

	/**
	 * Returns the negative of this quaternion
	 */
	Quaternion negative()
	{
		// TODO: Task 7
		Quaternion QuaternionNegative((-1)*s, v.negative());
		return QuaternionNegative;
	}

	/**
	 * Returns the conjugate of this quaternion
	 */
	Quaternion conjugate()
	{
		// TODO: Task 8
		Quaternion QuaternionConjugate(s, v.negative());
		return QuaternionConjugate;
	}

	/**
	 * Returns the squared magnitude of this quaternion
	 */
	float squaredMagnitude()
	{
		// TODO: Task 9
		float QSComponent = pow(s, 2) + Vector3::dot(v, v);
		return QSComponent;
	}

	/**
	 * Returns the magnitude of this quaternion
	 */
	float magnitude()
	{
		// TODO: Task 10
		float QuaternionMagnitude = sqrt(squaredMagnitude());
		return QuaternionMagnitude;
	}

	/**
	 * Returns the normalized version of this quaternion
	 */
	Quaternion normalized()
	{
		// TODO: Task 11
		Quaternion QuaternionNormalized(s/magnitude(), Vector3::multiply(v, 1/magnitude()));
		return QuaternionNormalized;
	}

	/**
	 * Returns the inverse of this quaternion
	 */
	Quaternion inverse()
	{
		// TODO: Task 12
		Quaternion QuaternionInverse(conjugate().s/squaredMagnitude(), Vector3::multiply(conjugate().v, 1/squaredMagnitude())); //notnegative, fix
		return QuaternionInverse;
	}

	/**
	 * Returns the dot product between two quaternions (a dot b)
	 */
	static float dot(const Quaternion& a, const Quaternion& b)
	{
		// TODO: Task 13
		float QSComponent = a.s*b.s;
		float QVComponent = Vector3::dot(a.v, b.v);
		return QSComponent+QVComponent;
	}

	/**
	 * Returns a formatted string showing the components of this quaternion.
	 * Format: [s, (x, y, z)]
	 */
	std::string toString()
	{
		std::ostringstream ret;
		ret << "[" << s << ", (" << v.x << ", " << v.y << ", " << v.z << ")]";
		return ret.str();
	}
};

/**
 * Rotates a vector by the specified angle along the specified axis of rotation
 * @param v - Vector to rotate
 * @param rotationAxis - Axis of rotation
 * @param angleInDegrees - Rotation amount (in degrees)
 */
Vector3 rotateVector(const Vector3& v, const Vector3& rotationAxis, float angleInDegrees)
{
	// TODO: Task 14
	Quaternion TransformedVector(0, v);
	float RQSComponent = cos(angleInDegrees * (M_PI / 180) /2); //https://www.cplusplus.com/reference/cmath/sin/, https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c 
	Vector3 RQVComponent = Vector3::multiply(rotationAxis, sin(angleInDegrees*(M_PI / 180)/2));
	Quaternion RotationQuaternion(RQSComponent, RQVComponent);
	Quaternion Resultant1(Quaternion::multiply(RotationQuaternion, TransformedVector));
	Quaternion Resultant2(Quaternion::multiply(Resultant1, RotationQuaternion.inverse()));
	return Resultant2.v;
}

/**
 * Struct that contains the values of the two quaternions that
 * will be used to check the different operations (add, subtract, etc.)
 */
struct QuaternionOperationTestCase
{
	Quaternion a;
	Quaternion b;
};

/**
 * Struct that contains the values of the axis of rotation and the rotation angle
 * for the interactive rotation tests
 */
struct CubeRotationTestCase
{
	Vector3 axisOfRotation;
	float angleInDegrees;
};

// List of test cases for the quaternion operations check.
// Feel free to add more test cases here.
std::vector<QuaternionOperationTestCase> quaternionTestCases =
{
	// { First quaternion, Second quaternion }
	{ Quaternion(1.0f, 1.0f, 1.0f, 1.0f), Quaternion(2.0f, 3.0f, 1.0f, -5.0f) },
	{ Quaternion(0.0f, 1.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 1.0f, 0.0f) },
};

// List of test caess for the interactive rotation test.
// Feel free to add more test cases here.
std::vector<CubeRotationTestCase> cubeRotationTestCases =
{
	// { Axis of rotation, angle in degrees }
	{ Vector3(0.0f, 1.0f, 0.0f), 0.0f },
	{ Vector3(1.0f, 0.0f, 0.0f), 90.0f },
	{ Vector3(1.0f, 1.0f, 0.0f), 45.0f },
	{ Vector3(0.0f, 1.0f, 1.0f), -120.0f },
};

// ----------------------------------------------------------------------------------
// DO NOT TOUCH ANY CODE BEYOND THIS POINT
// ----------------------------------------------------------------------------------

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

struct Vertex
{
	GLfloat x, y, z;
	GLfloat r, g, b;
};

struct Matrix4x4
{
	GLfloat values[16];

	Matrix4x4()
	{
		memset(values, 0, sizeof(GLfloat) * 16);
	}

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="other">Other matrix whose values we are copying</param>
	Matrix4x4(const Matrix4x4& other)
	{
		memcpy(values, other.values, sizeof(GLfloat) * 16);
	}

	/// <summary>
	/// Assignment operator
	/// </summary>
	/// <param name="other">Matrix we are equating to</param>
	void operator=(const Matrix4x4& other)
	{
		memcpy(values, other.values, sizeof(GLfloat) * 16);
	}
};

Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
{
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

Vector3 operator*(const Matrix4x4& a, const Vector3& b)
{
	// For now, just assume that the other vector is a point, not a direction
	float bw = 0.0f;

	Vector3 ret;

	ret.x = a.values[0] * b.x + a.values[4] * b.y + a.values[8] * b.z + a.values[12] * bw;
	ret.y = a.values[1] * b.x + a.values[5] * b.y + a.values[9] * b.z + a.values[13] * bw;
	ret.z = a.values[2] * b.x + a.values[6] * b.y + a.values[10] * b.z + a.values[14] * bw;
	float w = ret.y = a.values[3] * b.x + a.values[7] * b.y + a.values[11] * b.z + a.values[15] * bw;

	if (bw > 0.0f)
	{
		ret.x /= w;
		ret.y /= w;
		ret.z /= w;
	}
	
	return ret;
}

/**
 * Reads the contents of the file specified by the file path,
 * and places the file contents into a string.
 * @param	filePath		Path of the file to read
 * @param	outputString	String where the file contents will be copied to
 * @return	Returns true if the file was successfully read or not.
 */
bool ReadFile(const std::string& filePath, std::string& outputString)
{
	std::ifstream file(filePath);
	if (file.fail())
	{
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		outputString += line + "\n";
	}

	return true;
}

/**
 * Creates a shader object given the shader type and the corresponding shader source
 * @param	type	Shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...)
 * @param	source	Shader source (as string)
 * @return	Returns the handle to the shader object
 */
GLuint CreateShader(const GLuint& type, const std::string& source)
{
	// Create the shader object of the given type
	GLuint shader = glCreateShader(type);

	// Compile the shader source
	const char* sourceCStr = source.c_str();
	GLint sourceLen = source.size();
	glShaderSource(shader, 1, &sourceCStr, &sourceLen);
	glCompileShader(shader);

	// Check compilation status
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, infoLog);

		std::string errorMsg;

		if (type == GL_VERTEX_SHADER)
		{
			errorMsg += std::string("Failed to compile vertex shader!\n");
		}
		else if (type == GL_FRAGMENT_SHADER)
		{
			errorMsg += std::string("Failed to compile fragment shader!\n");
		}
		else
		{
			errorMsg += std::string("Failed to compile shader!\n");
		}
		errorMsg += std::string(infoLog);

		std::cout << errorMsg << std::endl;
	}

	return shader;
}

GLuint CreateShaderProgramFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	// Create the vertex and fragment shader objects
	GLuint vsh = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fsh = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// Create a shader program object
	GLuint program = glCreateProgram();

	// Attach the vertex and fragment shaders to the program
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);

	// Link all attached shaders
	glLinkProgram(program);

	// Check shader program link status
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		char infoLog[512];
		GLsizei infoLogLen = sizeof(infoLog);
		glGetProgramInfoLog(program, infoLogLen, &infoLogLen, infoLog);
		throw std::runtime_error(std::string("program link error: ") + infoLog);
		return 0;
	}

	// Detach the vertex and fragment shaders from the program,
	// since they've already been linked and we don't need them anymore.
	glDetachShader(program, vsh);
	glDetachShader(program, fsh);

	// Delete the vertex and fragment shader objects
	glDeleteShader(vsh);
	glDeleteShader(fsh);

	return program;
}

size_t testCaseNumber = 0;

Vector3 axisOfRotation(0.0f, 0.0f, 0.0f);
float angleInDegrees = 0.0f;

void printCurrentTestCaseInfo()
{
	std::cout << "Test case " << testCaseNumber << " | ";
	std::cout << "Axis: (" << axisOfRotation.x << ", " << axisOfRotation.y << ", " << axisOfRotation.z << ") | ";
	std::cout << "Angle: " << angleInDegrees << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS))
	{
		testCaseNumber = ((testCaseNumber - 1) + cubeRotationTestCases.size()) % cubeRotationTestCases.size();
		axisOfRotation = cubeRotationTestCases[testCaseNumber].axisOfRotation;
		angleInDegrees = cubeRotationTestCases[testCaseNumber].angleInDegrees;
		printCurrentTestCaseInfo();
	}
	else if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS))
	{
		testCaseNumber = (testCaseNumber + 1) % cubeRotationTestCases.size();
		axisOfRotation = cubeRotationTestCases[testCaseNumber].axisOfRotation;
		angleInDegrees = cubeRotationTestCases[testCaseNumber].angleInDegrees;
		printCurrentTestCaseInfo();
	}
	else if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
	{
		angleInDegrees = cubeRotationTestCases[testCaseNumber].angleInDegrees;
		printCurrentTestCaseInfo();
	}
	else if ((key == GLFW_KEY_A) && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleInDegrees -= ANGLE_INCREMENT;
		printCurrentTestCaseInfo();
	}
	else if ((key == GLFW_KEY_D) && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleInDegrees += ANGLE_INCREMENT;
		printCurrentTestCaseInfo();
	}
}

Matrix4x4 CreateIdentity()
{
	Matrix4x4 ret;
	ret.values[0] = 1.0f;
	ret.values[5] = 1.0f;
	ret.values[10] = 1.0f;
	ret.values[15] = 1.0f;
	return ret;
}

Matrix4x4 CreatePersp(float fovInDegrees, float width, float height, float near, float far)
{
	Matrix4x4 ret;

	float fovRadians = fovInDegrees * M_PI / 180.0f;
	float aspectRatio = width / height;

	ret.values[0] = 1.0f / (aspectRatio * tanf(fovRadians / 2.0f));
	ret.values[1] = 0.0f;
	ret.values[2] = 0.0f;
	ret.values[3] = 0.0f;

	ret.values[4] = 0.0f;
	ret.values[5] = 1.0f / tanf(fovRadians / 2.0f);
	ret.values[6] = 0.0f;
	ret.values[7] = 0.0f;
	
	ret.values[8] = 0.0f;
	ret.values[9] = 0.0f;
	ret.values[10] = -(far + near) / (far - near);
	ret.values[11] = -1.0f;

	ret.values[12] = 0.0f;
	ret.values[13] = 0.0f;
	ret.values[14] = 2.0f * far * near / (far - near);
	ret.values[15] = 0.0f;

	return ret;
}

Matrix4x4 CreateTranslation(GLfloat tx, GLfloat ty, GLfloat tz)
{
	Matrix4x4 ret = CreateIdentity();
	ret.values[12] = tx;
	ret.values[13] = ty;
	ret.values[14] = tz;
	ret.values[15] = 1.0f;

	return ret;
}

void performTest(Quaternion& a, Quaternion& b)
{
	std::cout << "a = " << a.toString() << ", b = " << b.toString() << std::endl;
	std::cout << "a + b = " << Quaternion::add(a, b).toString() << ", a - b = " << Quaternion::subtract(a, b).toString() << std::endl;
	std::cout << "ab = " << Quaternion::multiply(a, b).toString() << ", ba = " << Quaternion::multiply(b, a).toString() << std::endl;
	std::cout << "conjugate(a) = " << a.conjugate().toString() << ", conjugate(b) = " << b.conjugate().toString() << std::endl;
	std::cout << "norm(a) = " << a.magnitude() << ", norm(b) = " << b.magnitude() << std::endl;
	std::cout << "inverse(a) = " << a.inverse().toString() << ", inverse(b) = " << b.inverse().toString() << std::endl;
	std::cout << "a dot b = " << Quaternion::dot(a, b) << std::endl;
}

int main()
{
	if (quaternionTestCases.size() == 0)
	{
		std::cout << "Warning: No test cases set for checking quaternion operations..." << std::endl;
	}

	for (size_t i = 0; i < quaternionTestCases.size(); ++i)
	{
		if (i > 0)
		{
			std::cout << "===============" << std::endl;
		}

		performTest(quaternionTestCases[i].a, quaternionTestCases[i].b);
	}

	std::cout << std::endl << "--------------------------------------" << std::endl;
	printCurrentTestCaseInfo();

	if (cubeRotationTestCases.size() == 0)
	{
		std::cout << "No test cases found! Adding a default test case..." << std::endl;
		cubeRotationTestCases.push_back({ Vector3(0.0f, 1.0f, 0.0f), 90.0f });
	}

	testCaseNumber = 0;
	axisOfRotation = cubeRotationTestCases[0].axisOfRotation;
	angleInDegrees = cubeRotationTestCases[0].angleInDegrees;

	// Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "Cannot initialize GLFW!" << std::endl;
		return -1;
	}

	// Tell GLFW to use opengl without the deprecated functions (core profile, forward compatible)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Tell GLFW to use OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Set window to be not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Quaternions Exercise", nullptr, nullptr);

	// Check window validity
	if (!window)
	{
		std::cerr << "Cannot create window.";
		return -1;
	}

	// Make the current window as the current context for OpenGL
	glfwMakeContextCurrent(window);

	// Load OpenGL extensions via GLAD
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Set glfw key callback
	glfwSetKeyCallback(window, KeyCallback);

	Vertex vertices[] =
	{
		{ -0.5f, -0.5f, 0.5f, 1, 0, 0 },
		{ 0.5f, -0.5f, 0.5f, 1, 0, 0 },
		{ 0.5f, 0.5f, 0.5f, 1, 0, 0 },
		{ 0.5f, 0.5f, 0.5f, 1, 0, 0 },
		{ -0.5f, 0.5f, 0.5f, 1, 0, 0 },
		{ -0.5f, -0.5f, 0.5f, 1, 0, 0 },

		{ 0.5f, -0.5f, -0.5f, 0, 1, 0 },
		{ -0.5f, -0.5f, -0.5f, 0, 1, 0 },
		{ -0.5f, 0.5f, -0.5f, 0, 1, 0 },
		{ -0.5f, 0.5f, -0.5f, 0, 1, 0 },
		{ 0.5f, 0.5f, -0.5f, 0, 1, 0 },
		{ 0.5f, -0.5f, -0.5f, 0, 1, 0 },

		{ -0.5f, -0.5f, -0.5f, 0, 0, 1 },
		{ -0.5f, -0.5f, 0.5f, 0, 0, 1 },
		{ -0.5f, 0.5f, 0.5f, 0, 0, 1 },
		{ -0.5f, 0.5f, 0.5f, 0, 0, 1 },
		{ -0.5f, 0.5f, -0.5f, 0, 0, 1 },
		{ -0.5f, -0.5f, -0.5f, 0, 0, 1 },

		{ 0.5f, -0.5f, 0.5f, 1, 0, 1 },
		{ 0.5f, -0.5f, -0.5f, 1, 0, 1 },
		{ 0.5f, 0.5f, -0.5f, 1, 0, 1 },
		{ 0.5f, 0.5f, -0.5f, 1, 0, 1 },
		{ 0.5f, 0.5f, 0.5f, 1, 0, 1 },
		{ 0.5f, -0.5f, 0.5f, 1, 0, 1 },

		{ -0.5f, 0.5f, 0.5f, 1, 1, 0 },
		{ 0.5f, 0.5f, 0.5f, 1, 1, 0 },
		{ 0.5f, 0.5f, -0.5f, 1, 1, 0 },
		{ 0.5f, 0.5f, -0.5f, 1, 1, 0 },
		{ -0.5f, 0.5f, -0.5f, 1, 1, 0 },
		{ -0.5f, 0.5f, 0.5f, 1, 1, 0 },

		{ -0.5f, -0.5f, -0.5f, 0, 1, 1 },
		{ 0.5f, -0.5f, -0.5f, 0, 1, 1 },
		{ 0.5f, -0.5f, 0.5f, 0, 1, 1 },
		{ 0.5f, -0.5f, 0.5f, 0, 1, 1 },
		{ -0.5f, -0.5f, 0.5f, 0, 1, 1 },
		{ -0.5f, -0.5f, -0.5f, 0, 1, 1 }
	};

	Vertex verticesCopy[36];

	GLuint vbo, vao;
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, x)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));

	glBindVertexArray(0);

	// Setup shaders
	GLuint program = CreateShaderProgramFromSource(vertShaderSource, fragShaderSource);

	Matrix4x4 projMatrix = CreatePersp(90.0f, WINDOW_WIDTH * 1.0f, WINDOW_HEIGHT * 1.0f, -1.0f, -1000.0f);
	Matrix4x4 viewMatrix = CreateTranslation(0.0f, 0.0f, -2.0f);
	Matrix4x4 mvpMatrix = projMatrix * viewMatrix;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		// Set background color to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		glBindVertexArray(vao);

		for (size_t i = 0; i < 36; ++i)
		{
			verticesCopy[i] = vertices[i];

			Vector3 vertexPosition = Vector3(vertices[i].x, vertices[i].y, vertices[i].z);
			Vector3 rotatedVector = rotateVector(vertexPosition, cubeRotationTestCases[testCaseNumber].axisOfRotation, angleInDegrees);
			verticesCopy[i].x = rotatedVector.x;
			verticesCopy[i].y = rotatedVector.y;
			verticesCopy[i].z = rotatedVector.z;
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesCopy), verticesCopy);

		glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_FALSE, mvpMatrix.values);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Poll pending events
		glfwPollEvents();
	}

	glDeleteProgram(program);
	program = 0;

	glDeleteVertexArrays(1, &vao);
	vao = 0;

	glDeleteBuffers(1, &vbo);
	vbo = 0;

	glfwDestroyWindow(window);
	window = nullptr;

	// Terminate GLFW
	glfwTerminate();

	return 0;
}
