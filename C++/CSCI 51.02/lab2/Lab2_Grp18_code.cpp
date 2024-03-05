#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

//Reads first line of .txt to define number of loops.
int defineNumberOfLines()
{
    string firstLine;
    getline(cin, firstLine);
    return atoi(firstLine.c_str());
}

//Prints the outputs.
void printLines(int indexCount, int numberLines, int digit1, int digit2, string reply)
{
    cout << "Agent #" << indexCount + 1 << " is at ";
    printf("(%d, %d)\n", digit1, digit2);
    
    if(indexCount == numberLines-1)
    {
        cout << "Says:" << reply;
    }
    else
    {
        cout << "Says:" << reply << endl;
    } 
}

//Reads the 2nd line until end of the .txt file and sends it to be printed.
void readToPrintLines(int indexCount, int numberLines)
{
    int agentFirstDigit, agentSecondDigit;
    string userSays;
    scanf("%d %d", &agentFirstDigit, &agentSecondDigit);
    getline(cin, userSays);
    printLines(indexCount, numberLines, agentFirstDigit, agentSecondDigit, userSays);
}

//Starts the program.
int main(void)
{
    int numberLines = defineNumberOfLines();
    for(int i = 0; i < numberLines; i++)
    {
        readToPrintLines(i, numberLines);
    }
    return 0;
}

//g++ -o lab2 lab2.cpp
// .\lab2 < textFile.txt