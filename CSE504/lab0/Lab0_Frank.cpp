// Lab0_Frank.cpp : Author: Frank Sun, Email yanqing.sun@wustl.edu
//                  Lab 0 defines two functions which used to direct the command line and pare an input txt file
//                  sstream and fstream are the main concept that are practiced in this lab

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "headerFile.h"
#include <vector>
#include <sstream>

using namespace std;

// parse function
int parse(vector<string> & vec, char * infileName){

	string temp;
	ifstream infile;
	infile.open(infileName);
	if (infile.fail()){
		cout << "The input file can not be openned for reading" << endl;
		return errOpenFile;
	}
	else {
		while (!infile.eof()) {
			infile >> temp;
			vec.push_back(temp);
		}
		cout << "Strings in the input file have been push to the vector" << endl;
		return success;
	}
}
// usage function
int usage(char * programName){
	cout << endl;
	cout << "The number of command lines is not right, please input exactly two command lines" << endl;
	cout << "(1) the name of the program, which is  " << programName << endl;
	cout << ", and (2) the input file name" << endl;
	
	return 0;
}



int main(int argc, char* argv[])
{
	// check if the number of command lines is right
	if (argc != numCommand){
		usage(argv[0]);
		return wrongNumOfCmdLine;
	}

	//push all the strings in the inputfile to the vector 
	vector<string> vecString;
	parse(vecString, argv[1]);
	
	// declare a int vector  
	vector<int> vecInt;

	// iterate through the string vector 
	cout <<endl << "Strings that not only are consist of digit characters: " << endl;
	for (vector<string>::iterator it = vecString.begin(); it != vecString.end(); ++it){
		
		string current = *it;
		// check if all characters in current string is digit
		bool allDigit = true;
		for (int i = 0; i < current.size(); ++i){
			if (!isdigit(current[i])){
				allDigit = false;
			}
		}
		if (allDigit){
			istringstream stream(current);
			int val;
			stream >> val;
			vecInt.push_back(val);
		}
		else{
			cout << "  " << current;
		}
	}

	// iterater through the int vector to print out each element
	cout << endl << "Strings that only contain numeric digit characters: " << endl;
	for (vector<int>::iterator it = vecInt.begin(); it != vecInt.end(); ++it){
		cout << "  " << *it;
	}

	return success;
}