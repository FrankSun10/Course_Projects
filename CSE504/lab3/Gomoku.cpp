// Gomoku.cpp
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller


#include  "stdafx.h"
#include "Game_Base.h"


// constructor 1 of Gomoku class - takes no parameters, defaults to 19x19 with 5 in a row needed to win.
GomokuGame::GomokuGame(){
	GameType = "Gomoku";
	set_dimention(19, 19);
	numWins = 5;
	set_piece("W", "B");
	set_game_piece();
}

// constructor 2 of Gomoku class - takes one parameter, sets dimensions using that parameter and defaults to 5 in a row needed to win.
GomokuGame::GomokuGame(int dimension){
	GameType = "Gomoku";
	set_dimention(dimension, dimension);
	set_piece("W", "B");
	set_game_piece();
	numWins = 5;
}

// constructor 3 of Gomoku class - takes two parameters, sets dimensions and number of pieces in a row need to win to the two parameters (respectively).
GomokuGame::GomokuGame(int dimension, int k){
	this->numWins = k;
	GameType = "Gomoku";
	set_dimention(dimension, dimension);
	set_piece("W", "B");
	set_game_piece();
}

// print operator
void GomokuGame::print(){
	cout << *this << endl;;
}


// done function
bool GomokuGame::done(){
	bool done = false;
	for (int row = this->height; row >= 0 && row <= this->height; --row){
		for (int col = 0; col <= this->width; col++){
			bool gamePiece = false;
			int index = this->width * row + col;
			// check if a particular piece is not empty
			if (this->game_piece[index] == this->piece_1 || this->game_piece[index] == this->piece_2){
				gamePiece = true;
			}
			// check the right-down diagnol line
			if (gamePiece && (row - (numWins - 1) >= 1 && col + numWins - 1 <= this->width)){
				bool check = true;
				for (int i = 1; i < numWins; i++)
				{
					if (this->game_piece[index] != this->game_piece[index - i * (this->width - 1)])
					{
						check = false;
					}
				}
				
				if (check == true)
				{
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check the right-up diagnol line
			if (gamePiece && (row + (numWins - 1) <= this->height && col + (numWins - 1) <= this->width)){
				bool check = true;
				for (int i = 1; i < numWins; i++)
				{
					if (this->game_piece[index] != this->game_piece[index + i * (this->width + 1)])
					{
						check = false;
					}
				}

				if (check == true)
				{
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			//check row by row
			if (gamePiece && row - (numWins - 1) >= 1){
				bool check = true;
				for (int i = 1; i < numWins; i++)
				{
					if (this->game_piece[index] != this->game_piece[index - i * (this->width)])
					{
						check = false;
					}
				}

				if (check == true)
				{
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check col by col
			if (gamePiece && col + (numWins - 1) <= this->width){
				bool check = true;
				for (int i = 1; i < numWins; i++)
				{
					if (this->game_piece[index] != this->game_piece[index + i])
					{
						check = false;
					}
				}

				if (check == true)
				{
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
		}
	}
	return done;
}

// draw function
bool GomokuGame::draw(){
	// check if there is still moves
	bool has_move = true;
	int temp_height = this->height;
	int temp_width = this->width;
	int empty_count = temp_height * temp_width;
	for (int row = temp_height; row >= 1 && row <= temp_height; --row){
		for (int col = 1; col <= temp_width; ++col){
			int index = this->width * row + col;
			if (this->game_piece[index] == this->piece_1 || this->game_piece[index] == this->piece_2){
				empty_count--;
			}
		}
	}
	if (empty_count <= 0) has_move = false;
	// check if done or has moves
	if (has_move || this->done()){
		return false;
	}
	return true;
}

// turn function
int GomokuGame::turn(){
	// "X"'s turn
	if (this->piece_next == this->piece_1){
		// prompt the user to input valid coordinates
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);
		// check if quit
		if (prompt_result == MyEnum::quit) return MyEnum::quit;
		// update the game_piece and record the input in the vector moves_1
		this->moves_1_hor.push_back(hor);
		this->moves_1_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_1;
		// print out the game and a line indication the moves have been made
		this->print();
		cout << "Player " << this->piece_1 << ": ";
		for (size_t i = 0; i < this->moves_1_hor.size(); ++i){
			if (i == 0) cout << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
			else cout << "; " << this->moves_1_hor[i] << "," << this->moves_1_ver[i];
		}
		cout << endl;
		// switch the player
		this->piece_next = this->piece_2;
		return MyEnum::next_piece;
	}

	// "O"'s turn
	else{
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);
		if (prompt_result == MyEnum::quit) return MyEnum::quit;
		// update the game_piece and the input in moves_2
		this->moves_2_hor.push_back(hor);
		this->moves_2_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_2;
		// print out the game and line indicationg the moves 
		this->print();
		cout << "Player " << this->piece_2 << ": ";
		for (size_t i = 0; i < this->moves_2_hor.size(); ++i){
			if (i == 0) cout << this->moves_2_hor[i] << "," << this->moves_2_ver[i];
			else cout << "; " << this->moves_2_hor[i] << "," << this->moves_2_ver[i];
		}
		cout << endl;
		//switch the player
		this->piece_next = this->piece_1;
		return MyEnum::next_piece;
	}
}

ostream & operator << (ostream & out, GomokuGame & g)
{
	out << endl;
	int height = g.height + 1;
	int width = g.width + 1;
	for (int row = height - 1; row >= 0 && row < height; --row){
		for (int col = 0; col < width; ++col){
			// set the bottom row
			if (row == 0 && col == 0)
			{
				out << " X";
			}
			if (row == 0 && col != 0){
				out << " " << setw(g.max_piece) << col;
			}
			// set the left most collumn
			else if (col == 0 && row != 0){
				if (row >= 10) out << row<<" ";
				else out << " " << row << " ";
			}
			else if (col > 0 && row > 0){
				int index = (width - 1) * (row) + (col);
				out << setw(g.max_piece) << g.game_piece[index] << " ";
			}
		}
		out << endl;
		out << endl;
	}
	return out;
}