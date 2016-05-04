#include "alphabet.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <ctype.h>

using namespace std;

alphabet::alphabet()
{
    head.parent = nullptr;

    head.isLeaf = false;

    MAX_LENGTH = 0;

    ifstream infile("wordsEn.txt");

    string wordIn;

    while(getline(infile,wordIn))
    {
        if(wordIn.length() > MAX_LENGTH)
        {
            MAX_LENGTH = wordIn.length();
        }
        alphabet::addWord(wordIn);
    }

    addWord("i");  //Wasn't in the dictionary for some reason
}

alphabet::~alphabet()
{
    //dtor
}

std::string alphabet::makeLower(std::string lower) //Be sure to put this in front of all inputs
{
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

letter* alphabet::findWord(std::string target) //Only returns if it's a word.  Fudge.
{
    target = makeLower(target);
    letter* temp = new letter;
    temp = &head;
    bool found = false;
    for(int i {}; i < target.length(); i++)
    {
        for(int j {}; j < temp->children.size(); j++)
        {
            found = false;
            if(target[i] == temp->children[j]->key)
            {
                found = true;
                temp = temp->children[j];
                break;
            }
        }
        if(!found)
        {
            return nullptr;
        }
    }
    return temp;
}

letter* alphabet::addLetter(letter* parent, char baby)
{
    letter* newLetter = new letter;
    newLetter->key = baby;
    newLetter->parent = parent;
    parent->children.push_back(newLetter);
    return newLetter;
}

void alphabet::addWord(std::string name)
{
    //cout << "Adding " << name << endl; //Uncomment this if you want
    letter* temp = new letter;
    letter* newLetter;
    temp = &head;
    bool found;
    for(int i {}; i < name.length(); i++) //Go through each letter in the word
    {
        found = false;
        for(int j {}; j < temp->children.size(); j++) //Sorting through each child
        {
            if(name[i] == temp->children[j]->key)
            {
                found = true;
                temp = temp->children[j];
                break;
            }
        }
        if(!found) //If the letter isn't found, next letter isn't among children
        {
            // Have to make a new letter here

            newLetter = addLetter(temp, name[i]);
            temp = newLetter;
            if(i == name.length() - 1)
            {
                break;
            }
        }
    }
    //If we reach this point, we found the last letter of the word
    if(!temp->isLeaf)
    {
        //cout << "Making " << name << " leaf." << endl;
        temp->word = name;
        temp->isLeaf = true;
    }
    return;
}

void alphabet::traverseDict()
{
    letter* temp = new letter;
    temp = &head;
    bool done = false;
    int choice;
    while(!done)
    {
        cout << endl;
        cout << endl;
        cout << "Current Letter: " << temp->key << endl;
        cout << "Current Letter is leaf? " << temp->isLeaf << endl;
        if(temp->isLeaf)
        {
            cout << "Word: " << temp->word << endl;
        }
        cout << "Press the child number, or \'0\' to go to parent. " << endl;
        cout << "Negative number to quit." << endl;
        cout << "Parent: " << ((temp->parent == nullptr)? ' ':temp->parent->key)  << endl;
        cout << "Children: " << endl;
        for(int i {}; i < temp->children.size(); i++)
        {
            cout << i+1 << ": " << temp->children[i]->key << endl;
        }
        cin >> choice;
        // if user didn't input a number
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); //skip bad input
            //request new input
            cout<<"Please enter a valid input"<<endl;
            cin>>choice;
        }
        if(choice == 0)
        {
            if(temp == &head)
            {
                cout << "You\'re already at the head of the dictionary!" << endl;
                continue;
            }
            temp = temp->parent;
        }
        else if(choice < 0)
        {
            done = true;
        }
        else
        {
            temp = temp->children[choice-1];
        }

    }
    return;
}


void alphabet::recurPrint(letter* start, int minLength, int maxLength) //If don't provide pointer, start at head
{

    if(start->isLeaf && start->word.length() <= maxLength && start->word.length() >= minLength)
    {
        if(start->word.length() != 0)
        {
            cout << start->word << endl;
        }
    }
    for(int i {}; i < start->children.size(); i++)
    {
        recurPrint(start->children[i], minLength, maxLength);
    }
    return;
}


void alphabet::recurPrint(std::string startStr, int minLength, int maxLength) //Called in main
{
    letter* inPtr;
    startStr = makeLower(startStr);
    if(startStr.compare("") == 0)
    {
        inPtr = &head;
    }
    else
    {
        inPtr = findWord(startStr);
        if(inPtr == nullptr)
        {
            cout << "\"" << startStr << "\" was not found." << endl;
            return;
        }
    }
    if(maxLength == 100)
    {
        maxLength = MAX_LENGTH;
    }
    recurPrint(inPtr, minLength, maxLength);
    return;
}

string alphabet::removePunct(std::string str)
{
    for(int i {}; i < str.length(); i++)
        {
            if(int(str[i]) == 39 || isalpha(str[i]) || int(str[i]) == 32)
            {
                continue;
            }
            else
            {
                str.erase(str.begin()+i,str.begin()+i+2);  //PROBLEM CHILD
            }
        }
    return str;
}

void alphabet::spellCheck(std::string sentence)
{
    letter* currentWord;
    char yn;
    sentence = makeLower(sentence);
    sentence = removePunct(sentence); //Takes care of numbers as well
    vector<string> wordList;
    stringstream ss(sentence);
    string token;

    while(getline(ss,token, ' '))
    {
        wordList.push_back(token);
    }

    for(int i {}; i < wordList.size(); i++)
        {
            currentWord = findWord(wordList[i]);
            if(!currentWord->isLeaf)
            {
                cout << "The word \"" << wordList[i] << "\" was not found. \n Add to dictionary? Y/N: "<< endl;
                cin >> yn;
                if(yn == 'Y' || yn == 'y')
                {
                    addWord(wordList[i]);
                    cout << "Succesfully added \"" << wordList[i] << "\" to dictionary." << endl;
                }
            }
        }

    cout << "Spell check complete!" << endl;
    return;
}
