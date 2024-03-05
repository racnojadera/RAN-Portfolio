#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

const int windowWidth = 800, windowHeight = 600;
const float TARGET_FPS = 60.0f;
float H_ACCEL, H_COEFF, H_OPPOSITE, H_AIR, MIN_H_VEL, MAX_H_VEL;
float GRAVITY;
float V_ACCEL, V_HOLD, V_SAFE, CUT_V_VEL, MAX_V_VEL;
float GAP;
int CAM_TYPE;
std::vector<int> CAM_EDGES;
float CAM_DRIFT;

Camera2D camera;

struct Player
{
    Vector2 size = {24, 32};
    Vector2 position;
    Vector2 velocity = {0, 0};
    Vector2 movement = {0, 0};
    Rectangle bounds;
    int horizontalDirection = 0;
    int jumpHold = 0;
    int airborneCounter = 0;
    bool isGrounded = false;
};

struct Platform
{
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
    Color color;
    bool isWall;
};

Player player;
std::vector<Platform> listOfPlatforms;

void InitializeProperties()
{
    std::vector<float> tempList;
    std::fstream newFile;

    newFile.open("constproperties.txt", std::ios::in);
    if(newFile.is_open())
    {
        std::string tempString;
        while(getline(newFile, tempString))
        {
            if((tempList.size() != 14))
            {
                tempList.push_back(std::stof(tempString.substr(tempString.find('=')+1)));
            }
            else
            {
                std::string camEdgeLineInput;
                camEdgeLineInput = tempString.substr(tempString.find('=')+1);
                
                CAM_EDGES.push_back(std::stoi(camEdgeLineInput.substr(0, camEdgeLineInput.find(' '))));
                camEdgeLineInput = camEdgeLineInput.substr(camEdgeLineInput.find(' ') + 1);

                CAM_EDGES.push_back(std::stoi(camEdgeLineInput.substr(0, camEdgeLineInput.find(' '))));
                camEdgeLineInput = camEdgeLineInput.substr(camEdgeLineInput.find(' ') + 1);

                CAM_EDGES.push_back(std::stoi(camEdgeLineInput.substr(0, camEdgeLineInput.find(' '))));
                CAM_EDGES.push_back(std::stoi(camEdgeLineInput.substr(camEdgeLineInput.find(' '))));
                tempList.push_back(0);
            }
        }
    }
    newFile.close();

    tempList[0] /= TARGET_FPS;
    tempList[5] /= TARGET_FPS;
    tempList[6] /= TARGET_FPS;
    tempList[7] /= TARGET_FPS;
    tempList[10] /= TARGET_FPS;
    tempList[11] /= TARGET_FPS;

    H_ACCEL = tempList[0];
    H_COEFF = tempList[1];
    H_OPPOSITE = tempList[2];
    H_AIR = tempList[3];
    MIN_H_VEL = tempList[4];
    MAX_H_VEL = tempList[5];
    GRAVITY = tempList[6];
    V_ACCEL = tempList[7];
    V_HOLD = tempList[8];
    V_SAFE = tempList[9];
    CUT_V_VEL = tempList[10];
    MAX_V_VEL = tempList[11];
    GAP = tempList[12];
    CAM_TYPE = tempList[13];
    CAM_DRIFT = tempList[15];
}

