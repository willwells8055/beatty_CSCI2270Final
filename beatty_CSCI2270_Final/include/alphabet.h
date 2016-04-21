#ifndef ALPHABET_H
#define ALPHABET_H
#include <vector>
#include <string>

struct letter
{
    std::string word;
    char key;
    std::vector<letter*> children; //Up to 26 children
    letter* parent;
    bool isLeaf;
};

class alphabet
{
    public:
        alphabet();
        ~alphabet();
        void addWord(std::string name);
        void dictTraverse();
        letter* findWord(std::string target);
        void traverseDict();
        void recurPrint(std::string startStr = "", int minLength = 0, int maxLength = 100);//version for main.cpp
        void recurPrint(letter* start, int minLength, int maxLength); //Version for alphabet.cpp
        std::string makeLower(std::string lower);
        letter* addLetter(letter* parent, char baby);
        void spellCheck(std::string sentence);
        std::string removePunct(std::string str);
    protected:
    private:
        letter head;
        int MAX_LENGTH;
};

// TODO
//1. Finish readMe
//2. Fix Lindsay's "wal" prefix bug.  :(

#endif // ALPHABET_H
