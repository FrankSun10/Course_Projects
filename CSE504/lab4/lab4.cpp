// lab4.cpp : Defines the entry point for the console application.
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller


#include "stdafx.h"
#include "Game_Base.h"
#include "EnumHeader.h"

using namespace std;



// Checks that the command line is formatted correctly
int usage(string programName, string instruction){
	cout << endl;
	cout << "The command line is not correct" << endl;
	cout << "(1) The name of the program, which is  " << programName << endl;
	cout << "(2) " << instruction << endl;

	return MyEnum::err_input;
}

int main(int argc, char* argv[])
{	
	// Initializes the GameBase pointer to null before the user chooses which game to play
	shared_ptr<GameBase> game = NULL;
	try{
		// Try to set up the game
		GameBase::real_play(argc, argv);
		// Check for nullpointer exception
		game = GameBase::instance();
	}
	// If the GameBase value failed to allocate to the shared pointer
	catch (bad_alloc & ba)
	{
		cout << "Failed to allocate memory: " << ba.what() << endl;
		return err_bad_alloc;
	}
	catch (MyEnum exception)
	{
		if (exception == null_ptr_exception)
		{
			cout << "Null Pointer Exception" << endl;
		}

		return exception;
	}

	// Play the game in the terminal window
	return game->play();
}

