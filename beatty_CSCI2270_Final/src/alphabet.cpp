#include "alphabet.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

alphabet::alphabet()
{
    head.parent = nullptr;

    head.isLeaf = false;

    //int longest = 0;

    ifstream infile("wordsEn.txt");

    string wordIn;

    while(getline(infile,wordIn))
    {
        /*if(wordIn.length() > longest)
        {
            longest = wordIn.length();
        } */
        alphabet::addWord(wordIn);
    }
    //cout << "Longest word is " << longest << " characters." << endl;
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

letter* alphabet::findWord(std::string target)
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
    if(temp->isLeaf)
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
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
    cout << "Adding " << name << endl;
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

void alphabet::recurPrint(letter* start, int minLength = 0, int maxLength = 20) //If don't provide pointer, start at head
{
    if(start->isLeaf)
    {
        cout << start->word << endl;
    }
    for(int i {}; i < start->children.size(); i++)
    {
        recurPrint(start->children[i]);
    }
    return;
}

void alphabet::recurPrint(int minLength, int maxLength)
{
    recurPrint(&head, minLength, maxLength);
}

/*
void alphabet::recurPrint(std::string start)
{
    //This is how we start the whole thing
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
*/
