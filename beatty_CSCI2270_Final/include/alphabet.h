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
        void recurPrint(letter* start, int minLength, int maxLength);
        void recurPrint(int minLength = 0, int maxLength = 28);
        std::string makeLower(std::string lower);
        letter* addLetter(letter* parent, char baby);
        //void recurPrint();
    protected:
    private:
        letter head;
};

// TODO
//1. Finish readMe

#endif // ALPHABET_H
