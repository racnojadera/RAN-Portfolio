#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

void agentInformation(int agentNumber, int firstLocation, int secondLocation, string saysString)
{
    printf("Agent #%d is at (%d, %d)\n", agentNumber+1, firstLocation, secondLocation);
    cout << "Says:" << saysString << endl;
}

int main(void)
{
    string line;
    getline(cin, line);
    int lineCount;
    lineCount = atoi(line.c_str());

    for (int i = 0; i < lineCount; i++)
    {
        int firstLocation;
        int secondLocation;
        string saysString;

        scanf("%d %d", &firstLocation, &secondLocation);
        getline(cin, saysString);

        agentInformation(i+1, firstLocation, secondLocation, saysString);
    }
    return 0;
}