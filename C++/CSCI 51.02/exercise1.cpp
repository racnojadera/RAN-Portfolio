#include <iostream>
using namespace std;

/*
//1.
int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++)
    {
        cout<<"arg"<<i<<":"<<argv[i];
        cout<<endl;
    }
    return 0;
}*/


//2.
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        string argName = argv[i];
        string argNamePost = "";
        // cout << argName;
        for (int j = argName.length() - 1; j >= 0; j--)
        {
            argNamePost += argv[i][j];
        }

        cout << "arg" << i << ": " << argNamePost;
        cout << endl; // cout << "\n";

        // printf("%c\n", argv[i][0]);
    }
    return 0; // non-zero means an error
}

/*
//3. null pointer exception???
*/