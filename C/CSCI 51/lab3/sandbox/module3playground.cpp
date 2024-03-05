#include <iostream>
#include "Point3D.hpp"

using namespace std;

int main(void)
{
    // Point3D p;
    // Point3D *q;
    // p.x = 5;
    // p.y = -2;
    // p.z = 999;
    // cout << p.x << endl;

    // //displays 0 since it's not assigned to any variables yet
    // cout << q << endl;

    // q = &p;
    // //displays memory location of variable p
    // cout << q << endl;

    // q->x = 1000; //same as (*q).x
    // //displays value of x since you're dereferencing q
    // cout << (*q).x << endl;

    Point3D *p = new Point3D(7, 7, 7);
    cout << p->x << " " << p->y;
    cout << " " << p->z << endl;
    delete p;
    p = NULL;
    return 0;
}
