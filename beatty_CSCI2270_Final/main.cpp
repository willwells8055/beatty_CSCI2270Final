#include <iostream>
#include "alphabet.h"

using namespace std;

alphabet dict; //Create instance of dictionary

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
    cout << endl << endl;
    cout << "====== Main Menu ======" << endl;
    cout << "1. Print Dictionary" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Print Dictionary Subset" << endl; //Could do by length, first letter or two, etc.
    cout << "4. Traverse Dictionary" << endl;
    cout << "5. Spell Check" << endl;
    cout << "6. Quit" << endl;
    cin >> choice;

    switch(choice)
    {
    case 1:
        {
            dict.recurPrint();  //Prints all the words in the dictionary. Mostly for sense of scale
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
            if(!found->isLeaf)
            {
                cout << endl;
                cout << "\"" << target << "\"" << " was not found" << endl;
                cout << "Do you wish to add it to the dictionary? Y/N" << endl;
                cin >> yn;
                if(yn.compare("y") == 0 || yn.compare("Y") == 0)
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
                cout << endl;
                cout << "Yes, " << "\"" << target << "\"" << " is a word." << endl;
            }
            break;
        }
    case 3:
        {
            int toolChoice, maxOut, minOut;
            string prefix;
            letter* foundWord;
            cout << endl;
            cout << "=== Dictionary Subset Tool===" << endl;
            cout << "1. Specify prefix" << endl;
            cout << "2. Words of certain length" << endl;
            cout << "3. Both of the above" << endl;
            cout << "4. Back" << endl;
            cin >> toolChoice;
            switch(toolChoice)
            {
            case 1:
                {
                    cin.ignore();
                    cout << "Enter the prefix: " << endl;
                    cin >> prefix;
                    dict.recurPrint(prefix);
                    break;
                }
            case 2:
                {
                    cin.ignore();
                    cout << "Enter the maximum length of the word" << endl;
                    cin >> maxOut;
                    cout << "Enter the minimum length of the word" << endl;
                    cin >> minOut;
                    dict.recurPrint("", minOut, maxOut);
                    break;
                }
            case 3:
                {
                    cin.ignore();
                    cout << "Enter a prefix: " << endl;
                    getline(cin,prefix);
                    cout << "Enter the maximum length of the word" << endl;
                    cin >> maxOut;
                    cout << "Enter the minimum length of the word" << endl;
                    cin >> minOut;
                    cout << maxOut << minOut << endl;
                    if(minOut < 0 || maxOut < 0)
                    {
                        cout << "Please enter positive values, or 0." << endl;
                        break;
                    }
                    dict.recurPrint(prefix, minOut, maxOut);
                    break;
                }
            default:
                {
                    break;
                }
            }
            break;
        }
    case 4:
        {
            dict.traverseDict();
            break;
        }
    case 5:
        {
            string sentence;
            cin.ignore();
            cout << "Enter a word or sentence you want to check the spelling of: " << endl;
            getline(cin, sentence);
            dict.spellCheck(sentence);
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
