#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <queue>
#include <string>
#include <vector>

float scaleMultiplier = 2.0f;
std::vector<Vector2> listOfPoints, listOfPointsInBetween;

void InputValues()
{
    for(int i = 0; i < 4; i++)
    {
        //Converts copied input into readable values
        std::string userInput1, userInput2, userInput3, userInput4, userInput5;
        std::cout << "Copy inputs from canvas page directly to the terminal: ";
        std::cin >> userInput1 >> userInput2 >> userInput3 >> userInput4 >> userInput5;
        std::string firstPointX = userInput1.substr(1, userInput1.length()-2);
        std::string firstPointY = userInput2.substr(0, userInput2.length()-2);
        std::string secondPointX = userInput3.substr(1, userInput3.length()-2);
        std::string secondPointY = userInput4.substr(0, userInput4.length()-2);
        std::string middlePoint = userInput5.substr(0, userInput5.length()-1);

        //Set-up the points
        Vector2 point1, point2, point3;
        point1 = {std::stof(firstPointX), std::stof(firstPointY)};
        point2 = {std::stof(secondPointX), std::stof(secondPointY)};
        point3 = Vector2Add(Vector2Scale(Vector2Subtract(point2, point1), std::stof(middlePoint)/100), point1);

        //Adds each point into an arraylist for drawing
        listOfPoints.push_back(point1);
        listOfPoints.push_back(point2);
        listOfPointsInBetween.push_back(point3);
    }
}

void OpenWindow()
{
    int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "GDEV 42 - Exercise 1");

    const float TARGET_FPS = 60.0f;
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        for(size_t i = 0; i < listOfPointsInBetween.size(); ++i)
        {
            DrawCircleV(Vector2Scale(listOfPoints[2*i], scaleMultiplier), 5, RED);
            DrawCircleV(Vector2Scale(listOfPoints[2*i+1], scaleMultiplier), 5, RED);
            DrawLineV(Vector2Scale(listOfPoints[2*i], scaleMultiplier), Vector2Scale(listOfPoints[2*i+1], scaleMultiplier), RED);
            DrawCircleV(Vector2Scale(listOfPointsInBetween[i], scaleMultiplier), 5, GREEN);
        }
        EndDrawing();
    }
}

int main()
{
    InputValues();
    OpenWindow();
    
    return 0;
}