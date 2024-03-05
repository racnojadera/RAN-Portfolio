#include <iostream>

using namespace std;

int addTwoV1(int x)
{
    x += 2;
    return x;
}

int addTwoV2(int *x)
{
    *x += 2;
    return *x;
}

int main(int argc, char *argv[])
{
    int *p;
    cout << "V1: " << addTwoV1(5) << endl;
    cout << "V2: " << addTwoV2(p) << endl;
    return 0; // non-zero means an error
}