#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

enum class ShapeType
{
	AABB,
	Circle,
	AABBUniform //unigridadd
};

struct Object
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float inverseMass;
	Color color;
	ShapeType shapeType;
	Vector2 size;
};

//unigridadd
struct GridCells
{
	Vector2 minValue;
	Vector2 maxValue;
	std::vector<int> indicesOfObjectsInGrid;
};
//unigridadd

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

Vector2 GetClosestPointToAABB(Vector2 Point, Vector2 aabbMin, Vector2 aabbSize)
{
	Vector2 ret;
	ret.x = Clamp(Point.x, aabbMin.x, aabbMin.x + aabbSize.x);
	ret.y = Clamp(Point.y, aabbMin.y, aabbMin.y + aabbSize.y);
	return ret;
}

float GetImpulse(Vector2 relVelocity, Vector2 colNormal, float invMassA, float invMassB)
{
	float numerator = -2.0f * Vector2DotProduct(relVelocity, colNormal);
	float denominator = Vector2DotProduct(colNormal, colNormal) * (invMassA + invMassB);
	return (numerator / denominator);
}

bool HandleCircleAABBCollision(Object& circle, Object& aabb)
{
	Vector2 Q = GetClosestPointToAABB(circle.position, aabb.position, aabb.size);

	float distSqr = Vector2DistanceSqr(circle.position, Q);
	float radiusSqr = circle.size.x / 2.0f;
	radiusSqr *= radiusSqr;

	if (distSqr <= radiusSqr)
	{
		Vector2 collisionNormal = Vector2Subtract(circle.position, Q);
		Vector2 relativeVelocity = Vector2Subtract(circle.velocity, aabb.velocity);
		float normalRelVelocityDot = Vector2DotProduct(collisionNormal, relativeVelocity);
		if (normalRelVelocityDot < 0.0f)
		{
			float impulse = GetImpulse(relativeVelocity, collisionNormal, circle.inverseMass, aabb.inverseMass);

			circle.velocity = Vector2Add(circle.velocity, Vector2Scale(collisionNormal, impulse * circle.inverseMass));
			aabb.velocity = Vector2Subtract(aabb.velocity, Vector2Scale(collisionNormal, impulse * aabb.inverseMass));
		}
	}
	return false;
}

//unigridadd
bool CheckIfObjInGrid(GridCells& cell, Object& circle)
{
	bool withinX = false, withinY = true;
	Vector2 Q = GetClosestPointToAABB(circle.position, cell.minValue, Vector2Subtract(cell.maxValue, cell.minValue));
	float distSqr = Vector2DistanceSqr(circle.position, Q);
	float radiusSqr = circle.size.x / 2.0f;
	radiusSqr *= radiusSqr;

	if (distSqr <= radiusSqr)
	{
		Vector2 collisionNormal = Vector2Subtract(circle.position, Q);
		Vector2 relativeVelocity = Vector2Subtract(circle.velocity, Vector2Zero());
		float normalRelVelocityDot = Vector2DotProduct(collisionNormal, relativeVelocity);
		if (normalRelVelocityDot < 0.0f)
		{
			return true;
		}
	}
	if ((cell.minValue.x <= circle.position.x) && (cell.maxValue.x >= circle.position.x))
	{
		if ((cell.minValue.y <= circle.position.y) && (cell.maxValue.y >= circle.position.y))
		{
			return true;
		}
	}
	return false;
}
//unigridadd

void HandleCircleCircleCollision(Object& circleA, Object& circleB)
{
	Vector2 collisionNormal = Vector2Subtract(circleA.position, circleB.position);
	float distSqr = Vector2LengthSqr(collisionNormal);

	float radiusA = circleA.size.x / 2.0f, radiusB = circleB.size.x / 2.0f;
	float radiusSqr = (radiusA + radiusB) * (radiusA + radiusB);

	if (distSqr <= radiusSqr)
	{
		Vector2 relativeVelocity = Vector2Subtract(circleA.velocity, circleB.velocity);
		float normalRelVelocityDot = Vector2DotProduct(collisionNormal, relativeVelocity);
		if (normalRelVelocityDot < 0.0f)
		{
			float impulse = GetImpulse(relativeVelocity, collisionNormal, circleA.inverseMass, circleB.inverseMass);

			circleA.velocity = Vector2Add(circleA.velocity, Vector2Scale(collisionNormal, impulse * circleA.inverseMass));
			circleB.velocity = Vector2Subtract(circleB.velocity, Vector2Scale(collisionNormal, impulse * circleB.inverseMass));
		}
	}
}

