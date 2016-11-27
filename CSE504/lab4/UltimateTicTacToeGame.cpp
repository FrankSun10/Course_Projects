// UltimateTicTacToe.cpp
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller


#include  "stdafx.h"
#include "UltimateTicTacToe.h"
#include <fstream>
#include <set>
#include <array>


using namespace std;

/*
* This is the UltimateTicTacToe class,
*/

UltimateTicTacToe::UltimateTicTacToe(){
	this->clear = true;
	this->GameType = "UltimateTicTacToe"; // set the game type 

	// initialize the UltimateTicTacToe to be 9 seperate TicTacToe
	for (unsigned int i = 0; i < 9; i++)
	{
		TicTacToe name;
		tvector.push_back(name);
	}

	// read data from history game, and populate the individual tictactoes 
	if (readFile() == success){
		// need a funtion to populate the individuals
		this->fillIndividualTicTacToe();
		this->tvector[activeCell].isActive = true;
	}

	// if cann't read saved file, initialize UltimateTicTacToe to be a new one
	else{
		set_dimention(9, 9);
		set_piece("X", "O");
		set_game_piece();
		num_wins_2 = 3;
	}

}


// check if the tictactoe vector has active tictactoe
bool UltimateTicTacToe::hasActiveTicTacToe(){ 
	bool hasActive = false;
	for (int i = 0; i < 9; i++){
		if (this->tvector[i].isActive) hasActive = true;
	}
	return hasActive;
}

// check if the tictactoe should be active or not
void UltimateTicTacToe::checkStillActive(TicTacToe & t){
	if (t.done() || t.draw()){
		t.isActive = false;
	}
}

// function used to help determine whether the coordinate is valid or not
bool UltimateTicTacToe::isCoorValidHelper(TicTacToe & t, int index, string piece){
	if (! t.isActive){

		// if the tictactoe is done or draw, the index is not valid, reture false
		if (t.done() || t.draw()) return false;  

		// if there is another tictactoe is active
		if (this->hasActiveTicTacToe()) return false; 

		else{ // activate the tictactoe and store the piece to right slot
			t.isActive = true;
			t.get_game_piece()[index] = piece;
			checkStillActive(t);
			return true;
		}
	}

	// if the tictactoe is already active
	else{
		t.get_game_piece()[index] = piece;
		checkStillActive(t);
		return true;
	}
}

void UltimateTicTacToe::setActiveCell()
{
	this->activeCell = -1;
	for (unsigned int i = 0; i < tvector.size(); i++)
	{
		if (tvector[i].isActive == true)
		{
			this->activeCell = i;
		}
	}
}

// check if the input coordinate is valid or not 
bool UltimateTicTacToe::isCoorValid(unsigned int row, unsigned int col, string piece){
	
	int tictactoe_dimension = 5;
	// top row
	if (row >= 7 && row <= 9 ){
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * (row - 6) + col;
			return this->isCoorValidHelper(this->tvector[6], index, piece);
		}
		// middle
		else if (col >= 4 && col <= 6){
			int index = tictactoe_dimension * (row - 6) + (col - 3);
			return this->isCoorValidHelper(this->tvector[7], index, piece);
		}
		//right most
		else {
			int index = tictactoe_dimension * (row - 6) + (col - 6);
			return this->isCoorValidHelper(this->tvector[8], index, piece);
		}
	}

	// middle row
	else if (row >= 4 && row <= 6){
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * (row - 3) + col;
			return this->isCoorValidHelper(this->tvector[3], index, piece);
		}
		// middle
		else if (col >= 4 && col <= 6) {
			int index = tictactoe_dimension * (row - 3) + (col - 3);
			return this->isCoorValidHelper(this->tvector[4], index, piece);
		}
		// right most
		else {
			int index = tictactoe_dimension * (row - 3) + (col - 6);
			return this->isCoorValidHelper(this->tvector[5], index, piece);
		}
	}

	// bottom row
	else {
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * row + col;
			return this->isCoorValidHelper(this->tvector[0], index, piece);
		}
		// middle
		else if (col >= 4 && col <= 6){
			int index = tictactoe_dimension * row + (col - 3);
			return this->isCoorValidHelper(this->tvector[1], index, piece);
		}
		// right most
		else {
			int index = tictactoe_dimension * row + (col - 6);
			return this->isCoorValidHelper(this->tvector[2], index, piece);
		}
	}

}

