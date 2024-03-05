#include <string>
#include <iostream>
#include <fstream>
#include <winbase.h>

struct position
{
    int x;
    int y;
};

void Start(position* w, position* p, position* t)
{
    std::ifstream inFile;
    std::string label;
    std::string equalL;
    int a, b;
    int i = 0;
    inFile.open("settings.txt");
    if(!inFile)
    {
        std::cerr << "Unable to open settings.txt";
        exit(1);
    }
    //code assumes that player and target's coordinates are always inside the world grid
    while (inFile >> label >> equalL >> a >> b)
    {
        if(i==0)
        {
            (*w).x = a;
            (*w).y = b;
        }
        else if (i==1)
        {
            (*p).x = a;
            (*p).y = b;
        }
        else if (i==2)
        {
            (*t).x = a;
            (*t).y = b;
        }
        i++;
    }
    inFile.close();
}

void DrawMatrix(position* w, position* p, position* t)
{
    bool playerInRow, targetInRow;
    bool playerInputted = false;
    bool targetInputted = false;

    std::cout << std::endl;
    for(int height = 0; height <= ((*w).y * 3); height++)
    {
        if(height%3==0)
        {
            for(int width = 0; width <= ((*w).x * 3); width++)
            {
                if(width == 0)
                {
                    std::cout << "*";
                }
                else if(width != (*w).x * 3)
                {
                    std::cout << "*";
                }
                else
                {
                    std::cout << "*" << std::endl;
                }
            }
        }
        else
        {
            playerInRow = (((*p).y == height/3) && height%3==1) ? true : false;
            targetInRow = (((*t).y == height/3) && height%3==2) ? true : false;
            std::cout << "*";
            for(int width = 0; width < ((*w).x * 3); width++)
            {
                if(width%3==2)
                {
                    if(width != (*w).x * 3 - 1)
                    {
                        std::cout << "*";
                    }
                    else
                    {
                        std::cout << "*" << std::endl;
                    }
                }
                else if(width%3 == 0)
                {
                    if(playerInRow && ((*p).x == width/3))
                    {
                        if(!playerInputted)
                        {
                            std::cout << "P";
                            playerInputted = true;
                        }
                        else
                        {
                            std::cout << ".";
                        }
                    }
                    else
                    {
                        std::cout << ".";
                    }
                }
                else if(width%3 == 1)
                {
                    if(targetInRow && ((*t).x == width/3))
                    {
                        if(!targetInputted)
                        {
                            std::cout << "X";
                            targetInputted = true;
                        }
                        else
                        {
                            std::cout << ".";
                        }
                    }
                    else
                    {
                        std::cout << ".";
                    }
                }
            }
        }
    }
}

std::string UserInput()
{
    std::string userInput;
    std::getline(std::cin, userInput);
    return userInput;
}

void DoAction(std::string userCommand, position* w, position* p)
{
    std::string north = "n";
    std::string south = "s";
    std::string west = "w";
    std::string east = "e";
    if(userCommand == north)
    {
        (*p).y--;
        if((*p).y < 0)
        {
            (*p).y += (*w).y;
        }
    }
    else if(userCommand == south)
    {
        (*p).y++;
        if((*p).y >= (*w).y)
        {
            (*p).y -= (*w).y;
        }
    }
    else if(userCommand == east)
    {
        (*p).x++;
        if((*p).x >= (*w).x)
        {
            (*p).x -= (*w).x;
        }
    }
    else if(userCommand == west)
    {
        (*p).x--;
        if((*p).x < 0)
        {
            (*p).x += (*w).x;
        }
    }
}

bool CheckAttack(position* p, position* t)
{
    if(((*p).x == (*t).x) && ((*p).y == (*t).y))
    {
        std::cout << "You win!\nExiting..." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Target not found. Try again.\n" << std::endl;
        return false;
    }
}

void GameLoop(position* w, position* p, position* t)
{
    std::string userCommand = UserInput();
    std::string north = "n";
    std::string south = "s";
    std::string west = "w";
    std::string east = "e";
    std::string attack = "a";
    std::string exit = "exit";
    int attackResult;

    if((userCommand == north) || (userCommand == south) || (userCommand == east) || (userCommand == west))
    {
        DoAction(userCommand, w, p);
        DrawMatrix(w, p, t);
        GameLoop(w, p, t);
    }
    else if(userCommand == attack)
    {
        attackResult = CheckAttack(p, t);
        if(!attackResult)
        {
            GameLoop(w, p, t);
        }
    }
    else if(userCommand == exit)
    {
        std::cout << "Exiting..." << std::endl;
    }
    else
    {
        std::cout << "Invalid input. Try again." << std::endl;
        GameLoop(w, p, t);
    }
}

int main()
{
    position world, player, target;
    position* worldP = &world;
    position* playerP = &player;
    position* targetP = &target;
    Start(worldP, playerP, targetP);
    DrawMatrix(worldP, playerP, targetP);
    GameLoop(worldP, playerP, targetP);
    return 0;
}