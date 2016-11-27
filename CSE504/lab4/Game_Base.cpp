// Game_Base.cpp
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#include "stdafx.h"
#include "Game_Base.h"
#include "EnumHeader.h"
#include <fstream>
#include "TicTacToe.h"
#include "Gomoku.h"
#include "UltimateTicTacToe.h"
#include "SudokuGame.h"


// set the height and width of the game board
void GameBase::set_dimention(int height, int width){
	this->height = height;
	this->width = width;
}
// Handles the formatting of game pieces by setting each piece and updating the max length of all pieces
void GameBase::set_piece(string piece1, string piece2){
	this->piece_1 = piece1;
	this->piece_2 = piece2;
	this->max_piece = max(this->piece_1.length(), this->piece_2.length());
	// if the column value is up to two digits, increase the max to 2
	if (this->width > 10 && this->max_piece < 2) this->max_piece = 2;
}
// initialize the game_piece vector to be full of empty pieces
void GameBase::set_game_piece(){
	for (int i = 0; i < (this->height + 1) * (this->width + 1); ++i){
		this->game_piece.push_back(" ");
	}
}

// set the static shared_ptr of GameBase to null
shared_ptr<GameBase> GameBase::game_base_ptr = nullptr;

// This function returns the GameBase shared_ptr if it was not null
shared_ptr<GameBase> GameBase::instance(){
	if (game_base_ptr != nullptr)
	{
		return game_base_ptr;
	}
	else{
		throw null_ptr_exception;
	}
}

// In Sudoku games, this function lets user input a coordinate pair and a number 1-9 to place at that position.
int GameBase::prompt(unsigned int & hor, unsigned int & ver, unsigned int & digit){
	string inputCoord;
	string inputDigit;

	// give the instruction to users to input valid coordinates
	while (inputCoord.length() == 0){
		// instruction
		cout << "Please input a valid coordinate in the form of " <<
			" \"x,y\"  (where the ranges for x and y are [0," << height - 1 << "]). " <<
			"Else if you want to quit, please input \"quit\" " << endl;
		cin >> inputCoord;
		//check if user input "quit"
		if (inputCoord == "quit") return MyEnum::quit;
		// prompt the user to input a digit for the coordinate position

		// Once the user enters a valid coordinate pair, ask for digit to place at those coordinates
		while (inputDigit.length() == 0)
		{
			cout << "Please input a valid digit 1-9" << endl;
			cin >> inputDigit;
			if (inputDigit == "quit") return MyEnum::quit;
		}
	}

	if (!isdigit(inputCoord[0]) || !isdigit(inputCoord[2]) || !isdigit(inputDigit[0]) || inputDigit.length() > 1)
	{
		cout << "Invalid input. Please try again." << endl;
		return (prompt(hor, ver, digit));
	}

	// Check if coordinate format is correct
	for (size_t i = 0; i < inputCoord.length(); ++i){
		if (inputCoord[i] == ',') inputCoord[i] = ' '; // change comma to s whitespace to prepare for extraction
	}

	// Check if the digit is within the correct range
	if (stoi(inputDigit) > 0 && stoi(inputDigit) <= 9)
	{
		digit = stoi(inputDigit);
	}
	else{
		cout << "Digit not valid.  Please try again." << endl;
		return(prompt(hor, ver, digit));
	}

	// extract coordinates
	istringstream extract(inputCoord);
	int val_x, val_y;
	extract >> val_x;
	extract >> val_y;
	int index = this->width * val_y + val_x;
	// check if the coordinates are within the valid range
	if (!(val_x >= 0 && val_x < 9 && val_y >= 0 && val_y < 9))
	{
		cout << "Coordinates not valid.  Please try again." << endl;
		return(prompt(hor, ver, digit));
	}

	// checks if there is an element at the coordinates the user entered that was part of the initial game board. If it was, the user cannot change it.
	else if (permanent_game_piece[index] == true)
	{
		cout << "Cannot modify elements of the original template." << endl;
		return(prompt(hor, ver, digit));
	}
	// assign coordinate values to parameters
	hor = val_x;
	ver = val_y;

	return MyEnum::valid_input;
}

