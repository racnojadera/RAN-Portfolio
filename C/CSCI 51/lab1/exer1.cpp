#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        string argName = argv[i];
        string argNamePost = "";

        for (int j = argName.length() - 1; j >= 0; j--)
        {
            argNamePost += argv[i][j];
        }

        cout << "arg" << i << ": " << argNamePost;
        cout << endl; // cout << "\n";
    }
    return 0; // non-zero means an error
}