#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Point
{
    Vector2 position;
    float radius = 7;
    Color color;
};

Vector2 LerpQuad(Vector2 pointA, Vector2 pointB, Vector2 pointC, float tValue)
{
    Vector2 ret;
    Vector2 firstComp, secondComp, thirdComp;
    float aConst = (1-tValue);
    firstComp = Vector2Scale(pointA, aConst*aConst);
    secondComp = Vector2Scale(pointB, 2*aConst*tValue);
    thirdComp = Vector2Scale(pointC, tValue*tValue);
    ret = Vector2Add(Vector2Add(firstComp, secondComp), thirdComp);
    return ret;
}

std::vector<Point> listOfPoints;
std::vector<Vector2> lineFromPoints;
std::string stepsInput, numberOfPointsInput, pointXInput, pointYInput;

void InputValues()
{
    std::cin >> stepsInput;
    std::cin >> numberOfPointsInput;
    for(int i = 0; i < std::stoi(numberOfPointsInput); i++)
    {
        Point newPoint;
        std::cin >> pointXInput >> pointYInput;
        newPoint.position = {std::stof(pointXInput), std::stof(pointYInput)};
        
        if(i % 2 == 1)
        {
            if((std::stoi(numberOfPointsInput) % 2 == 0) && (i == std::stoi(numberOfPointsInput)-1))
            {
                newPoint.color = RED;
            }
            else
            {
                newPoint.color = GREEN;
            }
        }
        else
        {
            newPoint.color = RED;
        }
        listOfPoints.push_back(newPoint);
    }
}

bool CheckIfCirclePressed(Point circle, Vector2 mousePos)
{
    if (Vector2DistanceSqr(circle.position, mousePos) <= (circle.radius*circle.radius))
    {
        return true;
    }
    return false;
}

void CalculateLines()
{
    //Added an extra argument so program can accept even if number of points is not 3 + 2x.
    //Should an input not follow the 3 + 2x number of points, then the last two points will instead be converted into a simple line segment with both of the points serving as the endpoint of the segment.

    float step = 100.0f / std::stoi(stepsInput);
    step /= 100.0f;
    for(size_t i = 0; i < listOfPoints.size() - 2; i=i+2)
    {
        float currentT = step;
        lineFromPoints.push_back(listOfPoints[i].position);
        while(currentT < 1.0f)
        {
            Vector2 tempLine;
            tempLine = LerpQuad(listOfPoints[i].position, listOfPoints[i+1].position, listOfPoints[i+2].position, currentT);
            lineFromPoints.push_back(tempLine);
            currentT += step;
        }
        lineFromPoints.push_back(listOfPoints[i+2].position);
    }
    if(listOfPoints.size() % 2 == 0)
    {
        int arraySize = listOfPoints.size();
        lineFromPoints.push_back(listOfPoints[arraySize-2].position);
        lineFromPoints.push_back(listOfPoints[arraySize-1].position);
    }
}

void OpenWindow()
{
    const int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Homework 1 - Bezier Curves");

    //point gets unclipped from cursor when it moves too fast, and adjusting target fps seems to remedy the issue described
    const float TARGET_FPS = 30000.0f;
    SetTargetFPS(TARGET_FPS);

    CalculateLines();

    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            for(size_t i = 0; i < listOfPoints.size(); ++i)
            {
                if(CheckIfCirclePressed(listOfPoints[i], GetMousePosition()))
                {
                    lineFromPoints.clear();
                    listOfPoints[i].position = mousePosition;
                    CalculateLines();
                }
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        for(size_t i = 0; i < lineFromPoints.size()-1; ++i)
        {
            DrawLineV(lineFromPoints[i], lineFromPoints[i+1], WHITE);
        }

        for(size_t i = 0; i < listOfPoints.size(); ++i)
        {
            if(int(i) % 2 == 1)
            {
                DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
            }
            else
            {
                DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
            }
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