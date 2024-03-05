#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<std::vector<int>> listOfRows;
int numberOfLines = 0;

void UserPrompt()
{
    std::string userInputLines;
    std::cout << "Enter number of lines: ";
    std::cin >> userInputLines;
    numberOfLines = std::stoi(userInputLines);
}

void PascalTriangle()
{
    std::vector<int> row1and2;
    row1and2.push_back(1);
    listOfRows.push_back(row1and2);
    row1and2.push_back(1);
    listOfRows.push_back(row1and2);
    
    for(int i = 2; i < numberOfLines; i++)
    {
        std::vector<int> previousRow = listOfRows[i-1];
        std::vector<int> currentRow;

        currentRow.push_back(1);
        for(int j = 1; j < previousRow.size(); j++)
        {
            int currentValue;
            currentValue = previousRow[j-1] + previousRow[j];
            currentRow.push_back(currentValue);
        }
        currentRow.push_back(1);
        listOfRows.push_back(currentRow);
    }
    
}

void PrintRows()
{
    for(size_t i = 0; i < listOfRows.size(); ++i)
    {
        std::vector<int> tempRow = listOfRows[i];
        for(size_t j = 0; j < tempRow.size(); ++j)
        {
            std::cout << tempRow[j] << std::endl;
        }
        std::cout << std::endl;
    }
}

int main()
{
    UserPrompt();
    PascalTriangle();
    PrintRows();
    return 0;
}