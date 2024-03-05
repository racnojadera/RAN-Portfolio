#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <iostream>

struct Balls
{
    bool isActive;
    Vector2 position;
    Vector2 direction;
    float velocity;
    Color color;
    //assume billiard balls have mass of 10
    bool isCue; //true if ball is cue, false if normal balls
};

struct Border
{
    Vector2 position;
    int width;
    int height;
    float mass = 9999999999.0f;
};

struct Pockets
{
    Vector2 position;
    float mass = 9999999999.0f;
};

struct Line
{
    Vector2 startPosition;
    Vector2 endPosition;
    float magnitude;
};

int main()
{
    KeyboardKey resetGame;
    MouseButton chargeStick = MOUSE_BUTTON_LEFT;
    
    std::ifstream inFile;
    int keyboardButtonForReset;
    inFile.open("config.ini");
    while (inFile >> keyboardButtonForReset)
    {
        resetGame = (KeyboardKey)keyboardButtonForReset;
    }
    inFile.close();

    Balls ballsArray[4];
    Balls* pBalls = &ballsArray[0];

    //set-up balls - start
    pBalls[0].isCue = true;
    pBalls[0].position.x = 150;
    pBalls[0].position.y = 300;

    pBalls[1].isCue = false;
    pBalls[1].position.x = 517;
    pBalls[1].position.y = 300;

    pBalls[2].isCue = false;
    pBalls[2].position.x = 570;
    pBalls[2].position.y = 269;

    pBalls[3].isCue = false;
    pBalls[3].position.x = 570;
    pBalls[3].position.y = 331;

    for(int i = 0; i < sizeof(pBalls); i++)
    {
        pBalls[i].isActive = true;
        pBalls[i].velocity = 0;
        pBalls[i].color = BLUE;
    }
    pBalls[0].color = WHITE;
    //set-up balls - end

    Border bordersArray[4];
    Border* pBorders = &bordersArray[0];
    //set-up borders - start
    pBorders[0].position.x = 0;
    pBorders[0].position.y = 0;
    pBorders[0].width = 800;
    pBorders[0].height = 50;
    
    pBorders[1].position.x = 0;
    pBorders[1].position.y = 550;
    pBorders[1].width = 800;
    pBorders[1].height = 50;
    
    pBorders[2].position.x = 0;
    pBorders[2].position.y = 0;
    pBorders[2].width = 50;
    pBorders[2].height = 600;
    
    pBorders[3].position.x = 750;
    pBorders[3].position.y = 0;
    pBorders[3].width = 50;
    pBorders[3].height = 600; 
    //set-up borders - end

    Pockets pocketsArray[4];
    Pockets* pPockets = &pocketsArray[0];
    //set-up pockets - start
    pPockets[0].position.x = 60;
    pPockets[0].position.y = 60;

    pPockets[1].position.x = 60;
    pPockets[1].position.y = 540;

    pPockets[2].position.x = 740;
    pPockets[2].position.y = 60;

    pPockets[3].position.x = 740;
    pPockets[3].position.y = 540;
    //set-up pockets - end

    Line strafeLine;
    strafeLine.magnitude = 0;

    //set-up - start
    InitWindow(800, 600, "Homework 3 - Basic Physics, Collision");
    SetTargetFPS(60);
    float accumulator = 0.0f, TIMESTEP = 0.000001f/ 60;
    //set-up - end

    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        BeginDrawing();

        //process Input - start
        bool isIdle = true;
        for(int i = 0; i < sizeof(pBalls); i++)
        {
            if(pBalls[i].velocity != 0)
            {
                isIdle = false;
                break;
            }
        }

        if(IsKeyPressed(resetGame))
        {
            pBalls[0].position.x = 150;
            pBalls[0].position.y = 300;
            pBalls[1].position.x = 517;
            pBalls[1].position.y = 300;
            pBalls[2].position.x = 570;
            pBalls[2].position.y = 269;
            pBalls[3].position.x = 570;
            pBalls[3].position.y = 331;

            for(int i = 0; i < sizeof(pBalls); i++)
            {
                pBalls[i].velocity = 0;
                pBalls[i].isActive = true;
            }
            //set-up balls - end
        }

        strafeLine.startPosition = pBalls[0].position;
        float magnitude = sqrt(pow(strafeLine.startPosition.x - GetMouseX(), 2) + pow(strafeLine.startPosition.y - GetMouseY(), 2));

        if(IsMouseButtonDown(chargeStick) && isIdle)
        {
            if(magnitude <= 100)
            {
                strafeLine.magnitude = magnitude;
                strafeLine.endPosition = GetMousePosition();
            }
            else
            {
                strafeLine.magnitude = 100;
                strafeLine.endPosition.x = strafeLine.startPosition.x + (((GetMouseX()-strafeLine.startPosition.x)/magnitude)*100);
                strafeLine.endPosition.y = strafeLine.startPosition.y + (((GetMouseY()-strafeLine.startPosition.y)/magnitude)*100);
            }
        }

        if(IsMouseButtonReleased(chargeStick) && isIdle)
        {
            magnitude = sqrt(pow(strafeLine.startPosition.x - strafeLine.endPosition.x, 2) + pow(strafeLine.startPosition.y - strafeLine.endPosition.y, 2));
            pBalls[0].velocity = magnitude*10;
            pBalls[0].direction.x = -1*(strafeLine.endPosition.x-strafeLine.startPosition.x)/magnitude;
            pBalls[0].direction.y = (strafeLine.endPosition.y-strafeLine.startPosition.y)/magnitude;

        }
        //process Input - end







        //UPDATE ------------------------------------------------------------------ START
        if(accumulator >= TIMESTEP)
        accumulator -= TIMESTEP;
        {
            //general movement - start
            for(int i = 0; i < sizeof(pBalls); i++)
            {
                float magnitude = sqrt(pBalls[i].direction.x*pBalls[i].direction.x + pBalls[i].direction.y*pBalls[i].direction.y);
                pBalls[i].position.x += pBalls[i].velocity*deltaTime*(pBalls[i].direction.x/magnitude);
                pBalls[i].position.y -= pBalls[i].velocity*deltaTime*(pBalls[i].direction.y/magnitude);
                pBalls[i].velocity *= 0.99;
                if(pBalls[i].velocity < 10)
                {
                    pBalls[i].velocity = 0;
                }
            }
            //general movement - end

            //ball to ball - start
            //last part of the puzzle
            int arraySizeBalls = sizeof(pBalls);
            for(int i = 0; i < arraySizeBalls; i++)
            {
                for(int j = 0; j < arraySizeBalls; j++)
                {
                    if(i != j)
                    {
                        float magnitude = sqrt(pow(pBalls[j].position.x - pBalls[i].position.x, 2) + pow(pBalls[j].position.y - pBalls[i].position.y, 2));
                        if (magnitude < 60)
                        {
                            if(pBalls[i].isActive && pBalls[j].isActive)
                            {
                                pBalls[j].direction.x = -1*(pBalls[i].position.x - pBalls[j].position.x)/magnitude;
                                pBalls[j].direction.y = (pBalls[i].position.y - pBalls[j].position.y)/magnitude;
                                pBalls[i].direction.x = -1*(pBalls[j].position.x - pBalls[i].position.x)/magnitude;
                                pBalls[i].direction.y = (pBalls[j].position.y - pBalls[i].position.y)/magnitude;
                                float relVel = pBalls[j].velocity - pBalls[i].velocity;
                                float impulse = -1*(1.4*(relVel*magnitude)/(pow(magnitude, 2)*0.2));
                                pBalls[j].velocity += (impulse/5)*magnitude;
                            }
                        }
                    }
                }
            }
            
            //ball to ball - end

            //ball to border - start
            for(int i = 0; i < sizeof(pBalls); i++)
            {
                if((pBalls[i].position.x + 30)> 750 || (pBalls[i].position.x - 30) < 50)
                {
                    pBalls[i].direction.x *= -1;
                }
                if((pBalls[i].position.y + 30)> 550 || (pBalls[i].position.y - 30) < 50)
                {
                    pBalls[i].direction.y *= -1;
                }
            }
            //ball to border - end
            
            //ball to pocket - start
            for(int i = 0; i < sizeof(pBalls); i++)
            {
                for(int j = 0; j < sizeof(pPockets); j++)
                {
                    float magnitude = sqrt(pow(pPockets[j].position.x - pBalls[i].position.x, 2) + pow(pPockets[j].position.y - pBalls[i].position.y, 2));
                    if(magnitude < 65) //65 because radius of pockets is 35, radius of balls is 30
                    {
                        if(pBalls[i].isCue)
                        {
                            pBalls[i].position.x = 150;
                            pBalls[i].position.y = 300; 
                            pBalls[i].velocity = 0;
                        }
                        else
                        {
                            pBalls[i].velocity = 0;
                            pBalls[i].isActive = false;
                        }
                    }
                }
            }
            //ball to pocket - end
            accumulator += GetFrameTime();
        }
        
        //UPDATE ------------------------------------------------------------------ END







        //RENDER ------------------------------------------------------------------ START
        //poolbackground - start
        ClearBackground(CLITERAL(Color){21, 88, 67, 255});
        for(int i = 0; i < sizeof(pBorders); i++)
        {
            DrawRectangle(pBorders[i].position.x, pBorders[i].position.y, pBorders[i].width, pBorders[i].height, BROWN);
        }

        for(int i = 0; i < sizeof(pPockets); i++)
        {
            DrawCircle(pPockets[i].position.x, pPockets[i].position.y, 35, BLACK);
        }
        //poolbackground - end

        //balls - start
        for(int i = 0; i < sizeof(pBalls); i++)
        {
            if(pBalls[i].isActive)
            {
                DrawCircle(pBalls[i].position.x, pBalls[i].position.y, 30, pBalls[i].color);
            }
        }
        //balls - end

        if(isIdle && IsMouseButtonDown(chargeStick))
        {
            DrawLineEx(strafeLine.startPosition, strafeLine.endPosition, 5, YELLOW);
        }
        //RENDER ------------------------------------------------------------------ END

        EndDrawing();
    }
    return 0;
}