void InitializeObjects()
{
    std::string playerXPos, playerYPos;
    std::string numberOfPlatforms;
    std::string platformXPos, platformYPos, platformWidth, platformHeight;

    std::vector<std::string> linePerLine;
    std::fstream newFile;
    newFile.open("leveldata.txt", std::ios::in);
    if(newFile.is_open())
    {
        std::string tempString;
        while(getline(newFile, tempString))
        {
            linePerLine.push_back(tempString);
        }
    }
    newFile.close();

    for(int i = 0; i < linePerLine.size(); i++)
    {
        switch(i)
        {
            case 0:
                playerXPos = linePerLine[i].substr(0, linePerLine[i].find(' '));
                playerYPos = linePerLine[i].substr(linePerLine[i].find(' ') + 1);
                player.position = {std::stof(playerXPos), std::stof(playerYPos)};
                player.bounds = {player.position.x, player.position.y, player.size.x, player.size.y};
                break;

            case 1:
                numberOfPlatforms = linePerLine[i];
                break;

            default:
                platformXPos = linePerLine[i].substr(0, linePerLine[i].find(' '));
                linePerLine[i] = linePerLine[i].substr(linePerLine[i].find(' ') + 1);

                platformYPos = linePerLine[i].substr(0, linePerLine[i].find(' '));
                linePerLine[i] = linePerLine[i].substr(linePerLine[i].find(' ') + 1);

                platformWidth = linePerLine[i].substr(0, linePerLine[i].find(' '));
                platformHeight = linePerLine[i].substr(linePerLine[i].find(' '));

                if(listOfPlatforms.size() < std::stoi(numberOfPlatforms))
                {
                    Platform newPlatform;
                    newPlatform.position = {std::stof(platformXPos), std::stof(platformYPos)};
                    newPlatform.size = {std::stof(platformWidth), std::stof(platformHeight)};
                    newPlatform.bounds.x = newPlatform.position.x - newPlatform.size.x*0.5f;
                    newPlatform.bounds.y = newPlatform.position.y - newPlatform.size.y*0.5f;
                    newPlatform.bounds.width = newPlatform.size.x;
                    newPlatform.bounds.height = newPlatform.size.y;
                    newPlatform.color = RED;
                    if(newPlatform.bounds.width >= newPlatform.bounds.height)
                    {
                        newPlatform.isWall = false;
                    }
                    else
                    {
                        newPlatform.isWall = true;
                    }
                    listOfPlatforms.push_back(newPlatform);
                }
                break;
        }
    }

    camera = { 0 };
    camera.target = { player.bounds.x, player.bounds.y };
    camera.offset = { windowWidth, windowHeight };
    camera.zoom = 1.0f;
}

void HorizontalCollision(Platform &tempPlatform)
{
    float otherX = tempPlatform.position.x;
    float ourX = player.position.x;
    if(ourX > otherX)
    {
        otherX += tempPlatform.size.x * 0.5f;
        ourX -= player.size.x * 0.5f;
        player.position.x += (otherX - ourX + GAP);
        player.velocity.x = 0;
    }
    else if(ourX < otherX)
    {
        otherX -= tempPlatform.size.x * 0.5f;
        ourX += player.size.x * 0.5f;
        player.position.x += (otherX - ourX - GAP);
        player.velocity.x = 0;
    }
}

void VerticalCollision(Platform &tempPlatform)
{
    float otherY = tempPlatform.position.y;
    float ourY = player.position.y;
    if(ourY > otherY)
    {
        otherY += tempPlatform.size.y * 0.5f;
        ourY -= player.size.y * 0.5f;
        player.position.y += (otherY - ourY);
        player.velocity.y = 0;
    }
    else if(ourY < otherY)
    {
        otherY -= tempPlatform.size.y * 0.5f;
        ourY += player.size.y * 0.5f;
        player.position.y += (otherY - ourY);
        player.velocity.y = 0;
        player.isGrounded = true;
    }
}

