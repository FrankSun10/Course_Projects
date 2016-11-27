// lab2_Frank, Author: Frank Sun (Yanqing Sun), ID: 443269
//

#include "stdafx.h"
#include "Tic_tac_toe.h"
#include "EnumHeader.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

// usage method
int usage(string programName, string instruction){
	cout << endl;
	cout << "The command line is not correct" << endl;
	cout << "(1) The name of the program, which is  " << programName << endl;
	cout << "(2) " << instruction<< endl;

	return MyEnum::err_input;
}

int main(int argc, char* argv[])
{
	// check the command line
	string to_user_1 = "Please input one or two arguments in additon to the name of the program. If you choose to input only one argumen, ";
	string to_user_2 = " please input \"TicTacToe\" which starts the user driven model. If you choose to play against the auto_player, please input \"TicTacToe\" and \"auto_player\" as the arguments. ";
	string to_user = to_user_1 + to_user_2;
	try{
		if (argc != 2 && argc != 3){
			throw MyEnum::err_input;
		}
		if (argc == 2){
			string argument_1 = argv[1];
			if (argument_1 != "TicTacToe"){
				throw MyEnum::err_input;
			}
		}
		if (argc == 3){
			string argument_1 = argv[1];
			string argument_2 = argv[2];
			if (argument_1 != "TicTacToe" || argument_2 != "auto_player"){
				throw MyEnum::err_input;
			}
		}
	}
	catch (MyEnum){
		return usage(argv[0], to_user);
	}

	// play the game
	TicTacToeGame tic_tac_toe;
	if (argc == 3){
		tic_tac_toe.set_auto();
	}
	return tic_tac_toe.play();
	
}

