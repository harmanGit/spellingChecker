// spellcheck.cpp 
// This doesn't do any spell checking yet; it's just a simple test of the AVL-based Table ADT.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AvlTree.h"
using namespace std;

const string ITEM_NOT_FOUND = "99999";
ofstream fileWriter;

struct word 
{
	string wordValue;
	int line;
	int numberOfOccurrences;
};


void writeErrorFile(string &s)
{	
	fileWriter << s << endl;
}

void resetWord(word &tempWord, string &tempCreatingWord)
{
	tempCreatingWord = "";
	tempWord.wordValue = "";
	tempWord.line = 0;
	tempWord.numberOfOccurrences = 0;
}

int main()
{
	word ITEM_NOT_FOUND;
	word singleWord;
	ITEM_NOT_FOUND.wordValue = "ITEM_NOT_FOUND";
	ITEM_NOT_FOUND.line = 0;
	ITEM_NOT_FOUND.numberOfOccurrences = 0;
	AvlTree<struct word> words(ITEM_NOT_FOUND);  // constructs an empty tree of ints that returns ITEM_NOT_FOUND when find fails
	fileWriter.open("errorFile.txt");
	string fileName;
	string textFileName;
	string dictionaryFileName;
	ifstream textFile;
	ifstream dictionaryFile;
	string singleLine;
	string creatingAWord;
	char singleChar;

	cout << "Please enter the name for the file you want to spell check ---> ";
	cin >> fileName;
	textFileName = fileName + ".txt";
	cout << "Please enter the name for of the dictionary you want to use to check ---> ";
	cin >> fileName;
	dictionaryFileName = fileName +  ".dct";

	textFile.open(textFileName);
	dictionaryFile.open(dictionaryFileName);
	if (textFile.is_open())
	{
		while (getline(textFile, singleLine))//going line by line in the text file
		{
			singleLine += "#";//used to detect new lines
			for (int i = 0; i < singleLine.length(); ++i)//going char by char in the single line
			{
				singleChar = tolower(singleLine[i]);// converting to lowercase if char is uppercase
				if (isalpha(singleChar))//checking if char thats lowercase is a letter
					creatingAWord += creatingAWord;//adding it too the word
				else if (creatingAWord.length() >= 1)
				{
					if (words.find(singleWord).wordValue != creatingAWord)
					{
						singleWord.wordValue = creatingAWord;
						singleWord.line = i + 1;
						singleWord.numberOfOccurrences = 1;
						words.insert(singleWord);//inserting the word to the avl tree
					}
					//else
						//words.find(singleWord).numberOfOccurrences++;

					//resetting the creatingAWord and word struct
					resetWord(singleWord, creatingAWord);
				}	
			}		
		}
		textFile.close();
	}
	else cout << "File error, when attempting to open the given text file." << endl;


	//checking by going through the dictionary
	//if (dictionaryFile.is_open())
	//{
	//	while (getline(dictionaryFile, creatingAWord))
	//		if (words.find(singleWord).wordValue != ITEM_NOT_FOUND.wordValue)
	//			words.remove(singleWord);
	//	dictionaryFile.close();
	//}
	//else cout << "File error, when attempting to open the given dictionary file." << endl;

	//cout << "SIZE: " << words.getAVLTreeSize() << endl;

	//words.printTree();

	//words.traverse(writeErrorFile);

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