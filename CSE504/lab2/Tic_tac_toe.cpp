#include "stdafx.h"
#include "Tic_tac_toe.h"
#include "EnumHeader.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

TicTacToeGame::TicTacToeGame(){
	this->height = 5;
	this->width = 5;
	this->piece_1 = "X";
	this->piece_2 = "O";
	this->win_piece = "null";
	for (int i = 0; i < this->height * this->width; ++i){
		this->game_piece.push_back(" ");
	}
	this->piece_next = this->piece_1; // by default the game start with X
	this->auto_triger = false;
}

// set auto triger
void TicTacToeGame::set_auto(){
	this->auto_triger = true;
}

// play method
int TicTacToeGame::play(){
	//indicate auto model
	if (this->auto_triger){
		cout << "You have chosen to play against the auto_player, and the auto_player always plays \"O\".  ";
	}
	// allow the palyer to choose which piece should be the first
	string first_piece;
	while (first_piece != this->piece_1 && first_piece != this->piece_2){
		cout << "Please choose a piece (\"X\" or \"O\") to start the game." << endl;
		cin >> first_piece;
	}
	this->piece_next = first_piece;
	// repeatedly call turn() done() and draw()
	bool not_finish = true;
	int numTurn = 0;
	while (not_finish){
		int temp_turn_result = this->turn();
		numTurn++;
		bool temp_done_result = this->done();
		bool temp_draw_result = this->draw();
		//if done()
		if (temp_done_result){
			cout << "The player " << this->win_piece << " win the game !" << endl;
			not_finish = false;
			return MyEnum::success;
		}
		//if draw()
		if (temp_draw_result){
			cout << numTurn << " turns have been played. No winning moves remain." << endl;
			not_finish = false;
			return MyEnum::game_draw;
		}
		// if quit
		if (temp_turn_result == MyEnum::quit){
			cout << numTurn - 1 << " turns have been played. Player " << this->piece_next << " quited." << endl;
			not_finish = false;
			return MyEnum::quit;
		}
	}
	return MyEnum::err_input;
}

// turn method
int TicTacToeGame::turn(){
	// "X" turn without auto_player
	if (this->piece_next == this->piece_1 && !this->auto_triger){
		// prompt the player to input a valid coordinates and store them in hor and ver
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);
		// check if the input is quit
		if (prompt_result == MyEnum::quit){
			return MyEnum::quit;
		}
		// update the game_piece and record the input in the vector moves_1
		this->moves_1_hor.push_back(hor);
		this->moves_1_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_1;
		// print out the game and a line indicating the moves have been made as piece_1
		cout << *this << endl;
		cout << "Player " << this->piece_1 << ": ";
		for (size_t i = 0; i < this->moves_1_hor.size(); ++i){
			if (i == 0) cout << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
			else cout << "; " << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
		}
		cout << endl;
		// switch the palyer playing piect_1 to the other player who plays piece_2
		this->piece_next = this->piece_2;
		return MyEnum::next_piece;
	}
	// "O" turn without auto_player
	else if (this->piece_next == this->piece_2 && !this->auto_triger){
		// prompt the player to input a valid coordinates and store them in hor and ver
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);
		// check if the input is quit
		if (prompt_result == MyEnum::quit){
			return MyEnum::quit;
		}
		// update the game_piece and record the input in the vector moves_1
		this->moves_2_hor.push_back(hor);
		this->moves_2_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_2;
		// print out the game and a line indicating the moves have been made as piece_1
		cout << *this << endl;
		cout << "Player " << this->piece_2 << ": ";
		for (size_t i = 0; i < this->moves_2_hor.size(); ++i){
			if (i == 0) cout << this->moves_2_hor[i] << "," << this->moves_2_ver[i];
			else cout << "; " << this->moves_2_hor[i] << "," << this->moves_2_ver[i];
		}
		cout << endl;
		// switch the palyer playing piect_1 to the other player who plays piece_2
		this->piece_next = this->piece_1;
		return MyEnum::next_piece;
	}
	
	// "X"turn with auto_player, make X be the user-driven player
	else if (this->piece_next == this->piece_1 && this->auto_triger){
		// prompt the player to input a valid coordinates and store them in hor and ver
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);
		// check if the input is quit
		if (prompt_result == MyEnum::quit){
			return MyEnum::quit;
		}
		// update the game_piece and record the input in the vector moves_1
		this->moves_1_hor.push_back(hor);
		this->moves_1_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_1;
		// print out the game and a line indicating the moves have been made as piece_1
		cout << *this << endl;
		cout << "Player " << this->piece_1 << ": ";
		for (size_t i = 0; i < this->moves_1_hor.size(); ++i){
			if (i == 0) cout << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
			else cout << "; " << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
		}
		cout << endl;
		// switch the palyer playing piect_1 to the other player who plays piece_2
		this->piece_next = this->piece_2;
		return MyEnum::next_piece;
	}
	// auto_player plays "O"
	else{
		return this->auto_player();
	}
}

