#include  "stdafx.h"
#include "SudokuGame.h"
#include <fstream>
#include <set>
 
using namespace std;

SudokuGame::SudokuGame(){

	// set up default member variable
	this->height = 9;
	this -> width = 9;
	GameType = "Sudoku";
	clear = true;

	// remember the given pieces that shouldn't be changed by the user
	sudokuReadFile();
	this->game_piece.clear();

	// if no history file could be read, set up a new game
	if (readFile() != success)
	{
		this->set_game_piece(); // set up the game piece vector for readFile method
		this->game_piece.clear(); // if no file to read, just clear all the vector and read from the initializing file
		sudokuReadFile();
	}
	
}

// function used to print the game
void SudokuGame::print(){
	cout << *this << endl;;
}

// check if the game is done;
bool SudokuGame::done(){
	bool done = false;
	string space = " ";
	//check row by row to see if there are 1-9 in each row
	for (int row = this->height - 1; row >= 0 && row < this->height; --row)
	{
		// for each row use a set to store the value in each slot
		set<string> temp;
		for (unsigned int i = 0; i < 9; i++)
		{
			bool gamePiece = false;
			int index = this->width * row + i;
			// check if a particular piece is not empty
			if (this->game_piece[index] != space){
				gamePiece = true;
			}
			else{
				return done; // there is still empty slot, so it is not done
			}
			temp.insert(game_piece[index]);
		}
		// since set dosen't support duplication, so if there were duplications, the size of set should be less than 9
		if (temp.size() != 9)
		{
			return done;
		}

	}

	// check col by col to see if there are 1-9 in each colum
	for (int col = 0; col < this->width; col++){
		// for each column, use a set to store the value in each slot of the column
		set<string> temp;
		for (unsigned int i = 0; i < 9; i++)
		{
			bool gamePiece = false;
			int index = this->width * i + col;
			// check if a particular piece is not empty
			if (this->game_piece[index] != space){
				gamePiece = true;
			}
			else{
				return done; // there is still empty slot, so the game is not done
			}
			temp.insert(game_piece[index]);
		}
		// since set dosen't support duplication, so if there were duplications, the size of set should be less than 9
		if (temp.size() != 9)
		{
			return done;
		}
	}

	// check the sperate 9 squares
	for (int row = this->height - 1; row >= 0 && row < this->height; --row){
		for (int col = 0; col < this->width; ++col){
			// travel through all the slots to pick up the slots locating at the left up corner
			if (row + 1 % 3 == 0 && col % 3 == 0){
				// for each square, we use a set to store the value in each slot, and since we checked empty case above, no need to do it again
				set<string> temp;
				for (int i = row; i >= row - 2; --i){
					for (int j = col; j <= col + 2; ++j){
						int index = this->width * i + j;
						temp.insert(game_piece[index]);
					}
				}
				// check if the square has 9 different digits
				if (temp.size() != 9){
					return done;
				}
			}
		}
	}
	
	//if all tests are passed, then the game is done
	done = true;
	
	// we do not need to save the game when the game is done
	if (done)
	{
		emptyFile();
	}

	return done;
}


// Sudoku can never be draw, but according to the instruction, when there is no empty slot in the board, a message should be given
// So sudoku has a fake draw method
bool SudokuGame::draw(){
	bool check = false;
	// check if there is till empty slot in the game board
	for (unsigned int i = 0; i < game_piece.size(); i++)
	{
		if (game_piece[i].compare(" ") == 0)
		{
			check = true;
		}
	}
	// if no space and the game is not done, the game comes to fake draw
	if (check == false && done() == false)
	{
		cout << "Board is full - incorrect solution.  Please modify your solution." << endl;
	}

	return false;
}


// function to read a file that initializing the sudoku game
int SudokuGame::sudokuReadFile(){
	ifstream ifs;
	ifs.open("sudoku0.txt");
	if (ifs.is_open())
	{
		string temp;
		bool state = true;
		while (ifs >> temp){
			// replace 0 with space
			if (temp.compare("0") == 0)
			{
				string space = " ";
				temp = space;
				state = false;

			}
			else{
				state = true;
			}
			game_piece.push_back(temp);
			permanent_game_piece.push_back(state);
		}
		ifs.close();
		// check if the file had been succefully closed
		if (ifs.is_open())
		{
			return could_not_close;
		}
		return success;
	}
	return invalid_file;
}

int SudokuGame::turn(){

	// prompt the user to input valid coordinates and a piece
	unsigned int hor, ver, digit;
	int prompt_result = this->prompt(hor, ver, digit);

	// check if quit
	if (prompt_result == MyEnum::quit) return MyEnum::quit;

	// if not quit convert the digit to string, because the game_piece is an vector of string
	stringstream convert;
	convert << digit;
	string piece;
	convert >> piece;
	
	// update the game_piece vector
	int index = this->width * ver + hor;	
	this->game_piece[index] = piece;

	// print out the game and a line indication the moves have been made
	this->print();
	cout << endl;

	return MyEnum::success;
}



// insertion operator used to print out the game
ostream & operator<<(ostream & out, SudokuGame & s){
	
	string space = " "; // space 

	out << endl;
	int height = s.height + 1;
	int width = s.width + 1;
	for (int row = height - 1; row >= 0 && row < height; --row){
		for (int col = 0; col < width; ++col){
			// set the bottom row
			if (row == 0 && col == 0)
			{
				out << space << "#" << space << "||" ;
			}
			else if (row == 0 && col != 0){
				out << space << setw(s.max_piece) << col - 1 <<  space ;
				if (col % 3 == 0){
					out << "||";
				}
				else{
					out << "|";
				}
			}

			// set the left most collumn
			else if (col == 0 && row != 0){
				out << space << row - 1 << space << "||";
			}

			// set the board body
			else{
				int index = s.width * (row - 1) + col - 1;
				out << space << s.game_piece[index] << space;
				if (col % 3 == 0) out << "||";
				else out << "|";
			}
		}

		// set seperating lines
		out << endl;
		if ((row - 1) % 3 == 0 ){
			for (int i = 0; i < width; ++i){
				if (i % 3 == 0)  out << space << "=" << space << "||";
				else  out << space << "=" << space << "|";
			}
		}
		else if ( row != 0){
			for (int i = 0; i < width; ++i){
				if (i % 3 == 0)  out << space << "-" << space << "||";
				else  out << space << "-" << space << "|";
			}
		}
		out << endl;
	}
	
	return out;
}