// This function prompts users to input valid coordinates and other relevant data to the program
int GameBase::prompt(unsigned int & hor, unsigned int & ver){
	// store the user's input in a string, before that give users instruction 
	string input;
	while (input.length() == 0){
		if (GameType.compare("TicTacToe") == 0)
		{
			cout << "Please input a valid coordinate in forms of " <<
				" \"x,y\"  (where the ranges for x and y are [1,3]). " <<
				"Else if you want to quit, please input \"quit\" " << endl;
		}
		else if (GameType.compare("Gomoku") == 0) {
			cout << "Please input a valid coordinate in forms of " <<
				" \"x,y\"  (where the ranges for x and y are [1," << height << "]). " <<
				"Else if you want to quit, please input \"quit\" " << endl;
		}
		else if (this->GameType.compare("UltimateTicTacToe") == 0){
			cout << "If a game is active in one cell, please input a valid coordinate in forms of " <<
				" \"x,y\"  within that cell. " << "If you have just completed a game within a cell, feel free to move on to " <<
				"another board of your choice.  Else if you want to quit, please input \"quit\" " << endl;
		}
		cin >> input;
	}
	// check quit
	if (input == "quit") return MyEnum::quit;
	// check valid coordinates
	for (size_t i = 0; i < input.length(); ++i){
		if (input[i] == ',') input[i] = ' '; // change comma to s whitespace
	}
	istringstream extract(input);
	int val_x, val_y;
	extract >> val_x;
	extract >> val_y;
	string remaining; // check if there are still remainings
	int count = 0;
	while (extract >> remaining) count++;
	int beta = 0; // solve the diff betweent the dimension and valid game board for basic TicTacToe
	if (GameType.compare("TicTacToe") == 0)
	{
		beta = 2;
	}
	int index = this->width * val_y + val_x;
	if (count == 0 && val_x >= 1 && val_x <= (this->width - beta) && val_y >= 1 && val_y <= (this->height - beta) &&
		this->game_piece[index] != this->piece_1 && this->game_piece[index] != this->piece_2){
		hor = val_x;
		ver = val_y;
		return MyEnum::valid_input;
	}
	else{ // if invalid input, then prompt player to input again
		return GameBase::prompt(hor, ver);
	}
}

// Function used to empty the file used to record game history (called if the user chooses not to save their game)
int GameBase::emptyFile()
{

	string gamestring = "" + GameType + ".txt";
	ofstream ofs;
	ofs.open(gamestring);
	if (ofs.is_open())
	{
		ofs << endl;
		ofs.close();
		// Check if the file failed to close
		if (ofs.is_open())
		{
			return could_not_close;
		}
	}

	else{ // if the file could not be opened, then return a value indicating this to the user
		return invalid_file;
	}
	return cleared;
}

// Allows the user to play their chosen game type, checks for game-ending conditions, allows the user to save his game
int GameBase::play(){

	// first print the game board
	print();

	// allow the first player to choose which piece to use
	if (GameType.compare("TicTacToe") == 0 && clear == true)
	{
		string first_piece;
		while (first_piece != this->piece_1 && first_piece != this->piece_2){
		cout << "Please choose a piece (\"X\" or \"O\") to start the game." << endl;
		cin >> first_piece;
		}
		this->piece_next = first_piece;
	}

	// repeatedly call turn() done() and draw() while the game is still active
	bool not_finish = true;
	int numTurn = 0; // counter to record the number of turns
	while (not_finish){
		int temp_turn_result = this->turn();
		numTurn++;
		bool temp_done_result = this->done();
		bool temp_draw_result = this->draw();

		// If a user wins the game, print the victory message and return success
		if (temp_done_result){
			if (GameType.compare("Sudoku") != 0)
			{
				cout << "The Player " << this->win_piece << " win the game !" << endl;
			}
			else
			{
				cout << "You win!" << endl;
			}
			
			not_finish = false;
			return MyEnum::success;
		}

		// If the game ends in a draw, return game_draw.
		if (temp_draw_result){
			cout << numTurn << " turn have been played. No winning moves remain." << endl;
			not_finish = false;
			return MyEnum::game_draw;
		}
		// if the user indicates that they would like to quit the game, give the user the choice to save the game or not
		if (temp_turn_result == MyEnum::quit){
			string yesno = "";  // record if user want to save the game
			while (true)
			{
				cout << "Would you like to save your game? Please answer \"yes\" or \"no\"." << endl;
				cin >> yesno;
				if (yesno == "no")
				{	// If the user decides not to save his game, empty the file that has been prepared to record the game
					int check = emptyFile(); 
					if (check == cleared)
					{	// if emptyFile() function executed successfully, print info about the game
						cout << numTurn - 1 << " turn have been played. Player " << this->piece_next << " quited" << endl;
						not_finish = false;
						return MyEnum::quit;
					}
					else{
						// Return the result of emptyFile()
						return check;
					}
				}
				else if (yesno == "yes")
				{	
					// If the user decides that they would like to save the game, we write the game's data to a file corresponding to that game
					string gamestring = "" + GameType + ".txt"; //file name
					ofstream ofs;
					ofs.open(gamestring);
					if (ofs.is_open())
					{
						ofs << GameType << endl; // record gametype
						if (GameType.compare("Sudoku") != 0)
							ofs << piece_next << endl; // record the current piece
						for (unsigned int i = 0; i < game_piece.size(); i++)
						{	// record all pieces in the game_piece vector
							if (game_piece[i].find_first_not_of(' ') != string::npos)
							{
								ofs << game_piece[i] << " ";
							}
							else
							{	// record * as a special character to represent the empty slot
								ofs << "*" << " ";
							}
							
						}
						ofs << "$" << endl; // record $ as a special character to represent the end of vector
						ofs << height << endl; // record  the dimension
						if (GameType.compare("Sudoku") != 0){

							ofs << num_wins_2 << endl; // record num pieces in a line needed to win
							ofs << piece_1 << " " << piece_2 << endl; // record the two pieces
						}

						// If the user is playing a game of UltimateTicTacToe, insert the active cell's index into the output stream.
						if (GameType.compare("UltimateTicTacToe") == 0){
							ofs << activeCell;
						}
						ofs.close();
						if (ofs.is_open()) // check if the file successfully closed
						{	
							return could_not_close;
						}
					}
					else{ // Check if the file could not be opened
						return invalid_file;
					}
					return MyEnum::quit;
					
				}
			}
			
		}
	}
	return MyEnum::err_input;
}