void TicTacToeGame::almost_win(vector<int> vec, unsigned int & hor, unsigned int & ver, int dist_1, int dist_2, string piece){
	for (size_t i = 0; i < vec.size(); ++i){
		// check every piece with any other pieces 
		for (size_t j = 0; j < vec.size(); ++j){
			if (j != i){
				// check adjence win situation
				if (abs(vec[j] - vec[i]) == dist_1){
					int bigger_index = max(vec[i], vec[j]);
					int potential_1 = bigger_index + dist_1;
					int potential_2 = bigger_index - dist_2;
					if ( potential_1 % this->width <=3 && potential_1 % this->width >= 1
						&& potential_1 / this->width <= 3 && potential_1 / this->width >= 1
						&& this->game_piece[potential_1] != piece){
						ver = (bigger_index + dist_1) / this->width;
						hor = (bigger_index + dist_1) % this->width;
					}
					if (potential_2 % this->width <= 3 && potential_2 % this->width >= 1
						&& potential_2 / this->width <= 3 && potential_2 / this->width >= 1
						&& this->game_piece[potential_2] != piece){
						ver = (bigger_index - dist_2) / this->width;
						hor = (bigger_index - dist_2) % this->width;
					}
				}
				// check the other situation 
				if (abs(vec[j] - vec[i]) == dist_2){
					int bigger_index = max(vec[i], vec[j]);
					if (this->game_piece[bigger_index - dist_1] != piece){
						ver = (bigger_index - dist_1) / this->width;
						hor = (bigger_index - dist_1) % this->width;
					}
				}
			}
		}
	}
}

//auto_player() method, auto-player always plays "O"
int TicTacToeGame::auto_player(){
	unsigned int hor, ver;
	// if is the auto_player's first move, make it random
	if (this->moves_auto_hor.size() == 0){
		hor = rand() % 3 + 1;
		ver = rand() % 3 + 1;
		int temp_index = this->width * ver + hor;
		while (this->game_piece[temp_index] == this->piece_1 || this->game_piece[temp_index] == this->piece_2){
			hor = rand() % 3 + 1;
			ver = rand() % 3 + 1;
			temp_index = this->width * ver + hor;
		}
	}
	// start from the second move, try to construct win situation
	if (this->moves_auto_hor.size() >= 1){
		hor = rand() % 3 + 1;
		ver = rand() % 3 + 1;
		int first = 0;
		unsigned int first_index = this->width * this->moves_auto_ver[first] + this->moves_auto_hor[first];
	    unsigned int second_index = this->width * ver + hor;
		int dist = abs(int(second_index) - int(first_index));
		while (first < this->moves_auto_hor.size() && dist != 1 && dist != 2 && dist != 5 && dist != 10 && dist != 6 && dist != 12 
			|| this->game_piece[second_index] == this->piece_1 || this->game_piece[second_index] == this->piece_2){
			first_index = this->width * this->moves_auto_ver[first] + this->moves_auto_hor[first];
			hor = rand() % 3 + 1;
			ver = rand() % 3 + 1;
			second_index = this->width * ver + hor;
			dist = abs(int(second_index) - int(first_index));
			first++;
			if (first == this->moves_auto_hor.size()) first = 0;
		}
	}
	// prevent the user-driven player to win
	vector<int> user_index;
	for (size_t i = 0; i < this->moves_1_hor.size(); ++i){
		int temp = this->width * this->moves_1_ver[i] + this->moves_1_hor[i];
		user_index.push_back(temp);
	}
	this->almost_win(user_index, hor, ver, 1, 2, this->piece_2);
	this->almost_win(user_index, hor, ver, 5, 10, this->piece_2);
	this->almost_win(user_index, hor, ver, 6, 12, this->piece_2);
	this->almost_win(user_index, hor, ver, 4, 8, this->piece_2);

	//auto_player try to win
	vector<int> auto_index;
	for (size_t i = 0; i < this->moves_auto_hor.size(); ++i){
		int temp = this->width * this->moves_auto_ver[i] + this->moves_auto_hor[i];
		auto_index.push_back(temp);
	}
	this->almost_win(auto_index, hor, ver, 1, 2, this->piece_1);
	this->almost_win(auto_index, hor, ver, 5, 10, this->piece_1);
	this->almost_win(auto_index, hor, ver, 6, 12, this->piece_1);
	this->almost_win(auto_index, hor, ver, 4, 8, this->piece_1);
	//push back the value of hor and ver to auto moves
	this->moves_auto_hor.push_back(hor);
	this->moves_auto_ver.push_back(ver);
	int index = this->width * ver + hor;
	this->game_piece[index] = this->piece_2;
	cout << *this << endl;
	cout << "Auto_player (" << this->piece_2 << ") : ";
	for (size_t i = 0; i < this->moves_auto_hor.size(); ++i){
		if (i == 0) cout << this->moves_auto_hor[i] << "," << this->moves_auto_ver[i];
		else cout << "; " << this->moves_auto_hor[i] << "," << this->moves_auto_ver[i];
	}
	cout << endl;
	this->piece_next = this->piece_1;
	return MyEnum::next_piece;
}