void HandleCollision(Object& objA, Object& objB)
{
	if ((objA.shapeType == ShapeType::Circle) && (objB.shapeType == ShapeType::Circle))
	{
		HandleCircleCircleCollision(objA, objB);
	}
	else if ((objA.shapeType == ShapeType::Circle) && (objB.shapeType == ShapeType::AABB))
	{
		HandleCircleAABBCollision(objA, objB);
	}
	else if ((objA.shapeType == ShapeType::AABB) && (objB.shapeType == ShapeType::Circle))
	{
		HandleCircleAABBCollision(objB, objA);
	}
}

int main()
{
	int windowWidth = 1280, windowHeight = 720;
	InitWindow(windowWidth, windowHeight, "Homework 4");

	const float FPSCount = 60.0f;
	SetTargetFPS(FPSCount);

	const float timestep = 1.0f / FPSCount;
	float accumulator = 0.0f;

	int spaceInstance = 0;

	std::vector<Object> objects;

	Object verticalWall;
	Object horizontalWall;

	verticalWall.position = Vector2Zero();
	verticalWall.velocity = Vector2Zero();
	verticalWall.mass = 0.0f;
	verticalWall.inverseMass = 0.0f;
	verticalWall.shapeType = ShapeType::AABB;
	verticalWall.size.x = 5.0f;
	verticalWall.size.y = windowHeight;
	verticalWall.color = RED;
	objects.push_back(verticalWall);

	verticalWall.position.x = windowWidth - 5.0f;
	objects.push_back(verticalWall);

	horizontalWall.position = Vector2Zero();
	horizontalWall.velocity = Vector2Zero();
	horizontalWall.mass = 0.0f;
	horizontalWall.inverseMass = 0.0f;
	horizontalWall.shapeType = ShapeType::AABB;
	horizontalWall.size.x = windowWidth;
	horizontalWall.size.y = 5.0f;
	horizontalWall.color = RED;
	objects.push_back(horizontalWall);

	horizontalWall.position.y = windowHeight - 5.0f;
	objects.push_back(horizontalWall);

	//unigridaddition//
	std::vector<GridCells> unigrid;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			GridCells newCell;
			newCell.minValue.x = (windowWidth / 8) * (float)j;
			newCell.minValue.y = (windowHeight / 4) * (float)i;
			newCell.maxValue.x = (windowWidth / 8) * (float)(j + 1);
			newCell.maxValue.y = (windowHeight / 4) * (float)(i + 1);
			unigrid.push_back(newCell);
		}
	}
	//unigridaddition//

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			if (spaceInstance != 10)
			{
				for (int i = 0; i < 25; i++)
				{
					Object newCircle;
					newCircle.position.x = GetRandomValue(40, 1240);
					newCircle.position.y = GetRandomValue(40, 680);
					newCircle.velocity.x = RandomNumber(-100, 100);
					newCircle.velocity.y = RandomNumber(-100, 100);
					newCircle.velocity = Vector2Scale(newCircle.velocity, 5);
					newCircle.mass = 1.0f;
					newCircle.inverseMass = 1.0f / newCircle.mass;
					newCircle.shapeType = ShapeType::Circle;
					newCircle.size.x = GetRandomValue(5, 10);
					newCircle.size.y = newCircle.size.x;
					newCircle.color.r = GetRandomValue(0, 255);
					newCircle.color.g = GetRandomValue(0, 255);
					newCircle.color.b = GetRandomValue(0, 255);
					newCircle.color.a = 255;
					
					objects.push_back(newCircle);
				}
				spaceInstance++;
			}
			else
			{
				Object newCircle;
				newCircle.position.x = GetRandomValue(40, 1240);
				newCircle.position.y = GetRandomValue(40, 680);
				newCircle.velocity.x = RandomNumber(-100, 100);
				newCircle.velocity.y = RandomNumber(-100, 100);
				newCircle.velocity = Vector2Scale(newCircle.velocity, 5);
				newCircle.mass = GetRandomValue(10, 2000);
				newCircle.inverseMass = 1.0f / newCircle.mass;
				newCircle.shapeType = ShapeType::Circle;
				newCircle.size.x = 25;
				newCircle.size.y = newCircle.size.x;
				newCircle.color.r = GetRandomValue(0, 255);
				newCircle.color.g = GetRandomValue(0, 255);
				newCircle.color.b = GetRandomValue(0, 255);
				newCircle.color.a = 255;
				
				objects.push_back(newCircle);
				spaceInstance = 0;
			}
		}

		float deltaTime = GetFrameTime();
		accumulator = deltaTime;

		while (accumulator >= timestep)
		{
			//unigridadd
			for (int i = 0; i < unigrid.size(); i++)
			{
				GridCells& tempGridCell = unigrid[i];
				for (int j = 0; j < objects.size(); j++)
				{
					Object& objA = objects[j];
					if (CheckIfObjInGrid(tempGridCell, objA) && objA.shapeType == ShapeType::Circle)
					{
						//https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
						if (!(std::find(tempGridCell.indicesOfObjectsInGrid.begin(), tempGridCell.indicesOfObjectsInGrid.end(), j) != tempGridCell.indicesOfObjectsInGrid.end()))
						{
							tempGridCell.indicesOfObjectsInGrid.push_back(j);
						}
					}
					else
					{
						//https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
						tempGridCell.indicesOfObjectsInGrid.erase(std::remove(tempGridCell.indicesOfObjectsInGrid.begin(), tempGridCell.indicesOfObjectsInGrid.end(), j), tempGridCell.indicesOfObjectsInGrid.end());
					}
				}
			}
			//unigridadd
			for (int i = 0; i < objects.size(); i++)
			{
				Object& objA = objects[i];
				
				objA.velocity = Vector2Add(objA.velocity, Vector2Scale(objA.acceleration, timestep));
				objA.velocity = Vector2Subtract(objA.velocity, Vector2Scale(objA.velocity, 0.5f * objA.inverseMass * timestep));
				objA.position = Vector2Add(objA.position, Vector2Scale(objA.velocity, timestep));

				//unigridadd
				for (int j = i; j < objects.size(); j++)
				{
					Object& objB = objects[j];
					if ((objA.shapeType == ShapeType::Circle) && (objB.shapeType == ShapeType::AABB))
					{
						HandleCircleAABBCollision(objA, objB);
					}
					else if ((objA.shapeType == ShapeType::AABB) && (objB.shapeType == ShapeType::Circle))
					{
						HandleCircleAABBCollision(objB, objA);
					}
				}
				//unigridadd
			}

			for (int i = 0; i < unigrid.size(); i++)
			{
				GridCells& tempGridCell = unigrid[i];
				for (int j = 0; j < tempGridCell.indicesOfObjectsInGrid.size(); j++)
				{
					int objAIndex = tempGridCell.indicesOfObjectsInGrid[j];
					Object& objA = objects[objAIndex];
					for (int k = j + 1; k < tempGridCell.indicesOfObjectsInGrid.size(); k++)
					{
						int objBIndex = tempGridCell.indicesOfObjectsInGrid[k];
						Object& objB = objects[objBIndex];
						HandleCircleCircleCollision(objA, objB);
					}
				}
			}
			accumulator -= timestep;
		}


		BeginDrawing();
		ClearBackground(WHITE);

		//unigridadd
		/*for (int i = 0; i < unigrid.size(); i++)
		{
			GridCells& cell = unigrid[i];
			DrawRectangleLines(cell.minValue.x, cell.minValue.y, cell.maxValue.x - cell.minValue.x, cell.maxValue.y - cell.minValue.y, RED);
		}*/
		//unigridadd

		for (int i = 0; i < objects.size(); i++)
		{
			Object& obj = objects[i];
			if (obj.shapeType == ShapeType::Circle)
			{
				DrawCircleV(obj.position, obj.size.x / 2.0f, obj.color);
			}
			else if (obj.shapeType == ShapeType::AABB)
			{
				DrawRectangleV(obj.position, obj.size, obj.color);
			}
		}
		//std::cout << unigrid[0].indicesOfObjectsInGrid.size() << std::endl;
		/*for (int i = 0; i < unigrid[0].indicesOfObjectsInGrid.size(); i++)
		{
			std::cout << "Circle " << unigrid[0].indicesOfObjectsInGrid[i] << std::endl;
		}
		std::cout << std::endl;*/
		EndDrawing();
	}
	CloseWindow();
	return 0;
}