// spellcheck.cpp 
// This doesn't do any spell checking yet; it's just a simple test of the AVL-based Table ADT.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AvlTree.h"
using namespace std;

const int ITEM_NOT_FOUND = 99999;

int main()
{
	AvlTree<int> words(ITEM_NOT_FOUND);  // constructs an empty tree of ints
										 // that returns 99999 when find fails

	words.insert(4);
	words.insert(6);
	words.insert(9);
	words.insert(12);
	words.insert(2);

	if (words.find(9) != ITEM_NOT_FOUND)
		cout << "Find was sucessful." << endl;

	words.remove(9);

	cout << endl << endl;

	words.printTree();

	cin.get();  // wait for enter key
	return EXIT_SUCCESS;
}




