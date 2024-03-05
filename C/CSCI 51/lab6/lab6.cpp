#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

using namespace std;

string getDateAndTime() //https://stackoverflow.com/questions/5438482/getting-the-current-time-as-a-yyyy-mm-dd-hh-mm-ss-string/5438502
{
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer[80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"[%Y-%m-%d] %H:%M:%S",timeinfo);
    return buffer;
}

void printLoopDateTime(int i)
{
    sleep(10);
    cout << getDateAndTime() << endl;
    if(i == 2)
    {
        cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
        printLoopDateTime(0);
    }
    else
    {
        printLoopDateTime(i+1);
    }
}


int main(int argc, char* argv[])
{
    int forkRet = fork();
    if(forkRet < 0)
    { //error
        exit(1);
    }
    else if(forkRet == 0)
    { //child
        if(execl("/usr/bin/xclock","myXclock", NULL) == -1)
        {
            exit(1);
        }
    }
    else
    { //parent
        cout << getDateAndTime() << endl;
        printLoopDateTime(1);
    }
    return 0;
}