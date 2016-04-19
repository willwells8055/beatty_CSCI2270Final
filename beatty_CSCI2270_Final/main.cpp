#include <iostream>
#include "alphabet.h"

using namespace std;

alphabet dict;

bool menuDisp();

int main()
{
    bool menuAgain = true;
    while(menuAgain)
    {
        menuAgain = menuDisp();
    }
    return 0;
}

bool menuDisp()
{
    int choice;
    cout << "====== Main Menu ======" << endl;
    cout << "1. Print Dictionary" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Print Dictionary Subset" << endl; //Could do by lenth, first letter or two, etc.
    cout << "4. Traverse Dictionary" << endl;
    cout << ". Quit" << endl;
    cin >> choice;

    switch(choice)
    {
    case 1:
        {
            break;
        }
    case 2:
        {
            letter* found = new letter;
            string target;
            string yn;
            cin.ignore();
            cout << "Enter the word you wish to find: " << endl;
            cin >> target;
            found = dict.findWord(target);
            if(found == nullptr)
            {
                cout << "\"" << target << "\"" << " was not found" << endl;
                cout << "Do you wish to add it to the dictionary? Y/N" << endl;
                cin >> yn;
                if(yn.compare("y") == 0 || yn.compare("Y"))
                {
                    dict.addWord(target);
                    cout << "\"" << target << "\"" << " was added to the dictionary" << endl;
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "Yes, " << "\"" << target << "\"" << " is a word." << endl;
            }
            break;
        }
    case 3:
        {
            break;
        }
    case 4:
        {
            dict.traverseDict();
            break;
        }
    default:
        {
            return false;
            break;
        }
    }
    return true;
}
