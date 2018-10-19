//Harman Dhillon

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include "AvlTree.h"
using namespace std;

const string ITEM_NOT_FOUND = "99999";
ofstream fileWriter;
int totalMisspelledWords;

class word
{
private:
	string aWord;
	queue<int> line;
	int numberOfOccurrences;
public:
	//default constructor
	word() { aWord = ""; numberOfOccurrences = 0; queue<int> empty; swap(line, empty);}
	//explict constructor
	word(string w, int l, int n)
	{
		aWord = w;
		line.push(l);
		numberOfOccurrences = n;
	}
	void setWord(string newWord) { aWord = newWord; }
	void addLine(int lineValue) { line.push(lineValue); }
	void incrementNumberOfOccurrences() {++numberOfOccurrences; }
	void addToTotalErrors() { totalMisspelledWords += numberOfOccurrences; }

	string getWord() { return aWord; }
	string getLine() 
	{
		string returnString = "[";
		queue<int> tempQ = line;
		while (!tempQ.empty())
		{
			returnString += to_string(tempQ.front());
			if (tempQ.size() != 1)//formatting
				returnString += ", ";
			tempQ.pop();
		}
		return returnString + "]";
	}
	int getNumberOfOccurrences() { return numberOfOccurrences; }
	string getPageNumber()
	{
		queue<int> tempQ = line;
		int tempInt = 0;
		string returnString = "[";
		while(!tempQ.empty())
		{
			tempInt = tempQ.front();
			returnString += to_string(tempInt / 66 + 1);

			if (tempQ.size() != 1)//formatting
				returnString += ", ";
			tempQ.pop();
		}
		return returnString + "]";
		
	}
};

map<string, word> allWords;

void writeErrorFile(string &str)
{
	fileWriter << "Incorrect Spelled Word: " << str << endl;
	fileWriter << "		Number Of Occurrences: " << allWords[str].getNumberOfOccurrences() << endl;
	fileWriter << "		Page Numbers: " << allWords[str].getPageNumber() << endl;
	fileWriter << "		Lines at error found: " << allWords[str].getLine() << endl;//print list
	allWords[str].addToTotalErrors();//adding up total number of errors

}

string toLower(string s)
{
	string returnString = "";
	for (int i = 0; i < s.length(); i++)
	{
		returnString += tolower(s[i]);
	}
	return returnString;
}


int main()
{
	AvlTree<string> words(ITEM_NOT_FOUND);  // constructs an empty tree of ints that returns 99999 when find fails
	fileWriter.open("errorFile.txt");
	string fileName;
	string textFileName;
	string dictionaryFileName;
	ifstream textFile;
	ifstream dictionaryFile;
	string singleLine;
	string singleWord;
	int lineCount;
	char singleChar;

	cout << "Please enter the name for the file you want to spell check ---> ";
	cin >> fileName;
	textFileName = fileName + ".txt";
	cout << "Please enter the name for of the dictionary you want to use to check ---> ";
	cin >> fileName;
	dictionaryFileName = fileName + ".dct";

	textFile.open(textFileName);
	dictionaryFile.open(dictionaryFileName);
	if (textFile.is_open())
	{
		lineCount = 0;
		while (getline(textFile, singleLine))//going line by line in the text file
		{
			++lineCount;
			singleLine += "#";//used to detect new lines
			for (int i = 0; i < singleLine.length(); ++i)//going char by char in the single line
			{
				singleChar = tolower(singleLine[i]);// converting to lowercase if char is uppercase
				if (isalpha(singleChar))//checking if char thats lowercase is a letter
					singleWord += singleChar;//adding it too the word
				else if (singleWord.length() >= 1)
				{
					words.insert(singleWord);//inserting the word to the avl tree

					map<string, word>::iterator itr;
					itr = allWords.find(singleWord);
					if (itr != allWords.end())
					{
						itr->second.incrementNumberOfOccurrences();//existing word, count++
						itr->second.addLine(lineCount);//adding a new line to the existing word object
					}
					else
					{
						word wordData(singleWord, lineCount, 0);
						wordData.incrementNumberOfOccurrences();
						allWords[singleWord] = wordData;//new word
					}
						singleWord = "";//resetting the word

				}
			}
		}
		textFile.close();
	}
	else cout << "File error, when attempting to open the given text file." << endl;


	//checking spelling by going through the dictionary
	if (dictionaryFile.is_open())
	{
		while (getline(dictionaryFile, singleWord))
			if (words.find(toLower(singleWord)) != ITEM_NOT_FOUND)
				words.remove(toLower(singleWord));
		dictionaryFile.close();
	}
	else cout << "File error, when attempting to open the given dictionary file." << endl;

	//words.printTree();

	words.traverse(writeErrorFile);
	fileWriter << "--------------------------------------------" << endl;
	fileWriter << "Total Unique Incorrect Words: " << words.getAVLTreeSize() << endl;
	fileWriter << "Total Incorrect Words: " << totalMisspelledWords << endl;
    cout << "Error file created!" << endl;
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