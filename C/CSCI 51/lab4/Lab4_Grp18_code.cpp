#include <iostream>
#include <cstdlib>

using namespace std;
 
int russianPeasant(int x, int y)
{
    int answer = 0;

    // if x is positive and y is negative switch x and y
    if (x>0 && y<0){
        int temp;
        temp = y;
        y = x;
        x = temp;
    }

    // if x and y are both negative, get their absolute values
    // since when two negative numbers are multiplied the answer would
    // be same if they were both positive numbers
    if (x<0 && y<0 ){
        x = abs(x);
        y = abs(y);
    }

    // main russian peasant algorithm
    while (y > 0)
    {
        // If y is odd, add the first number to answer
        if (y & 1)
            answer = answer + x;
 
        // Double x and Half y
        x = x << 1;
        y = y >> 1;
    }
    return answer;
}
 
int main()
{
    int x, y;
    cout << "Enter First Integer:"  << endl;
    cin >> x;
    cout << "Enter Second Integer:"  << endl;
    cin >> y;
    cout << "\n" << x << " * " << y << " = " << russianPeasant(x,y) << endl;
    return 0;
}