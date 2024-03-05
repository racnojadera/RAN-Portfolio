#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;


//answers are written on this array


//creates a Point3D structure containing values x, y, z
struct Point3D
{
    int x;
    int y;
    int z;
};

//gets the amount of cases provided by the user
int getCasesInput()
{
    int UserInput;
    cin >> UserInput;
    return UserInput;
}

//gets the amount of lines provided by the user
int getLinesInput()
{
    int UserInput;
    cin >> UserInput;
    return UserInput;
}

//sets the values of a point based on the user's input
Point3D getPointCoordFromLine()
{
    Point3D currpoint;
    scanf("%d %d %d", &currpoint.x, &currpoint.y, &currpoint.z);
    return currpoint;
}

//calculates the manhattan distance between two points
int getManhattanDistance(Point3D a, Point3D b)
{
    int sum, absdiffx, absdiffy, absdiffz;
    absdiffx = abs(a.x - b.x);
    absdiffy = abs(a.y - b.y);
    absdiffz = abs(a.z - b.z);
    sum = absdiffx + absdiffy + absdiffz;
    return sum;
    //cout << sum << "\n" << endl;
}

//asks the user for the number of lines per case, and prints the manhattan distance of 2 points.
string getCoordinateInputsAndPrintManhattanDistance(int a, Point3D pointA, Point3D pointB)
{
    a = getLinesInput();
    string answer;
    for(int i = 0; i < a - 1; i++)
    {
        if(i!=0)
        {
            pointA = pointB;
        } else
        {
            pointA = getPointCoordFromLine();
        }
        pointB = getPointCoordFromLine();
        answer += to_string(getManhattanDistance(pointA, pointB)) + "\n";
    }
    return answer;
}


int main(void)
{
    int cases, lines;
    string finalAnswer;
    Point3D point1, point2;
    
    cases = getCasesInput();
    for(int i = 0; i < cases; i++) //loops the code based on how many cases there are
    {
        finalAnswer += getCoordinateInputsAndPrintManhattanDistance(lines, point1, point2); 
    }
    cout << "\n" << finalAnswer;
    return 0;
}