// Function used to recover the previously saved game file
int GameBase::readFile()
{
	string gamestring = "" + GameType + ".txt"; // Create a string of the filename
	ifstream ifs;
	ifs.open(gamestring);
	if (ifs.is_open())
	{
		string test;
		ifs >> test;
		if (test.compare(GameType) != 0)
		{  
			return new_game;
		}
		else
		{
			if (GameType.compare("Sudoku") != 0)
			{
				// restore the current piece
				ifs >> piece_next;
			}
			// restore the game_piece vector
			bool dollarsign = false; 
			while (!dollarsign) // While the program has not reached the end of the vector, keep extracting to the game_piece vector.
			{
				string temp = "";
				ifs >> temp;
				if (temp.compare("$") != 0)
				{
					if (temp.compare("*") == 0)
					{
						game_piece.push_back(" ");
					}
					else{
						game_piece.push_back(temp);
						clear = false;
					}
				}
				else{
					dollarsign = true; // End of the vector
				}
			}

			// Restore the game's dimensions 
			ifs >> height;
			width = height;

			if (GameType.compare("Sudoku") != 0)
			{
				// Restore the number of pieces in a row required to win.
				ifs >> num_wins_2;

				// Restore the pieces
				ifs >> piece_1;
				ifs >> piece_2;
			}
			if (GameType.compare("UltimateTicTacToe") == 0){
				ifs >> activeCell;
			}

			// close the file and check if it was closed successfully 
			ifs.close();
			if (ifs.is_open())
			{
				return could_not_close;
			}
			return MyEnum::success;
		}
	}

	return MyEnum::invalid_file;
}

// Initializes the user's desired gametype.
void GameBase::real_play(int argc, char* argv[]){

	// if the game_base_ptr is not null, throw an error. The game base pointer should initially be null.
	if (game_base_ptr != nullptr)
	{
		throw MyEnum::already_allocated;
	}
	else{
		if (argc < 2)
		{
			cout << "Please input at least one argument which is \"TicTacToe\" or \"Gomoku\" or  \"Sudoku\" or \"UltimateTicTacToe\" in addition to the program name" << endl;
			throw MyEnum::invalid_num_args; // if only the name of the program were input, throw an error.  The program requires at least two arguments to run.

		}
		string gameName = argv[1]; // record the name of the game
		int numCommandLine_defult = 2;
		int numCommandLine_with_dimension = 3;

		// The user chooses to play a game of TicTacToe.
		if (gameName == "TicTacToe" && argc == numCommandLine_defult)
		{
			game_base_ptr = make_shared<TicTacToe> ();
		}

		// The user chooses to play the default Gomoku game.
		else if (gameName == "Gomoku" && argc == numCommandLine_defult)
		{
			game_base_ptr = make_shared<GomokuGame>();
		}

		// The user chooses to play Ultimate TicTacToe.
		else if (gameName == "UltimateTicTacToe" && argc == numCommandLine_defult)
		{
			game_base_ptr = make_shared<UltimateTicTacToe>();
		}

		// If the user wants to play Gomoku game with custom dimensions:
		else if (gameName == "Gomoku" && argc == numCommandLine_with_dimension && isdigit(*argv[2]))
		{
			game_base_ptr = make_shared<GomokuGame>(stoi(argv[2]));
		}

		// If the user wants to play Gomoku game with custom dimensions and different number of pieces in a row needed to win:
		else if (gameName == "Gomoku" && argc == 4 && isdigit(*argv[2]) && isdigit(*argv[3]))
		{
			// Checks that the number of pieces in a row needed to win (specified by the user) is less than the height/width (specified by the user)
			if (stoi(argv[3]) <= stoi(argv[2]))
			{
				game_base_ptr = make_shared<GomokuGame>(stoi(argv[2]), stoi(argv[3]));
			}
			else{
				cout << "Please input at least one argument which is \"TicTacToe\" or \"Gomoku\" in addition to the program name" << endl;
				throw invalid_num_args;
			}
		}

		// The user chooses to play Sudoku.
		else if (gameName == "Sudoku" && argc == 2)
		{
			game_base_ptr = make_shared<SudokuGame>();
		}

		// The user chooses to play Ultimate TicTacToe.
		else if (gameName == "UltimateTicTacToe" && argc == 2){
			game_base_ptr = make_shared<UltimateTicTacToe>();
		}

		// otherwise throw error
		else{
			cout << "Please input at least one argument which is \"TicTacToe\" or \"Gomoku\" or  \"Sudoku\" or \"UltimateTicTacToe\" in addition to the program name" << endl;
			throw invalid_num_args;
		}
	}
}