// prompt method
int TicTacToeGame::prompt(unsigned int& hor, unsigned int& ver){
	// store the user's input in a stirng
	string input;
	// prompt the user to input valid coordinates or quit 
	while (input.length() == 0){
		cout << "Please input a valid coordinate in forms of " <<
			" \"x,y\"  (where the ranges for x and y are [1,3]). " <<
			"Else if you want to quit, please input \"quit\" " << endl;
		cin >> input;
	}
	// check quit
	if (input == "quit"){
		return MyEnum::quit;
	}
	// check valid coordinates
	for (size_t i = 0; i < input.length(); ++i){
		if (input[i] == ',') input[i] = ' ';
	}
	istringstream extract(input);
	int val_x, val_y;
	// firstly extract two int from input
	extract >> val_x;
	extract >> val_y;
	// check if there are still remainings
	string remaining;
	int count = 0;
	while (extract >> remaining){
		count++;
	}
	// check valid cooperates, allow user to put more than only one comma between the two numbers
	int index = this->width * val_y + val_x;
	if (count == 0 && val_x >= 1 && val_x <= 3 && val_y >= 0 && val_y <= 3 &&
		this->game_piece[index] != this->piece_1 && this->game_piece[index] != this->piece_2){
		hor = val_x;
		ver = val_y;
		return MyEnum::valid_input;
	}
	// if invalid input, then prompt player to input
	else{
		return TicTacToeGame::prompt(hor, ver);
	}
}

// draw method that return bool
bool TicTacToeGame::draw(){
	// check if still has moves
	bool has_move = true;
	int temp_height = this->height - 2;
	int temp_width = this->width - 2;
	int empty_count = temp_height * temp_width;
	for (int row = temp_height; row >= 1 && row <= temp_height; --row){
		for (int col = 1; col <= temp_width; ++col){
			int index = this->width * row + col;
			if (this->game_piece[index] == this->piece_1 ||
				this->game_piece[index] == this->piece_2){
				empty_count--;
			}
		}
	}
	if (empty_count <= 0) has_move = false;
	//if there are moves remainning or done() method return true draw() return false;
	if (has_move || this->done()){
		return false;
	}
	return true;
}

//non-static boolean done() method
bool TicTacToeGame::done(){
	bool done = false;
	for (int row = this->height - 1; row >= 0 && row < this->height; --row){
		for (int col = 0; col < this->width; col++){
			bool gamePiece = false;
			int index = this->width * row + col;
			// check if a particular piece is not  empty
			if (this->game_piece[index] == this->piece_1 || this->game_piece[index] == this->piece_2){
				gamePiece = true;
			}
			// check the right-down diagnol line
			if (gamePiece && (row - 2 >= 0 && col + 2 < this->width)){
				if (this->game_piece[index] == this->game_piece[index - 4] &&
					this->game_piece[index] == this->game_piece[index - 8]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check the left-up diagnol line
			if (gamePiece && (row + 2 < this->height && col + 2 < this->width)){
				if (this->game_piece[index] == this->game_piece[index + 6] &&
					this->game_piece[index] == this->game_piece[index + 12]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check row by row
			if (gamePiece && row - 2 >= 0){
				if (this->game_piece[index] == this->game_piece[index - 5] &&
					this->game_piece[index] == this->game_piece[index - 10]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check col by col
			if (gamePiece && col + 2 < this->width){
				if (this->game_piece[index] == this->game_piece[index + 1] &&
					this->game_piece[index] == this->game_piece[index + 2]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
		}
	}
	return done;

}

// define the ostream operator
ostream & operator << (ostream & out, TicTacToeGame & t){
	out << endl;
	int height = 6, width = 6;
	for (int row = height - 1; row >= 0 && row < height; --row){
		for (int col = 0; col < width; ++col){
			// set the bottowm row 
			if (row == 0 && col != 0){
				out << "   " << col - 1;
			}
			// set the left most collumn
			else if (col == 0 && row != 0){
				out << row - 1 << "  ";
			}
			// set the game pieces
			else if (col > 0 && row > 0){
				int index = (width - 1) * (row - 1) + (col - 1);
				out << t.game_piece[index] << "   ";
			}
		}
		out << endl;
		out << endl;
	}
	return out;
}