#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

int main (void){
    int sum = 0, cases = 0, lines = 0, lineCount = 0, count = 0;
    int x, y, z;

    cin >> cases;
    cin >> lines;

    int pointData[lines][3];

    for(int i = 0; i < cases; i++){
        while(lineCount < lines)
        {
            
            // cin >> x;

            scanf("%d %d %d", &x, &y, &z);
            pointData[lineCount][0] = x;
            pointData[lineCount][1] = y;
            pointData[lineCount][2] = z;

            // istringstream ss(x);
            // string dataStore;
            
            // while(ss >> dataStore)
            // {
            //     pointData[lines][count] = std::stoi(dataStore);
            //     count++;
            // }
            lineCount++;
        }
        for(int j = 0; j < lineCount - 1; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                sum += abs(pointData[j][k] - pointData[j+1][k]);
            }
            cout << sum << endl;
            sum = 0;
        }
        // reset linecount
        lineCount = 0;

        if(i == cases - 1)
        {
            break;
        }
        else
        {
            cin >> lines;
        }
    }
}