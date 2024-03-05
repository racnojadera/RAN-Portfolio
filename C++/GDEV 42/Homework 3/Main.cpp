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

struct MovingObject
{
    Vector2 position;
    Vector2 velocityForDeviance;
    float radius = 10;
    Color color;
    bool isActive;
    int bezierNumber;
    bool deviating;
    float tValue;
};

bool CheckIfCirclePressed(Point circle, Vector2 mousePos)
{
    if (Vector2DistanceSqr(circle.position, mousePos) <= (circle.radius*circle.radius))
    {
        return true;
    }
    return false;
}

std::vector<MovingObject> listOfMovingObjects;

std::vector<Point> listOfPoints;
std::vector<Vector2> lineFromPoints;
std::vector<std::vector<Point>> listOfControlPointsSetList;
std::string stepsInput, numberOfPointsInput, pointXInput, pointYInput;
std::string curveOrder; //also numberOfLines
std::string vInput;

void InputValues()
{
    std::cin >> curveOrder;
    std::cin >> stepsInput;
    std::cin >> vInput;
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


Vector2 CalculateDerivative(std::vector<Point> currentListOfPoints, float tValue)
{
    Vector2 ret;
    int pComp = currentListOfPoints.size()-2;
    int originalpComp = currentListOfPoints.size()-1; //multiplied to the coefficient
    std::vector<int> pascalRowBeingUsed = listOfRows[pComp];

    for(int i = 0; i < currentListOfPoints.size()-1; i++)
    {
        float oneMinusTComp, tComp;

        oneMinusTComp = pow((1-tValue),pComp-i);
        tComp = pow(tValue, i);

        Vector2 tempVector = Vector2Subtract(currentListOfPoints[i+1].position, currentListOfPoints[i].position);
        float coef;
        coef = pascalRowBeingUsed[i] * oneMinusTComp * tComp * originalpComp;
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
        listOfControlPointsSetList.push_back(currentListOfPoints);
    }
}

void CalculateMovingObject(MovingObject &movingObject)
{
    movingObject.tValue += 0.003f;
    if(movingObject.tValue >= 1.0f && movingObject.bezierNumber < listOfControlPointsSetList.size()-1)
    {
        movingObject.bezierNumber++;
        movingObject.tValue = 0.0f;
    }
    
    
    float currentTValue = movingObject.tValue;
    if((int(currentTValue*1000) % 100/(std::stoi(vInput)-1) == 0) && !movingObject.deviating)
    {
        int randValue = rand() % 1000 + 1;
        if(randValue <= 67)
        {
            movingObject.deviating = true;
            Vector2 copyOfVector = movingObject.velocityForDeviance;
            movingObject.velocityForDeviance.x = -1*copyOfVector.y;
            movingObject.velocityForDeviance.y = copyOfVector.x;
        }
    }

    if(!movingObject.deviating)
    {
        Vector2 newPosition = ParametricBezier(listOfControlPointsSetList[movingObject.bezierNumber], movingObject.tValue);
        movingObject.velocityForDeviance = Vector2Subtract(newPosition, movingObject.position);
        movingObject.position = newPosition;
        
    }
    else
    {
        Vector2 newVelocity;
        if(movingObject.tValue >= 1.0f)
        {
            newVelocity = CalculateDerivative(listOfControlPointsSetList[movingObject.bezierNumber], 1.0f);
        }
        else
        {
            newVelocity = CalculateDerivative(listOfControlPointsSetList[movingObject.bezierNumber], movingObject.tValue);
        }
        movingObject.position.x += newVelocity.y*0.003f;
        movingObject.position.y += -1*newVelocity.x*0.003f;
        
    }
}

void OpenWindow()
{
    const int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Homework 3 - Movement Along the Bezier Curve");

    //point gets unclipped from cursor when it moves too fast, and adjusting target fps seems to remedy the issue described
    const float TARGET_FPS = 30000.0f;
    SetTargetFPS(TARGET_FPS);

    const float TIMESTEP = 1.0f/ TARGET_FPS;
    float accumulator = 0.0f;

    CalculateLines();
    lineFromPoints.clear();
    listOfControlPointsSetList.clear();
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
                    listOfControlPointsSetList.clear();
                    lineFromPoints.clear();
                    listOfPoints[i].position = mousePosition;
                    CalculateLines();
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            MovingObject newMovingObject;
            newMovingObject.position = listOfPoints[0].position;
            newMovingObject.velocityForDeviance = {0.0f, 0.0f};
            newMovingObject.radius = 10;
            newMovingObject.color = BLUE;
            newMovingObject.isActive = true;
            newMovingObject.bezierNumber = 0;
            newMovingObject.tValue = -0.003f;
            newMovingObject.deviating = false;
            listOfMovingObjects.push_back(newMovingObject);
        }
        
        float deltaTime = GetFrameTime();

        accumulator += deltaTime;
        while(accumulator >= TIMESTEP*500)
        {
            for(size_t i = 0; i < listOfMovingObjects.size(); ++i)
            {
                MovingObject &tempObj = listOfMovingObjects[i];
                if (!tempObj.isActive)
                {
                    continue;
                }
                CalculateMovingObject(tempObj);
                if(!tempObj.deviating)
                {
                    if(tempObj.tValue >= 1.0f)
                    {
                        tempObj.isActive = false;
                    }
                }
                else
                {
                    if(tempObj.position.x <= 0 || tempObj.position.x >= windowWidth || tempObj.position.y <= 0 || tempObj.position.y >= windowHeight)
                    {
                        tempObj.isActive = false;
                    }
                }
            }
            accumulator -= TIMESTEP*500;
        }

        //update ball position
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

        for(size_t i = 0; i < listOfMovingObjects.size(); ++i)
        {
            if(listOfMovingObjects[i].isActive)
            {
                DrawCircleV(listOfMovingObjects[i].position, listOfMovingObjects[i].radius, listOfMovingObjects[i].color);
            }   
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