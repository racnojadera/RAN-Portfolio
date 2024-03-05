#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    string s, sTwo;
    char sThree[80], sFour[80]; // limit of 80 characters
    cout << "Input a string: ";

    // cin >> s;
    getline(cin, sTwo);
    // scanf("%s", sThree);
    // fgets(sFour, 80, stdin);

    // cout << "(cin)You typed: " << s << endl;
    cout << "(getline)You typed: " << sTwo << endl;
    // printf("(scanf,printf)You typed: %s\n", sThree);
    // printf("(fgets,printf)You typed: %s\n", sFour);
    return 0;
}
