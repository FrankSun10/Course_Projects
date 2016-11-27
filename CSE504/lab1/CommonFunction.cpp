#include "stdafx.h"
#include "CommonHeader.h"
#include <string>
#include "pieceHeader.h"
#include <iostream>

using namespace std;

// usage function
int usage(string programName, string fileName){
	cout << endl;
	cout << "The number of command lines is not right, please input exactly two command lines" << endl;
	cout << "(1) the name of the program, which is  " << programName << endl;
	cout << ", and (2) " << fileName << endl;

	return valueToReturn::errNumCommandLines;
}
// turn all characters in a string to lowercase
void lowercase(string & str){
	for (char & s : str){
		s = tolower(s);
	}
}

