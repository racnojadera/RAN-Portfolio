#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<Vector2> listOfNumbers;
int numberOfLines = 0;

void UserPrompt()
{
    std::string userInputLines;
    std::cout << "Enter number of lines: ";
    std::cin >> userInputLines;
    numberOfLines = std::stoi(userInputLines);
}

/*std::vector<Vector2> PascalTriangle()
{
    std::cout << numberOfLines;
}*/

void PascalTriangle()
{
    std::cout << numberOfLines;
}

int main()
{
    UserPrompt();
    PascalTriangle();
    pause();
    return 0;
}