void MainWindow()
{
    InitWindow(windowWidth, windowHeight, "Homework 5: A Simple Platformer with a Camera");
    SetTargetFPS(TARGET_FPS);

    const float TIMESTEP = 1.0f / TARGET_FPS;
    float accumulator = 0.0f;

    bool playerColliding = false;

    Camera2D camera = { 0 };
    camera.target = { player.bounds.x, player.bounds.y };
    camera.offset = { windowWidth / 2, windowHeight / 2 };
    camera.zoom = 1.0f;
    
    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        accumulator += deltaTime;
        while(accumulator >= TIMESTEP)
        {
            if(IsKeyDown(KEY_A))
            {
                if(player.velocity.x > -1.0f*MAX_H_VEL)
                {
                    player.velocity.x -= H_ACCEL;
                }
                else
                {
                    player.velocity.x = -1.0f*MAX_H_VEL;
                }
                player.movement.x = 1;
            }
            if(IsKeyDown(KEY_D))
            {
                if(player.velocity.x < MAX_H_VEL)
                {
                    player.velocity.x += H_ACCEL;
                }
                else
                {
                    player.velocity.x = MAX_H_VEL;
                }
                player.movement.x = 1;
            }

            if(IsKeyDown(KEY_W))
            {
                if(player.isGrounded)
                {
                    if(player.jumpHold < V_HOLD)
                    {
                        player.jumpHold++;
                    }
                    else
                    {
                        player.jumpHold = V_HOLD;
                    }
                    player.movement.y = 0;
                }
            }
            if(IsKeyReleased(KEY_W))
            {
                if(player.isGrounded)
                {
                    player.movement.y = 1;
                }
            }

            if((player.jumpHold > 0) && (player.movement.y == 1))
            {
                if(player.jumpHold >= 5)
                {
                    if(player.velocity.y > CUT_V_VEL)
                    {
                        player.velocity.y += V_ACCEL;
                    }
                    else
                    {
                        player.velocity.y = CUT_V_VEL;
                    }
                }
                else if(player.jumpHold > 0)
                {
                    std::cout << "this runs" << std::endl;
                    if(player.velocity.y > CUT_V_VEL)
                    {
                        player.velocity.y += V_ACCEL*0.01f;
                    }
                    else
                    {
                        player.velocity.y = CUT_V_VEL*0.01f;
                    }
                }
                player.jumpHold--;
            }

            if(player.airborneCounter > V_SAFE)
            {
                player.isGrounded = false;
            }

            if((!player.isGrounded) || (player.jumpHold == 0))
            {
                if(player.velocity.y < MAX_V_VEL)
                {
                    player.velocity.y += GRAVITY;
                }
                else
                {
                    player.velocity.y = MAX_V_VEL;
                }
            }
            
            if(player.movement.x == 0)
            {
                player.velocity.x *= H_COEFF;
                if(player.velocity.x <= MIN_H_VEL)
                {
                    player.velocity.x = 0;
                    player.horizontalDirection = 0;
                }
            }
            player.movement.x = 0;

            if(!player.isGrounded)
            {
                player.position.x += player.velocity.x*H_AIR;
            }
            else
            {
                player.position.x += player.velocity.x;
            }
            player.position.y += player.velocity.y;

            for(size_t i = 0; i < listOfPlatforms.size(); ++i)
            {
                if(CheckCollisionRecs(listOfPlatforms[i].bounds, {player.position.x, player.position.y, player.size.x, player.size.y+1}) && !listOfPlatforms[i].isWall)
                {
                    playerColliding = true;
                    break;
                }
            }

            if(!playerColliding)
            {
                player.airborneCounter++;
            }
            else
            {
                player.airborneCounter = 0;
            }

            for(size_t i = 0; i < listOfPlatforms.size(); ++i)
            {
                if(CheckCollisionRecs(listOfPlatforms[i].bounds, player.bounds) && listOfPlatforms[i].isWall)
                {
                    HorizontalCollision(listOfPlatforms[i]);
                }

                if(CheckCollisionRecs(listOfPlatforms[i].bounds, player.bounds) && !listOfPlatforms[i].isWall)
                {
                    VerticalCollision(listOfPlatforms[i]);
                }
            }

            player.bounds.x = player.position.x - player.size.x*0.5f;
            player.bounds.y = player.position.y - player.size.y*0.5f;
            playerColliding = false;


            //ALL CAMERA
            switch (CAM_TYPE)
            {
                case 0:
                    camera.target = {player.bounds.x, player.bounds.y};
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    if(player.isGrounded)
                    {
                        float driftY = Clamp(player.position.y - camera.target.y, -CAM_DRIFT, CAM_DRIFT);
                        camera.target.y += driftY;
                    }
                    break;
            }
            accumulator -= TIMESTEP;
        }

        BeginDrawing();
        BeginMode2D(camera);

        ClearBackground(WHITE);
        DrawRectangleRec(player.bounds, GREEN);
        for(size_t i = 0; i < listOfPlatforms.size(); ++i)
        {
            DrawRectangleRec(listOfPlatforms[i].bounds, listOfPlatforms[i].color);
        }

        EndMode2D();
        EndDrawing();
    }    
}

int main()
{
    InitializeProperties();
    InitializeObjects();
    MainWindow();
    return 0;
}