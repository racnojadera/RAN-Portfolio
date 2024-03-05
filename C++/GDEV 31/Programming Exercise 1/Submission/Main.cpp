#include <iostream>
#include <cmath>

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
	
	/**
	 * Task 1: negative() member function
	 */
	 Vector3 negative()
	 {
		 Vector3 Negative(x*(-1.0f),y*(-1.0f),z*(-1.0f));
		 return Negative;
	 }
	
	/**
	 * Task 2: magnitude() member function
	 */
	float magnitude()
	{
		float Magnitude = sqrt(x*x + y*y + z*z);
		return Magnitude;
	}
	 
	/**
	 * Task 3: squaredMagnitude() member function
	 */
	float squaredMagnitude()
	{
		float SquaredMagnitude = x*x + y*y + z*z;
		return SquaredMagnitude;
	}
	
	/**
	 * Task 4: normalized() member function
	 */
	Vector3 normalized()
	{
		Vector3 original(x,y,z);
		float Magnitude = original.magnitude();

		if (Magnitude > 0)
		{
			Vector3 NormalizedVector(x/Magnitude, y/Magnitude, z/Magnitude);
			return NormalizedVector;
		}
		Vector3 ret;
		return ret;
	}

	/**
	 * Task 5: add() static member function
	 */
	static Vector3 add(Vector3 a, Vector3 b)
	{
		Vector3 Sum(a.x+b.x, a.y+b.y, a.z+b.z);
		return Sum;
	}
	
	/**
	 * Task 6: subtract() static member function
	 */
	static Vector3 subtract(Vector3 a, Vector3 b)
	{
		Vector3 Difference(a.x-b.x, a.y-b.y, a.z-b.z);
		return Difference;
	}

	/**
	 * Task 7: multiply() static member function
	 */
	static Vector3 multiply(Vector3 a, float s)
	{
		Vector3 Product(a.x*s, a.y*s, a.z*s);
		return Product;
	}
	
	/**
	 * Task 8: dot() static member function
	 */
	static float dot(Vector3 a, Vector3 b)
	{
		float dotProduct = a.x*b.x + a.y*b.y + a.z*b.z;
		return dotProduct;
	}

	/**
	 * Task 9: cross() static member function
	 */
	static Vector3 cross(Vector3 a, Vector3 b)
	{
		Vector3 CrossProduct((a.y*b.z-a.z*b.y), (a.z*b.x - a.x*b.z), (a.x*b.y - a.y*b.x));
		return CrossProduct;
	}
	
	/**
	 * Task 10: project() static member function
	 */
	static Vector3 project(Vector3 a, Vector3 b)
	{
		float MagnitudeB = b.magnitude();
		float DotAB = Vector3::dot(a, b);
		float ScalarMagDot = DotAB/pow(MagnitudeB,2);
		Vector3 Projection(ScalarMagDot*b.x, ScalarMagDot*b.y, ScalarMagDot*b.z);
		return Projection;
	}


	/**
	 * Task 11: reflect() static member function
	 */
	static Vector3 reflect(Vector3 a, Vector3 b)
	{
		Vector3 ProjectionAB = Vector3::project(a,b);
		Vector3 Reflection((a.x-2*ProjectionAB.x), (a.y-2*ProjectionAB.y), (a.z-2*ProjectionAB.z));
		return Reflection;
	}
};

int main()
{
	/**
	 * Task 12: Read input from standard input, and output
	 * to standard output based on the sample output.
	 */
	 Vector3 A, B;
	 float S;
	 std::cin >> A.x >> A.y >> A.z >> B.x >> B.y >> B.z >> S;



	 Vector3 NegativeA = A.negative(); //task 1
	 Vector3 NegativeB = B.negative(); //task 1
	 float MagnitudeA = A.magnitude(); //task 2
	 float MagnitudeB = B.magnitude(); //task 2
	 float SquaredMagnitudeA = A.squaredMagnitude(); //task 3
	 float SquaredMagnitudeB = B.squaredMagnitude(); //task 3
	 Vector3 NormalizedA = A.normalized(); //task 4
	 Vector3 NormalizedB = B.normalized(); //task 4
	 Vector3 SumOfAB = Vector3::add(A, B); //task 5
	 Vector3 DifferenceOfAB = Vector3::subtract(A, B); //task 6
	 Vector3 ProductOfAS = Vector3::multiply(A, S); //task 7
	 float DotProductAB = Vector3::dot(A, B); //task 8
	 Vector3 CrossProductAB = Vector3::cross(A, B); //task 9
	 Vector3 ProjectionAB = Vector3::project(A, B); //task 10
	 Vector3 ReflectionAB = Vector3::reflect(A, B); //task 11



	//task 12
	 std::cout << "A = (" << A.x << ", " << A.y << ", " << A.z << ")" << std::endl;
	 std::cout << "B = (" << B.x << ", " << B.y << ", " << B.z << ")" << std::endl;
	 std::cout << "S = " << S << std::endl;
	 std::cout << "-A = (" << NegativeA.x << ", " << NegativeA.y << ", " << NegativeA.z << ")" << std::endl;
	 std::cout << "-B = (" << NegativeB.x << ", " << NegativeB.y << ", " << NegativeB.z << ")" << std::endl;
	 std::cout << "Squared magnitude of A = " << SquaredMagnitudeA << std::endl;
	 std::cout << "Magnitude of A " << MagnitudeA << std::endl;
	 std::cout << "Squared magnitude of B = " << SquaredMagnitudeB << std::endl;
	 std::cout << "Magnitude of B " << MagnitudeB << std::endl;
	 std::cout << "A normalized = (" << NormalizedA.x << ", " << NormalizedA.y << ", " << NormalizedA.z <<")" << std::endl;
	 std::cout << "B normalized = (" << NormalizedB.x << ", " << NormalizedB.y << ", " << NormalizedB.z <<")" << std::endl;
	 std::cout << "A + B = (" << SumOfAB.x << ", " << SumOfAB.y << ", " << SumOfAB.z << ")" << std::endl;
	 std::cout << "A - B = (" << DifferenceOfAB.x << ", " << DifferenceOfAB.y << ", " << DifferenceOfAB.z << ")" << std::endl;
	 std::cout << "A * S = (" << ProductOfAS.x << ", " << ProductOfAS.y << ", " << ProductOfAS.z << ")" << std::endl;
	 std::cout << "A dot B = " << DotProductAB << std::endl;
	 std::cout << "A cross B = (" << CrossProductAB.x << ", " << CrossProductAB.y << ", " << CrossProductAB.z << ")" << std::endl;
	 std::cout << "Projection of A onto B = (" << ProjectionAB.x << ", " << ProjectionAB.y << ", " << ProjectionAB.z << ")" << std::endl;
	 std::cout << "Reflection of A along B = (" << ReflectionAB.x << ", " << ReflectionAB.y << ", " << ReflectionAB.z << ")" << std::endl;

	return 0;
}

