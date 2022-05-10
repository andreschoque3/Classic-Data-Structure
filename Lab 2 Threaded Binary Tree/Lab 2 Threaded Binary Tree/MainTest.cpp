#include <iostream>
#include <iomanip>
#include "BST.h"
#include "BinNode.h"

using namespace std;



int main()
{
	BST<int, string> mainTest; //tests insert functions
	mainTest.insert(77, "seventy-seven");
	mainTest.insert(70, "seventy");
	mainTest.insert(75, "seventy-five");
	mainTest.insert(66, "sixty-six");
	mainTest.insert(79, "seventy-nine");
	mainTest.insert(68, "sixty-eight");
	mainTest.insert(67, "sixty-seven");
	mainTest.insert(69, "sixty-nine");
	mainTest.insert(90, "ninety");
	mainTest.insert(85, "eighty-five");
	mainTest.insert(83, "eighty-three");
	mainTest.insert(87, "eighty-seven");
	mainTest.insert(65, "sixty-five");
	cout << "Printing Tree . . . " << endl; // prints the binary tree
	mainTest.print();
	cout << endl << endl;
	cout << "Printing Tree Values in Sequential Order . . . " << endl; // prints the tree in sequential order
	mainTest.printInorder();
	cout << endl << endl;
	cout << "Printing Tree Values in Reverse Sequential Order . . . " << endl; //prints the tree in reverse order
	mainTest.printReverse();
	system("pause");

	return 0;

}