// helper for fillIndividualTicTacToe function
void UltimateTicTacToe::fillIndividualTicTacToeHelper(int row, int col, string piece){
	int tictactoe_dimension = 5;
	// top row
	if (row >= 7 && row <= 9){
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * (row - 6) + col;
			this->tvector[6].get_game_piece()[index] = piece;
		}
		// middle
		else if (col >= 4 && col <= 6){
			int index = tictactoe_dimension * (row - 6) + (col - 3);
			this->tvector[7].get_game_piece()[index] = piece;
		}
		//right most
		else if (col >= 7 && col <= 9){
			int index = tictactoe_dimension * (row - 6) + (col - 6);
			this->tvector[8].get_game_piece()[index] = piece;
		}
	}

	// middle row
	else if (row >= 4 && row <= 6){
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * (row - 3) + col;
			this->tvector[3].get_game_piece()[index] = piece;
		}
		// middle
		else if (col >= 4 && col <= 6) {
			int index = tictactoe_dimension * (row - 3) + (col - 3);
			this->tvector[4].get_game_piece()[index] = piece;
		}
		// right most
		else if (col >= 7 && col <= 9){
			int index = tictactoe_dimension * (row - 3) + (col - 6);
			this->tvector[5].get_game_piece()[index] = piece;
		}
	}

	// bottom row
	else if (row >= 1 && row <= 3){
		// left most
		if (col >= 1 && col <= 3){
			int index = tictactoe_dimension * row + col;
			this->tvector[0].get_game_piece()[index] = piece;
		}
		// middle
		else if (col >= 4 && col <= 6){
			int index = tictactoe_dimension * row + (col - 3);
			this->tvector[1].get_game_piece()[index] = piece;
		}
		// right most
		else if (col >= 7 && col <= 9){
			int index = tictactoe_dimension * row + (col - 6);
			this->tvector[2].get_game_piece()[index] = piece;
		}
	}
}

// function used to fill all individual tictactoe
void UltimateTicTacToe::fillIndividualTicTacToe(){

	for (int row = 1; row <= this->height; ++row){
		for (int col = 1; col <= this->width; ++col){
			int index_ultimate = this->width * row + col;
			string piece = this->game_piece[index_ultimate];
			this->fillIndividualTicTacToeHelper(row, col, piece);
		}
	}
}



