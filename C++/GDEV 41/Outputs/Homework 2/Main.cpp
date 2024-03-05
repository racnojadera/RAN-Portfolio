#include <cmath>
#include <raylib.h>
#include <fstream>

struct Particle
{
    bool isActive;
    Vector2 position;
    Vector2 direction;
    float speed;
    float lifeTime;
    Color color;

    float maxLifeTime;
};

int findFirstInactiveParticle(int* pointerInactive, Particle* pParticles)
{
    for(int i = 0; i < 1000; i++)
    {
        if(!pParticles[i].isActive)
        {
            return i;
        }
    }
    return 0;
}

float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

int main()
{
    bool isPlaying = true;
    int firstInactiveParticle = 0;
    int* pFIP = &firstInactiveParticle;
    Particle particlesArray[1000];
    Particle* pParticles = &particlesArray[0];

    KeyboardKey keyboardAdjustDecrease, keyboardAdjustIncrease;
    KeyboardKey mouseAdjustDecrease, mouseAdjustIncrease;
    KeyboardKey keyboardFire, keyboardMouseSwitch;
    MouseButton mouseFire;
    int keyboardRate = 25;
    int mouseRate = 25;
    int FPSCount = 60;
    int inputMode = 1;

    float kbTimeSinceLastGen, msTimeSinceLastGen;

    //set-up, read .ini -- start
    InitWindow(800, 600, "Homework 2 - Game Loop, Input, Frames");
    SetTargetFPS(FPSCount);

    std::ifstream inFile;
    std::string label;
    int adj1;
    int adj2;
    int i = 0;

    inFile.open("config.ini");
    /*
    keyboard- = 263
    keyboard+ = 262
    mouse- = 264
    mouse+ = 265
    kbmswitch = 258
    keyboardfire = 32

    mousefire = 0
    */

    while (inFile >> adj1 >> adj2)
    {
        if(i == 0)
        {
            keyboardAdjustDecrease = (KeyboardKey)adj1;
            keyboardAdjustIncrease = (KeyboardKey)adj2;
        }
        else if (i == 1)
        {
            mouseAdjustDecrease = (KeyboardKey)adj1;
            mouseAdjustIncrease = (KeyboardKey)adj2;
        }
        else if (i == 2)
        {
            keyboardFire = (KeyboardKey)adj1;
            keyboardMouseSwitch = (KeyboardKey)adj2;
        }
        else if (i == 3)
        {
            mouseFire = (MouseButton)adj1;
        }
        i++;
    }
    inFile.close();
    //set-up, read .ini -- end

    for(int i = 0; i < 1000; i++)
    {
        pParticles[i].isActive = false;
    }

    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        
        //process Input -- start
        if(IsKeyPressed(keyboardAdjustDecrease))
        {
            if(keyboardRate >= 2)
            {
                keyboardRate--;
            }
        }
        if(IsKeyPressed(keyboardAdjustIncrease))
        {
            if(keyboardRate <= 49)
            {
                keyboardRate++;
            }
        }
        if(IsKeyPressed(mouseAdjustDecrease))
        {
            if(mouseRate >= 2)
            {
                mouseRate--;
            }
        }
        if(IsKeyPressed(mouseAdjustIncrease))
        {
            if(mouseRate <= 49)
            {
                mouseRate++;
            }
        }
        if(IsKeyPressed(keyboardMouseSwitch))
        {
            if(inputMode == 3)
            {
                inputMode = 1;
            }
            else
            {
                inputMode++;
            }
        }

        if(IsKeyDown(keyboardFire) && (inputMode == 1 || inputMode == 3))
        {
            if(kbTimeSinceLastGen >= 1.0f/keyboardRate)
            {
                kbTimeSinceLastGen -= 1.0f/keyboardRate;
                firstInactiveParticle = findFirstInactiveParticle(pFIP, pParticles);
                pParticles[firstInactiveParticle].isActive = true;
                pParticles[firstInactiveParticle].position.x = 0.5f*800;
                pParticles[firstInactiveParticle].position.y = 1.0f*600;
                pParticles[firstInactiveParticle].direction.y = 1.0f;
                pParticles[firstInactiveParticle].direction.x = RandomNumber(-1, 1);
                pParticles[firstInactiveParticle].speed = RandomNumber(50, 100);
                pParticles[firstInactiveParticle].lifeTime = RandomNumber(2, 5);
                pParticles[firstInactiveParticle].maxLifeTime = pParticles[firstInactiveParticle].lifeTime;
                pParticles[firstInactiveParticle].color.r = GetRandomValue(0, 255);
                pParticles[firstInactiveParticle].color.g = GetRandomValue(0, 255);
                pParticles[firstInactiveParticle].color.b = GetRandomValue(0, 255);
            }
            kbTimeSinceLastGen += GetFrameTime();
        }

        if(IsMouseButtonDown(mouseFire) && (inputMode == 2 || inputMode == 3))
        {
            if(msTimeSinceLastGen >= 1.0f/mouseRate)
            {
                msTimeSinceLastGen -= 1.0f/keyboardRate;
                firstInactiveParticle = findFirstInactiveParticle(pFIP, pParticles);
                pParticles[firstInactiveParticle].isActive = true;
                pParticles[firstInactiveParticle].position.x = GetMouseX();
                pParticles[firstInactiveParticle].position.y = GetMouseY();
                pParticles[firstInactiveParticle].direction.y = RandomNumber(-1, 1);
                pParticles[firstInactiveParticle].direction.x = RandomNumber(-1, 1);
                pParticles[firstInactiveParticle].speed = RandomNumber(50, 100);
                pParticles[firstInactiveParticle].lifeTime = RandomNumber(0.5f, 2);
                pParticles[firstInactiveParticle].maxLifeTime = pParticles[firstInactiveParticle].lifeTime;
                pParticles[firstInactiveParticle].color.r = GetRandomValue(0, 255);
                pParticles[firstInactiveParticle].color.g = GetRandomValue(0, 255);
                pParticles[firstInactiveParticle].color.b = GetRandomValue(0, 255);
            }
            msTimeSinceLastGen += GetFrameTime();
        }
        //process Input -- end

        //update -- start
        for(int i = 0; i < 1000; i++)
        {
            if(pParticles[i].lifeTime <= 0)
            {
                pParticles[i].isActive = false;
            }
            else //if the particle's lifetime is greater than 0, then particle.isActive is true and is updated
            {
                //because for some reason, raymath.h won't get imported
                float magnitude = sqrt(pParticles[i].direction.x*pParticles[i].direction.x + pParticles[i].direction.y*pParticles[i].direction.y);

                pParticles[i].position.x += pParticles[i].speed*deltaTime*(pParticles[i].direction.x/magnitude);
                pParticles[i].position.y -= pParticles[i].speed*deltaTime*(pParticles[i].direction.y/magnitude);
                pParticles[i].color.a = (int) ((pParticles[i].lifeTime / pParticles[i].maxLifeTime) * 255);
                pParticles[i].lifeTime -= deltaTime;
            }
        }
        //update -- end

        //render -- start
        ClearBackground(WHITE);
        for(int i = 0; i < 1000; i++)
        {
            if(pParticles[i].isActive)
            {
                DrawCircle(pParticles[i].position.x, pParticles[i].position.y, 5, pParticles[i].color);
            }
            
        }
        DrawText("Press 'TAB' to change input method", 5, 571, 12, BLACK);
        if(inputMode == 1)
        {
            DrawText("Current Input Mode: Keyboard", 05, 583, 12, BLACK);
        }
        else if(inputMode == 2)
        {
            DrawText("Current Input Mode: Mouse", 5, 583, 12, BLACK);
        }
        else if(inputMode == 3)
        {
            DrawText("Current Input Mode: Keyboard and Mouse", 5, 583, 12, BLACK);
        }
        //render -- end
        EndDrawing();
    }
    
    //deallocation -- start
    delete [] pParticles;
    pParticles = 0;
    //deallocation -- end
    return 0;
}