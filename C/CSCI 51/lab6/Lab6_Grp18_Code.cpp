
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int count = 0;
void printDateTime(int counter)
{
    time_t now = time(0);

    tm *ltm = localtime(&now);

    // [yyyy-mm-dd] hh:mm:ss

    // print various components of tm structure.
    cout << "[" << 1900 + ltm->tm_year;
    if(1 + ltm->tm_mon < 10)
    {
        cout << "-0"<< 1 + ltm->tm_mon;
    }
    else
    {
        cout << "-"<< 1 + ltm->tm_mon;
    }
    if(ltm->tm_mday < 10)
    {
        cout << "-0"<< ltm->tm_mday;
    }
    else
    {
        cout << "-"<< ltm->tm_mday;
    }

    cout << "] "<< ltm->tm_hour << ":";
    if(ltm->tm_min < 10)
    {
        cout << "0"<< ltm->tm_min;
    }
    else
    {
        cout << ltm->tm_min;
    }

    if(ltm->tm_sec < 10)
    {
        cout << ":0" << ltm->tm_sec << endl;
    }
    else
    {
        cout << ":" << ltm->tm_sec << endl;
    }

    if(counter == 3)
    {
        cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
        count = 0;
    }
}

int main( void ){
    int forkRet = fork();
    if( forkRet < 0 )
    { //error
        exit( 1 );
    }
    else if( forkRet == 0 )
    { //Child process
        // cout << "I'm a kid process!\nMy ID is " << getpid() << ".\n";
        execl("/usr/bin/xclock", "myXClock", NULL);
        // execv( "/usr/bin/xclock", argv );
    }
    else 
    { //Parent process 
        // cout << "Parent ID: " << getpid() << ",\nfork() returned " << forkRet << ".\n";
        while(true)
        {
            count++;
            printDateTime(count);
            sleep(3);
        }
    }
    return 0;
}
