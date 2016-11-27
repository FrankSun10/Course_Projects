// Game_Base.cpp
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#include "stdafx.h"
#include "Game_Base.h"

// set the dimensions of the game 
void GameBase::set_dimention(int height, int width){
	this->height = height;
	this->width = width;
}
// set the each piece and update the max lenght of all pieces
void GameBase::set_piece(string piece1, string piece2){
	this->piece_1 = piece1;
	this->piece_2 = piece2;
	this->max_piece = max(this->piece_1.length(), this->piece_2.length());
	// if the column was up to two digits, increase the max to 2
	if (this->width > 10 && this->max_piece < 2) this->max_piece = 2;
}
// initialize the game_piece with empty piece
void GameBase::set_game_piece(){
	for (int i = 0; i < (this->height + 1) * (this->width + 1); ++i){
		this->game_piece.push_back(" ");
	}
}

// function prompt
int GameBase::prompt(unsigned int & hor, unsigned int & ver){
	// store the user's input in a string
	string input;
	while (input.length() == 0){
		if (GameType.compare("TicTacToe") == 0)
		{
			cout << "Please input a valid coordinate in forms of " <<
				" \"x,y\"  (where the ranges for x and y are [1,3]). " <<
				"Else if you want to quit, please input \"quit\" " << endl;
		}
		else {
			cout << "Please input a valid coordinate in forms of " <<
				" \"x,y\"  (where the ranges for x and y are [1," << height << "]). " <<
				"Else if you want to quit, please input \"quit\" " << endl;
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
	int index = this->width * val_y + val_x;
	int beta = 0;
	if (GameType.compare("TicTacToe") == 0)
	{
		beta = 2;
	}
	if (count == 0 && val_x >= 1 && val_x <= (this->width - beta) && val_y >= 1 && val_y <= (this->height - beta) &&
		this->game_piece[index] != this->piece_1 && this->game_piece[index] != this->piece_2){
		hor = val_x;
		ver = val_y;
		return MyEnum::valid_input;
	}
	else{ // if invalid input, then prompt player to input
		return GameBase::prompt(hor, ver);
	}
}

// play() function
int GameBase::play(){
	
	// allow the palyer to choose which piece should be the first

	if (GameType.compare("TicTacToe") == 0)
	{
		string first_piece;
	while (first_piece != this->piece_1 && first_piece != this->piece_2){
		cout << "Please choose a piece (\"X\" or \"O\") to start the game." << endl;
		cin >> first_piece;
	}
	this->piece_next = first_piece;

	}


	// repeated call turn() done() and draw()
	bool not_finish = true;
	int numTurn = 0;
	while (not_finish){
		int temp_turn_result = this->turn();
		numTurn++;
		bool temp_done_result = this->done();
		bool temp_draw_result = this->draw();
		// if done()
		if (temp_done_result){
			cout << "The Player " << this->win_piece << " win the game !" << endl;
			not_finish = false;
			return MyEnum::success;
		}
		// if draw
		if (temp_draw_result){
			cout << numTurn << " turn have been played. No winning moves remain." << endl;
			not_finish = false;
			return MyEnum::game_draw;
		}
		// if quit
		if (temp_turn_result == MyEnum::quit){
			cout << numTurn - 1 << " turn have been played. Player " << this->piece_next << " quited" << endl;
			not_finish = false;
			return MyEnum::quit;
		}
	}
	return MyEnum::err_input;
}

// the real_play function
GameBase* GameBase::real_play(int argc, char* argv[]){
	string arg_1 = argv[1];

	// If user wants to play TicTacToe
	if (arg_1 == "TicTacToe" && argc==2)
	{
		TicTacToe * t = new TicTacToe();
		return t;
	}
	
	// If user wants to play default Gomoku game
	if (arg_1 == "Gomoku" && argc == 2)
	{
		GomokuGame * g = new GomokuGame();
		return g;
	}

	// If user wants to play Gomoku game with different dimensions
	if (arg_1 == "Gomoku" && argc == 3 && isdigit(*argv[2]))
	{
		GomokuGame * g = new GomokuGame(stoi(argv[2]));
		return g;
	}

	// If user wants to play Gomoku game with different dimensions and different number of pieces in a row needed to win
	if (arg_1 == "Gomoku" && argc == 4 && isdigit(*argv[2]) && isdigit(*argv[3]))
	{
		if (stoi(argv[3]) <= stoi(argv[2]))
			{
				GomokuGame * g = new GomokuGame(stoi(argv[2]), stoi(argv[3]));
				return g;
			}
		else{
			cout << "Please input at least one argument which is \"TicTacToe\" or \"Gomoku\" in addition to the program name" << endl;
			return nullptr;
			}
	}

	else{
		cout << "Please input at least one argument which is \"TicTacToe\" or \"Gomoku\" in addition to the program name" << endl;
		return nullptr;
	}

	
}