#include <cstdlib>
#include <iostream>
using namespace std;

int main(void) {
    int x;
    cout << "Enter an integer: ";
    //non-integer values read as 0
    //float values are disposed of their decimal values/values less than 1.
    
    cin >> x; // cin >> name; CSCI 51.02 ...
    cout << "Received input: " << x;
    cout << endl << "Added 2, now: ";
    cout << (x+2) << endl;
    return 0;
}