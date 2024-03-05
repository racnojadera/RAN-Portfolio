#include <iostream>
using namespace std;
 
// A method to multiply two numbers using Russian Peasant method
int russianPeasant(int a, int b)
{
    int res = 0; // initialize result
 
    // While second number doesn't become 1

    if (b < 0){
        
        while (b > 0)
        {
            // If second number becomes odd, add the first number to result
            if (b % 2 == 1)
                res += a;
    
            // Double the first number and halve the second number
            a = a << 1;
            b = b >> 1;
        }

        return res;
    }
    else if (b > 0){
        while (b > 0)
        {
            // If second number becomes odd, add the first number to result
            if (b % 2 == 1)
                res = res + a;
    
            // Double the first number and halve the second number
            a = a << 1;
            b = b >> 1;
        }
        return res;
    }
    return res;
}
 
// Driver program to test above function
int main()
{
    cout << russianPeasant(-18, -1) << endl;
    cout << russianPeasant(-20, 12) << endl;
    return 0;
}