// Game_Base.h
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	GAME_BASE_H
#define GAME_BASE_H


#include "EnumHeader.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

using namespace std;

class GameBase{
protected: 
	int height; // dimension height
	int width; // dimension width
	string piece_1;  
	string piece_2;
	int max_piece; // the lenght of the bigger piece in piece_1 and piece_2
	string win_piece = "null";  // represent the piece that won the game
	vector<string> game_piece;  // vector stores the game 
	string piece_next = this->piece_1; // the piece going to take a move, by default assigned piece1
	vector<int> moves_1_hor, moves_1_ver; // record the moves of piece_1
	vector<int> moves_2_hor, moves_2_ver; // record the moves of piece_2
	string GameType;   // record the type of different games
	static shared_ptr<GameBase> game_base_ptr;
	int num_wins_2;  // number of pieces in line to win the game
	bool clear; // check if the the saved file is empty or not
	vector<bool> permanent_game_piece; // used to tract the initial board of Sudoku


public:
	void set_dimention(int, int); // set up the dimention of the game board
	void set_piece(string, string); // set up each piece and update the max length of all pieces
	void set_game_piece(); // set empty game_piece
	virtual void print() = 0; // pure virtual print function
	virtual bool done() = 0; // pure virtual done function
	virtual bool draw() = 0; // pure virtual draw function
	virtual int prompt(unsigned int &, unsigned int &); // prompt user to input coordinate
	virtual int prompt(unsigned int &, unsigned int &, unsigned int &); // prompt user to input coordinate and a piece for Sudoku
	virtual int turn() = 0; // pure virtual turn function
	int activeCell = -1;
	int play();   
	static void real_play(int, char*[]);
	static shared_ptr<GameBase> instance();
	int emptyFile();
	int readFile();
	void operator=(GameBase &&) = delete;
	~GameBase() = default;
	

};


#endif