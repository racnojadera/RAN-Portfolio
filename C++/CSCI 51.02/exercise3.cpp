#include <iostream>
using namespace std;

int addTwoV1(int x)
{
    x += 2;
    return x;
}

int addTwoV2(int* x)
{
    *x += 2;
    return *x;
}

void displayValues(int x, int y)
{
    cout << "The value for V1 is: " << x << endl;
    cout << "The value for V2 is: " << y << endl;
}

int main(void)
{
    int value1 = 10;
    int value2 = value1;

    displayValues(value1, value2);
    return 0;
}