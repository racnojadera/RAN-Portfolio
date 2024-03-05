#include <raylib.h>

struct Particle
{
    bool isActive;
    Vector2 position;
    Vector2 direction;
    float speed;
    float lifeTime;
    float maxLifeTime;
    Color color;
};

void setupInitialState(Particle* pParticles, KeyboardKey kAD, KeyboardKey kAI, KeyboardKey mAD, KeyboardKey mAI, KeyboardKey kMS)
{
    InitWindow(800,600, "Homework 2 - Game Loop, Input, Frames");
    for(int i = 0; i < 1000; i++)
    {
        pParticles[i].isActive = false;
    }
    pParticles[500].isActive = true;
    pParticles[500].lifeTime = 500;
    pParticles[500].maxLifeTime = 500;
    pParticles[500].color = (Color) {128, 128, 128, 255};
    //bind keybinds
    SetTargetFPS(60);
}

void clearScreen()
{
    ClearBackground(BLACK);
}

void processInput(bool* isPlaying)
{
    if(WindowShouldClose())
    {
        *isPlaying = false;
    }
    //when pressed
}

void update(Particle* pParticles)
{
    for(int i = 0; i < 1000; i++)
    {
        if(pParticles[i].lifeTime <= 0)
        {
            pParticles[i].isActive = false;
        }
        else
        {
            pParticles[i].lifeTime-=10;
            //DrawText(pParticles[i].lifeTime, 400, 588, 12, WHITE);
            pParticles[i].color = Fade(pParticles[i].color, (pParticles[i].lifeTime/pParticles[i].maxLifeTime));
        }
        //position add/subtract
        
    }
}

void render(Particle* pPtls)
{
    for(int i = 0; i < 1000; i++)
    {
        if(pPtls[i].isActive)
        {
            //DrawCircle(400, 300, 5, RED);
            DrawCircle(400, 300, 5, pPtls[i].color);
            //DrawCircle(pPtls[i].position.x, pPtls[i].position.y, 5, pPtls[i].color);
        }
    }
}

void cleanupState()
{
    //insert deallocate array snippet here
    CloseWindow();
}

int main() {
    Particle particlesArray[1000];
    Particle* pParticles = &particlesArray[0];

    KeyboardKey keyboardAdjustDecrease, keyboardAdjustIncrease;
    KeyboardKey mouseAdjustDecrease, mouseAdjustIncrease;
    KeyboardKey keyboardMouseSwitch;
    int keyboardRate, mouseRate;
    bool keyboardMode = true;

    setupInitialState(pParticles, keyboardAdjustDecrease, keyboardAdjustIncrease, mouseAdjustDecrease, mouseAdjustIncrease, keyboardMouseSwitch);
    bool isPlaying = true;
    while (isPlaying)
    {
        BeginDrawing();
        //DrawText("abc", 400, 588, 12, WHITE);
        processInput(&isPlaying);
        update(pParticles);
        render(pParticles);
        EndDrawing();
    }
    cleanupState();
    return 0;
}