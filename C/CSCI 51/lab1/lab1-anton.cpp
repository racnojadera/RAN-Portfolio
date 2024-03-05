
#include <iostream>

using namespace std;

string getNextLetter(char *letter)
{
    char lowAlphabetArr[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char upAlphabetArr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    bool letterExist = false;

    //checks if letter is in alphabet
    for (int i = 0; i < 26; i++)
    {
        if ((*letter == lowAlphabetArr[i]) || (*letter == upAlphabetArr[i]))
        {
            letterExist = true;
        }
    }
    if (!letterExist)
    {
        return std::string(1, *letter);
    }
    for (int i = 0; i < 26; i++)
    {
        if (*letter == lowAlphabetArr[i] && i != 25)
        {
            string newLetter = std::string(1, lowAlphabetArr[i + 1]);
            return newLetter;
        }
        else if (*letter == lowAlphabetArr[i] && i == 25)
        {
            string newLetter = std::string(1, lowAlphabetArr[0]);
            return newLetter;
        }
        if (*letter == upAlphabetArr[i] && i != 25)
        {
            string newLetter = std::string(1, upAlphabetArr[i + 1]);
            return newLetter;
        }
        else if (*letter == upAlphabetArr[i] && i == 25)
        {
            string newLetter = std::string(1, upAlphabetArr[0]);
            return newLetter;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    string stringName;

    //input string name
    cin >> stringName;

    //first output
    cout << stringName << endl;

    //this will output the first letter then # for succeeding letters. It will only end the line after the for loop
    for (int i = 0; i < stringName.length(); i++)
    {
        if (i == 0)
        {
            cout << stringName[0];
        }
        else
        {
            cout << "#";
        }
    }
    cout << endl;

    string stringNew;
    //this will call the getNextLetter function and output the results. It will only end the line after the for loop
    for (int i = 0; i < stringName.length(); i++)
    {
        stringNew += getNextLetter(&stringName[i]);
    }
    
    cout << stringNew;
    cout << endl;
    return 0; // non-zero means an error
}
