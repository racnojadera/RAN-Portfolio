#include <iostream>
using namespace std;

int main(void)
{
    
    int i;
    int *p;
    p = &i;

    for(i = -5; i<=5; i++)
    {
        p = &i;
        cout << "int i = " << i << endl;
        cout << "pointer p: " << p << endl;
        cout << "address of i: " << &i << endl;
        cout << "dereference p: " << *p << endl;
        cout << endl;
    }
}