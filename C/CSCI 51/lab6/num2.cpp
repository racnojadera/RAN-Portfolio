#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

// just use execv to run ANY program

if(execl( "/usr/bin/dasdasdlab", "boop", NULL ) == -1) {

// error

cout << "Error. Booooo!" << endl;

}

cout << "Will this line still be printed?" << endl;

}