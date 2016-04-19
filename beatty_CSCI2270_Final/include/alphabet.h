#ifndef ALPHABET_H
#define ALPHABET_H
#include <vector>
#include <string>

struct letter
{
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
        void recurPrint(std::string start);
        void recurPrint(letter* start);
    protected:
    private:
        letter head;
};

// TODO
//1. Finish readMe

#endif // ALPHABET_H
