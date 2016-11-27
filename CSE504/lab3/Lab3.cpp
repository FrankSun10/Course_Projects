// Lab3.cpp : Defines the entry point for the console application.
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#include "stdafx.h"
#include "Game_Base.h"
#include "EnumHeader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// usage method
int usage(string programName, string instruction){
	cout << endl;
	cout << "The command line is not correct" << endl;
	cout << "(1) The name of the program, which is  " << programName << endl;
	cout << "(2) " << instruction << endl;

	return MyEnum::err_input;
}

int main(int argc, char* argv[])
{
	try{
		GameBase * prt = GameBase::real_play(argc, argv);
		GameBase * shared_ptr = prt;
		// Check for nullpointer exception
		if (prt == 0){
			return usage(argv[0], "Null pointer");
		}
		else{
			// Otherwise, call play method of Game_Base
			return prt->play();
		}
	}
	catch (bad_alloc & ba)
	{
		cout << "Failed to allocate memory: " << ba.what() << endl;
		return err_bad_alloc; //enum for failure to allocate memory
	}
		



}

