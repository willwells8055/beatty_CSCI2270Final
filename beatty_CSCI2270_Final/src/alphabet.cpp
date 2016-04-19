#include "alphabet.h"
#include <fstream>
#include <iostream>

using namespace std;

alphabet::alphabet()
{
    head.parent = nullptr;

    ifstream infile("wordsEn.txt");

    string wordIn;

    while(getline(infile,wordIn))
    {
        alphabet::addWord(wordIn);
    }
}

alphabet::~alphabet()
{
    //dtor
}

letter* alphabet::findWord(std::string target)
{
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
    if(temp->isLeaf)
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
}

void alphabet::addWord(std::string name)
{
    cout << "Adding " << name << endl;
    letter* temp = new letter;
    temp = &head;
    bool found;
    for(int i{}; i < name.length(); i++) //Go through each letter in the word
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
            { // Have to make a new letter here
                letter* newLetter = new letter;
                newLetter->key = name[i];
                newLetter->parent = temp;
                temp->children.push_back(newLetter);
                if(i == name.length() - 1)
                {
                    break;
                }
            }
        }
        //If we reach this point, we found the last letter of the word
        if(!temp->isLeaf)
        {
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
        cout << "Current Letter: " << temp->key << endl;
        cout << "Current Letter is leaf? " << temp->isLeaf << endl;
        cout << "Press the child number, or \'0\' to go to parent. " << endl;
        cout << "Negative number to quit." << endl;
        cout << "Parent: " << ((temp->parent == nullptr)? ' ':temp->parent->key)  << endl;
        cout << "Children: " << endl;
        for(int i{}; i < temp->children.size(); i++)
            {
                cout << i << ": " << temp->children[i]->key << endl;
            }
        cin >> choice;
        if(choice == 0)
        {
            temp = temp->parent;
        }
        else if(choice < 0)
        {
            done = true;
        }
        else
        {
            temp = temp->children[choice];
        }
    }
    return;
}

void alphabet::recurPrint(letter* start) //Modify this, will need to pass string up
{
    for(int i{}; i < start->children.size(); i++)
        {

        }
}

void alphabet::recurPrint(std::string start)
{
    letter* temp = new letter;
    if(start == "00000000")
    {
        temp = &head;
    }
    else
    {
        temp = findWord(start);
    }

}
