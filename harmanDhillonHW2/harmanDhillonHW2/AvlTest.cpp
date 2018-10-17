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
	string singleLine;
	string singleWord;
	char singleChar;

	cout << "Please enter the name for the file you want to spell check ---> " << endl;
	cin >> fileName;

	textFileName = fileName + ".txt";
	dictionaryFileName = fileName +  ".dct";

	cout << textFileName << " || " << dictionaryFileName << endl;

	ifstream textFile;
	ifstream dictionaryFile;
	textFile.open(textFileName);
	dictionaryFile.open(dictionaryFileName);
	if (textFile.is_open())
	{
		while (getline(textFile, singleLine))
		{
			for (int i = 0; i < singleLine.length(); ++i)
			{
				singleChar = tolower(singleLine[i]);
				if (isalpha(singleChar))
					singleWord += singleChar;
				else
				{
					cout << singleWord << endl;
					cout << "||";
					//words.insert(singleWord);
					singleWord = "";
				}	
			}		
		}
		textFile.close();
	}
	else cout << "File error, when attempting to open the given text file." << endl;


	//if (dictionaryFile.is_open())
	//{
	//	while (getline(dictionaryFile, singleWord))
	//	{
	//		if (words.find(singleWord) != ITEM_NOT_FOUND)
	//		{
	//			words.remove(singleWord);
	//		}
	//	}
	//	dictionaryFile.close();
	//}
	//else cout << "File error, when attempting to open the given dictionary file." << endl;

	//cout << "SIZE: " << words.getAVLTreeSize();

	//ofstream fileWriter("errorFile.txt");
	//fileWriter << "Error File" << endl;

	//words.printTree();

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