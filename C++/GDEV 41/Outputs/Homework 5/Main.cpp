#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "entt.hpp"

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

struct PositionMovementComponent
{
	Vector2 position;
	Vector2 direction;
	float speed;
};

struct ObjectPropertiesComponent
{
	float radius;
	Color color;
	float lifeTime;
};

struct OpacityComponent
{
	float fadeDuration;
};

struct GrowShrinkComponent
{
	float growShrinkRate;
};

struct ChildrenSpawnComponent
{
	int numberOfChildren;
};

void SpawnObject(entt::registry& registry, Vector2 position)
{
	entt::entity e = registry.create();
	PositionMovementComponent& tempObjectPosVel = registry.emplace<PositionMovementComponent>(e);
	ObjectPropertiesComponent& tempObjectProperties = registry.emplace<ObjectPropertiesComponent>(e);
	
	//position
	tempObjectPosVel.position = position;
	tempObjectPosVel.direction.x = RandomNumber(-1, 1);
	tempObjectPosVel.direction.y = RandomNumber(-1, 1);
	tempObjectPosVel.speed = RandomNumber(1, 100);

	//properties
	tempObjectProperties.radius = RandomNumber(3, 15);
	tempObjectProperties.color.r = GetRandomValue(0, 255);
	tempObjectProperties.color.g = GetRandomValue(0, 255);
	tempObjectProperties.color.b = GetRandomValue(0, 255);
	tempObjectProperties.color.a = 255;
	tempObjectProperties.lifeTime = GetRandomValue(5, 13);

	//fade
	if (GetRandomValue(0, 100) < 35)
	{
		OpacityComponent& tempObjectOpacity = registry.emplace<OpacityComponent>(e);
		tempObjectOpacity.fadeDuration = RandomNumber(1, tempObjectProperties.lifeTime);
	}

	//size
	if (GetRandomValue(0, 100) < 35)
	{
		GrowShrinkComponent& tempObjectSizeModifier = registry.emplace<GrowShrinkComponent>(e);
		tempObjectSizeModifier.growShrinkRate = RandomNumber(-5, 5);
	}

	//birth
	if (GetRandomValue(0, 100) < 10)
	{
		ChildrenSpawnComponent& tempObjectChildSpawn = registry.emplace<ChildrenSpawnComponent>(e);
		tempObjectChildSpawn.numberOfChildren = RandomNumber(1, 5);
	}
}

int main()
{
	int windowWidth = 1280, windowHeight = 720;
	InitWindow(windowWidth, windowHeight, "Homework 05");

	const float FPSCount = 60.0f;
	SetTargetFPS(FPSCount);

	const float timestep = 1.0f / FPSCount;
	float accumulator = 0.0f;

	entt::registry registry;

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		accumulator += deltaTime;
		if (IsKeyDown(KEY_SPACE) && accumulator >= timestep)
		{
			SpawnObject(registry, { (float)windowWidth / 2, (float)windowHeight / 2 });
			accumulator -= timestep;
		}

		BeginDrawing();
		ClearBackground(WHITE);

		auto objects = registry.view<PositionMovementComponent, ObjectPropertiesComponent, OpacityComponent, GrowShrinkComponent, ChildrenSpawnComponent>();
		for (auto entity : objects)
		{
			PositionMovementComponent& tempObjectPosVel = registry.get<PositionMovementComponent>(entity);
			ObjectPropertiesComponent& tempObjectProperties = registry.get<ObjectPropertiesComponent>(entity);
			OpacityComponent& tempObjectOpacity = registry.get<OpacityComponent>(entity);
			GrowShrinkComponent& tempObjectSizeModifier = registry.get<GrowShrinkComponent>(entity);
			ChildrenSpawnComponent& tempObjectChildSpawn = registry.get<ChildrenSpawnComponent>(entity);

			if (tempObjectProperties.lifeTime > 0)
			{
				tempObjectProperties.lifeTime -= deltaTime;
				tempObjectPosVel.position = Vector2Add(tempObjectPosVel.position, Vector2Scale(Vector2Scale(tempObjectPosVel.direction, tempObjectPosVel.speed), deltaTime));
				
				if ((tempObjectOpacity.isActive) && tempObjectProperties.color.a > 0)
				{
					tempObjectProperties.color.a -= (255 / tempObjectOpacity.fadeDuration) * deltaTime;
				}

				if (tempObjectSizeModifier.isActive)
				{
					tempObjectProperties.radius += tempObjectSizeModifier.growShrinkRate * 0.01;
				}
			}
			else
			{
				if (tempObjectChildSpawn.isActive)
				{
					for (int i = 0; i < tempObjectChildSpawn.numberOfChildren; i++)
					{
						SpawnObject(registry, tempObjectPosVel.position);
					}
				}
				registry.destroy(entity);
			}
			DrawCircleV(tempObjectPosVel.position, tempObjectProperties.radius, tempObjectProperties.color);
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}