// turn function
int UltimateTicTacToe::turn(){
	// "X"'s turn
	if (this->piece_next == this->piece_1){
		// prompt the user to input valid coordinates
		unsigned int hor, ver;
		int prompt_result = this->prompt(hor, ver);

		// check if quit
		if (prompt_result == MyEnum::quit) return MyEnum::quit;
		
		// check if the coordinate is in the active tictactoe, if not recursively call turn
		if (!this->isCoorValid(ver, hor, this->piece_1)) return turn();
		
		// update the game_piece and record the input in the vector moves_1
		this->moves_1_hor.push_back(hor);
		this->moves_1_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_1;
		this->setActiveCell();
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

		// check if quit
		if (prompt_result == MyEnum::quit) return MyEnum::quit;
		
		// check if the input coordinate is valid for the active tictactoe
		if (!this->isCoorValid(ver, hor, this->piece_2)) return turn();

		// update the game_piece and the input in moves_2
		this->moves_2_hor.push_back(hor);
		this->moves_2_ver.push_back(ver);
		int index = this->width * ver + hor;
		this->game_piece[index] = this->piece_2;
		this->setActiveCell();
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

// function to print the game
void UltimateTicTacToe::print()
{
	cout << *this << endl;
}


// function to tell if the game is draw or not
bool UltimateTicTacToe::draw()
{
	
	int counter = 0;
	for (int i = 0; i < this->height; ++i){
		if (this->tvector[i].done() || this->tvector[i].draw()){
			counter++;
		}
	}

	if (counter == 9 && !this->done()) return true;
	else return false;
}


// function to tell if UltimateTicTacToe is done or not
bool UltimateTicTacToe::done(){
	
	int tictactoe_dimension = 3;
	bool isDone = false;

	for (int row = 0; row < tictactoe_dimension; ++row){
		for (int col = 0; col < tictactoe_dimension; ++col){

			int index = tictactoe_dimension * row + col;
			bool hasWinPiece = false;
			// check if the particular tictactoe is done
			if (this->tvector[index].get_win_piece() != "null"){
				hasWinPiece = true;
			}

			// right-down diagnol line
			if (hasWinPiece && (row - 2 >= 0 && col + 2 < tictactoe_dimension)){
				if (this->tvector[index].get_win_piece() == this->tvector[index - (tictactoe_dimension - 1)].get_win_piece()
					&& this->tvector[index].get_win_piece() == this->tvector[index - 2 * (tictactoe_dimension - 1)].get_win_piece()){
					isDone = true;
					this->win_piece = this->tvector[index].get_win_piece();
				}
					
			}

			// check the left-up diagnol line
			if (hasWinPiece && (row + 2 < tictactoe_dimension && col + 2 < tictactoe_dimension)){
				if (this->tvector[index].get_win_piece() == this->tvector[index + (tictactoe_dimension + 1)].get_win_piece()
					&& this->tvector[index].get_win_piece() == this->tvector[index + 2 * (tictactoe_dimension + 1)].get_win_piece()){
					isDone = true;
					this->win_piece = this->tvector[index].get_win_piece();
				}
			}

			//check row by row
			if (hasWinPiece && row - 2 >= 0){
				if (this->tvector[index].get_win_piece() == this->tvector[index - tictactoe_dimension].get_win_piece()
					&& this->tvector[index].get_win_piece() == this->tvector[index - 2 * tictactoe_dimension].get_win_piece()){
					isDone = true;
					this->win_piece = this->tvector[index].get_win_piece();
				}
			}

			// check col by col
			if (hasWinPiece && col + 2 < tictactoe_dimension){
				if (this->tvector[index].get_win_piece() == this->tvector[index + 1].get_win_piece()
					&& this->tvector[index].get_win_piece() == this->tvector[index + 2].get_win_piece()){
					isDone = true;
					this->win_piece = this->tvector[index].get_win_piece();
				}
			}

		}
	}
	
	// if the game is done, don't save it
	if (isDone)
	{
		emptyFile();
	}

	return isDone;

}


//insertion operator for UltimateTicTacToe
ostream & operator<<(ostream & out, UltimateTicTacToe & u){
	//u.fillGamePieceVector();
	string space = " "; // space 

	out << endl;
	int height = u.height + 1;
	int width = u.width + 1;
	for (int row = height - 1; row >= 0 && row < height; --row){
		for (int col = 0; col < width; ++col){
			// set the bottom row
			if (row == 0 && col == 0)
			{
				out << space << "#" << space << "||";
			}
			else if (row == 0 && col != 0){
				//out << space << setw(u.max_piece) << col - 1 << space;
				out << space << setw(u.max_piece) << col << space;
				if (col % 3 == 0){
					out << "||";
				}
				else{
					out << "|";
				}
			}

			// set the left most collumn
			else if (col == 0 && row != 0){
				//out << space << row - 1 << space << "||";
				out << space << row << space << "||";
			}

			// set the board body
			else{
				//int index = u.width * ((height - 1) - (row - 1)) + (col - 1);
				int index = u.width * row + col;
				out << space << u.game_piece[index] << space;
				if (col % 3 == 0) out << "||";
				else out << "|";
			}
		}

		// set seperating lines
		out << endl;
		if ((row - 1) % 3 == 0){
			for (int i = 0; i < width; ++i){
				if (i % 3 == 0)  out << space << "=" << space << "||";
				else  out << space << "=" << space << "|";
			}
		}
		else if (row != 0){
			for (int i = 0; i < width; ++i){
				if (i % 3 == 0)  out << space << "-" << space << "||";
				else  out << space << "-" << space << "|";
			}
		}
		out << endl;
	}

	return out;
}
