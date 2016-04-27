# beatty_CSCI2270Final

## Team
Dawson Beatty, working alone

## Project
Will be making a rudimentary spell checker, using a giant tree of more than 100,000 English words. Reads in words from a preexisting text file. Stores all of the words in a large "trie", which will be explained later. Includes options for searching for individual words, adding new words, and printing specific subsets of the dictionary.

Possible problems include efficiently searching such a large structure, and organization. 

### Issues/Bugs
There's a bug in the spell checker that will create a seg fault if there's punctuation at the end of the line.  It's a problem in the for loop of the removePunct() function.  If you fix it you'll be my favorite person. Also if you're feeling lazy you can just report that as a bug and let me sort it out later.  

## Use Instructions
Make sure that the wordsEn.txt is in the path, since that's where all the words are read in from. 

The menu will open up upon running the program. 
1. Printing the dictionary is more for a sense of scale than any practical purposes. The user can gaze in awe at the thousands of lines of words that the masterful dictionary contains. 
2. Search for a word to see whether or not it's in the dictionary. Returns yes or no.  IF no, the user has the option to add the word to the dictionary for the current session.
3. Print Disctionary Subset gives lots of options for which section of the dictionary the user wishes to see.  To view all three letter words starting with J, for example, the user would input "J" as the prefix, and 3 as the min and max length of the word. 
4. Traverse Dictionary was built as a debugging tool, but I left it in because deleting a line is beyond the scope of my talents. This gives the user the ability to see how the tree is organized, branching from letter to letter.
5. The part bringing the whole thing together is the spell checker

## Dependencies
If you want a non-empty dictionary, make sure that wordsEn.txt is in your path. It's included in the submission, but you can get it here http://www-01.sil.org/linguistics/wordlists/english/ as well if you're feeling mistrustful of teext files. 

## System Requirements
Code was writted on Windows, should work fine on all other operating systems. Probably. No promises. 

## Data Structure Concept
A "trie" was used, which optimizes for fast reTRIEval. A trie has many similarities to a binary search tree, with the key difference being that a trie can have a theoretically unlimited number of children.  Each letter of a word gets its own node, with pointers to longer words down the chain.  In terms of data storage this system borders on war crime for its hideous inefficiency, but the principle behind the data structure is completely valid. 

## Future Options
Could append user added words to the bottom of the text file so dictionary will last more than one session.
