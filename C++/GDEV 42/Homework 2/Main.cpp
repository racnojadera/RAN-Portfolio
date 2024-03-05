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

bool CheckIfCirclePressed(Point circle, Vector2 mousePos)
{
    if (Vector2DistanceSqr(circle.position, mousePos) <= (circle.radius*circle.radius))
    {
        return true;
    }
    return false;
}

std::vector<Point> listOfPoints;
std::vector<Vector2> lineFromPoints;
std::string stepsInput, numberOfPointsInput, pointXInput, pointYInput;
std::string curveOrder; //also numberOfLines

void InputValues()
{
    std::cin >> curveOrder;
    std::cin >> stepsInput;
    std::cin >> numberOfPointsInput;
    for(int i = 0; i < std::stoi(numberOfPointsInput); i++)
    {
        Point newPoint;
        std::cin >> pointXInput >> pointYInput;
        newPoint.position = {std::stof(pointXInput), std::stof(pointYInput)};
        newPoint.color = RED;
        listOfPoints.push_back(newPoint);
    }
}

std::vector<std::vector<int>> listOfRows;

void GeneratePascalTriangle()
{
    std::vector<int> row1and2;
    row1and2.push_back(1);
    listOfRows.push_back(row1and2);
    row1and2.push_back(1);
    listOfRows.push_back(row1and2);

    for (int i = 2; i <= std::stoi(curveOrder); i++)
    {
        std::vector<int> previousRow = listOfRows[i-1];
        std::vector<int> currentRow;

        currentRow.push_back(1);
        for (int j = 1; j < previousRow.size(); j++)
        {
            int currentValue;
            currentValue = previousRow[j-1] + previousRow[j];
            currentRow.push_back(currentValue);
        }
        currentRow.push_back(1);
        listOfRows.push_back(currentRow);
    }
}

Vector2 ParametricBezier(std::vector<Point> currentListOfPoints, float tValue)
{
    Vector2 ret;
    int pComp = currentListOfPoints.size()-1;
    std::vector<int> pascalRowBeingUsed = listOfRows[pComp];
    for(int i = 0; i < currentListOfPoints.size(); i++)
    {
        //i is the points inside the list
        float oneMinusTComp;
        float tComp;

        oneMinusTComp = pow((1-tValue),pComp-i);
        tComp = pow(tValue, i);

        Vector2 tempVector = currentListOfPoints[i].position;
        float coef;
        coef = pascalRowBeingUsed[i] * oneMinusTComp * tComp;
        ret = Vector2Add(ret, Vector2Scale(tempVector, coef));
    }

    return ret;
}

void CalculateLines()
{
    float step = 100.0f / std::stoi(stepsInput);
    step /= 100.0f;
    for(size_t i = 0; i < listOfPoints.size() - std::stoi(curveOrder); i = i + std::stoi(curveOrder))
    {
        std::vector<Point> currentListOfPoints;
        listOfPoints[i].color = GREEN;
        currentListOfPoints.push_back(listOfPoints[i]);
        
        //error
        for(int j = 1; j < std::stoi(curveOrder); j++)
        {
            currentListOfPoints.push_back(listOfPoints[i+j]);
        }
        
        listOfPoints[i+std::stoi(curveOrder)].color = GREEN;
        currentListOfPoints.push_back(listOfPoints[i+std::stoi(curveOrder)]);

        //instead of listofpoints, we now use currentlistofpoints
        float currentT = step;
        lineFromPoints.push_back(currentListOfPoints[0].position);

        while(currentT < 1.0f)
        {
            Vector2 tempLine;
            tempLine = ParametricBezier(currentListOfPoints, currentT);
            lineFromPoints.push_back(tempLine);
            currentT += step;
        }
        lineFromPoints.push_back(currentListOfPoints[currentListOfPoints.size()-1].position);
    }
}

void OpenWindow()
{
    const int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Homework 2 - Bezier Curve Using Parametric Formula");

    //point gets unclipped from cursor when it moves too fast, and adjusting target fps seems to remedy the issue described
    const float TARGET_FPS = 30000.0f;
    SetTargetFPS(TARGET_FPS);

    CalculateLines();
    lineFromPoints.clear();
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
            DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
        }
        EndDrawing();
    }
}

int main()
{
    InputValues();
    GeneratePascalTriangle();
    OpenWindow();
    return 0;
}