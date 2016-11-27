// TicTacToe.cpp
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller


#include  "stdafx.h"
#include "TicTacToe.h"

// Builds a TicTacToe game, checks if a save file exists.  If a save file exists, load its data into the program (specifically, TicTacToe's class variables).
TicTacToe::TicTacToe(){
	this->clear = true;
	this->GameType = "TicTacToe"; // set game type

	// read a file that might be saved for the game, if not successful, initialize the game as a new game
	if (this->readFile() != success)  
	{
		set_dimention(5, 5);
		set_piece("X", "O");
		set_game_piece();
		num_wins_2 = 3;
	}
	
}

// Print the game board.
void TicTacToe::print(){
	cout << *this << endl;;
}

// function to get game_piece
vector<string> & TicTacToe::get_game_piece(){
	return  this->game_piece;
}

//function to get win_piece
string & TicTacToe::get_win_piece(){
	return this->win_piece;
}

// done function
bool TicTacToe::done(){
	bool done = false;
	for (int row = this->height - 1; row >= 0 && row < this->height; --row){
		for (int col = 0; col < this->width; col++){
			bool gamePiece = false;
			int index = this->width * row + col;
			// check if a particular piece is not empty
			if (this->game_piece[index] == this->piece_1 || this->game_piece[index] == this->piece_2){
				gamePiece = true;
			}
			// check the right-down diagnol line
			if (gamePiece && (row - 2 >= 0 && col + 2 < this->width)){
				if (this->game_piece[index] == this->game_piece[index - (this->width - 1)]
					&& this->game_piece[index] == this->game_piece[index - 2 * (this->width - 1)]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check the left-up diagnol line
			if (gamePiece && (row + 2 < this->height && col + 2 < this->width)){
				if (this->game_piece[index] == this->game_piece[index + (this->width + 1)]
					&& this->game_piece[index] == this->game_piece[index + 2*(this->width + 1)]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			//check row by row
			if (gamePiece && row - 2 >= 0){
				if (this->game_piece[index] == this->game_piece[index - this->width]
					&& this->game_piece[index] == this->game_piece[index - 2 * this->width]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
			// check col by col
			if (gamePiece && col + 2 < this->width){
				if (this->game_piece[index] == this->game_piece[index + 1]
					&& this->game_piece[index] == this->game_piece[index + 2]){
					done = true;
					this->win_piece = this->game_piece[index];
				}
			}
		}
	}

	if (done)
	{
		emptyFile();
	}

	return done;
}

// draw function
bool TicTacToe::draw(){
	// check if there is still moves
	bool has_move = true;
	int temp_height = this->height-2;
	int temp_width = this->width-2;
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

	emptyFile();

	return true;
}

// turn function
int TicTacToe::turn(){
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
// define the ostream operator
ostream & operator << (ostream & out, TicTacToe & t){
	out << endl;
	int height = t.height + 1;
	int width = t.width + 1;
	for (int row = height - 1; row >= 0 && row < height; --row){
		for (int col = 0; col < width; ++col){
			// set the bottom row
			if (row == 0 && col != 0){
				out << "   " << setw(t.max_piece) << col - 1;
			}
			// set the left most collumn
			else if (col == 0 && row != 0){
				if (row - 1 >= 10) out << row - 1 << "  ";
				else out << row - 1 << "  ";
			}
			else if (col > 0 && row > 0){
				int index = (width - 1) * (row - 1) + (col - 1);
				out << setw(t.max_piece) << t.game_piece[index] << "   ";
			}
		}
		out << endl;
		out << endl;
	}
	return out;
}

