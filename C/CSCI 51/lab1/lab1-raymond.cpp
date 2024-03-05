#include <iostream>
using namespace std;

//Asks the user for an input.
string getName()
{
    string username;
    cin>>username;
    return username;
}

//Replaces the 2nd letter until the last letter of the user's input with "#".
string modifyHash(string nameorig)
{
    string namemodified = nameorig;
    for(int i = 1; i < namemodified.length(); i++)
    {
        namemodified[i] = '#';
    }
    return namemodified;
}

//Shifts letter characters to the next letter in the same category (uppercase/lowercase). Ignores if character is not a letter.
char modifyShift(char *letterorig)
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

//Displays the original user input, the #'ed version, and the shifted version.
void displayOutputs(string nameorig, string namehashed, string nameshifted)
{
    cout<<nameorig<<endl;
    cout<<namehashed<<endl;
    cout<<nameshifted<<endl;
}

//Starts the program.
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
