// spellcheck.cpp 
// This doesn't do any spell checking yet; it's just a simple test of the AVL-based Table ADT.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AvlTree.h"
using namespace std;

const string ITEM_NOT_FOUND = "99999";

int main()
{
	AvlTree<string> words(ITEM_NOT_FOUND);  // constructs an empty tree of ints that returns 99999 when find fails

	string fileName;
	string textFileName;
	string dictionaryFileName;
	ifstream textFile;
	ifstream dictionaryFile;
	string singleLine;
	string singleWord;
	char singleChar;

	cout << "Please enter the name for the file you want to spell check ---> " << endl;
	cin >> fileName;
	textFileName = fileName + ".txt";
	cout << "Please enter the name for of the dictionary you want to use to check ---> " << endl;
	cin >> fileName;
	dictionaryFileName = fileName +  ".dct";

	textFile.open(textFileName);
	dictionaryFile.open(dictionaryFileName);
	if (textFile.is_open())
	{
		while (getline(textFile, singleLine))//going line by line in the text file
		{
			singleLine += "#";// used to detect newlines
			for (int i = 0; i < singleLine.length(); ++i)//going char by char in the single line
			{
				singleChar = tolower(singleLine[i]);// converting to lowercase if char is uppercase
				if (isalpha(singleChar))//checking if char thats lowercase is a letter
					singleWord += singleChar;//adding it too the word
				else
				{
					words.insert(singleWord);//inserting the word to the avl tree
					singleWord = "";//resetting the word
				}	
			}		
		}
		textFile.close();
	}
	else cout << "File error, when attempting to open the given text file." << endl;


	if (dictionaryFile.is_open())
	{
		while (getline(dictionaryFile, singleWord))
		{
			if (words.find(singleWord) != ITEM_NOT_FOUND)
			{
				words.remove(singleWord);
			}
		}
		dictionaryFile.close();
	}
	else cout << "File error, when attempting to open the given dictionary file." << endl;

	cout << "SIZE: " << words.getAVLTreeSize();

	ofstream fileWriter("errorFile.txt");
	fileWriter << "Error File" << endl;

	words.printTree();

	char c;
	cin >> c;

	/*
	words.insert(4);
	words.insert(6);
	words.insert(9);
	words.insert(12);
	words.insert(2);

	if (words.find(9) != ITEM_NOT_FOUND)
		cout << "Find was sucessful." << endl;

	words.remove(9);

	cout << "number removed: " << words.getAVLTreeSize();

	cout << endl << endl;

	words.printTree();

	cin.get();  // wait for enter key
	*/
	return EXIT_SUCCESS;
}