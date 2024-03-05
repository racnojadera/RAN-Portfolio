#include <iostream>
#include <string>
using namespace std;

string getName()
{
    string username;
    cin>>username;
    return username;
}

string modifyHash(string nameorig)
{
    string namemodified = nameorig;
    for(int i = 1; i < namemodified.length(); i++)
    {
        namemodified[i] = '#'; //https://www.w3schools.com/cpp/cpp_strings_access.asp
    }
    return namemodified;
}

char modifyShift(char *letterorig) //https://www.learncpp.com/cpp-tutorial/chars/
{
    char *lettermodified = letterorig;
    bool uppercased = (*lettermodified >= 'A' && *lettermodified <= 'Z');
    bool lowercased = (*lettermodified >= 'a' && *lettermodified <= 'z');
    
    if(uppercased || lowercased)
    {
        *lettermodified += 1;
        if((*lettermodified == 'z' + 1) || (*lettermodified == 'Z' + 1))
        {
            *lettermodified -= 26;
        }
    }
    return *lettermodified;
}

void displayOutputs(string nameorig, string namehashed, string nameshifted)
{
    cout<<nameorig<<endl;
    cout<<namehashed<<endl;
    cout<<nameshifted<<endl;
}

int main(void)
{
    string name_input, name_hashed, name_shifted;
    name_input = getName();
    name_hashed = modifyHash(name_input);
    name_shifted = name_input;

    for(int i = 0; i < name_input.length(); i++)
    {
        modifyShift(&name_shifted[i]);
    }
    
    displayOutputs(name_input, name_hashed, name_shifted);
    return 0;
}