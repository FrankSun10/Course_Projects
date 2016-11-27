// Game_Base.h
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	GAME_BASE_H
#define GAME_BASE_H

#include "stdafx.h"
#include "EnumHeader.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class GameBase{
protected: 
	int height;
	int width;
	string piece_1;
	string piece_2;
	int max_piece;
	string win_piece = "null";
	vector<string> game_piece;
	string piece_next = this->piece_1;
	vector<int> moves_1_hor, moves_1_ver;
	vector<int> moves_2_hor, moves_2_ver;
	string GameType;
public:
	void set_dimention(int, int); // set up the dimention of the game board
	void set_piece(string, string); // set up each piece and update the max length of all pieces
	void set_game_piece(); // set empty game_piece
	virtual void print() = 0; // pure virtual print function
	virtual bool done() = 0; // pure virtual done function
	virtual bool draw() = 0; // pure virtual draw function
	virtual int prompt(unsigned int &, unsigned int &);
	virtual int turn() = 0; // pure virtual turn function
	int play();
	static GameBase* real_play(int, char*[]);
};

// TicTacToe Class 
class TicTacToe: public GameBase{
	friend ostream & operator << (ostream & out, TicTacToe & t);

public:
	TicTacToe();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
};

// declare the ostream operator
ostream & operator << (ostream & out, TicTacToe & t);



class GomokuGame : public GameBase{
	// friend of ostream operator
	friend ostream & operator << (ostream & out, GomokuGame & g);

	// member variable
private:
	
public:
	// public methods in GomokuGame
	GomokuGame();
	GomokuGame(int dimension);
	GomokuGame(int dimension, int k);
	int numWins;
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	
};
// declare the ostream operator
ostream & operator << (ostream & out, GomokuGame & g);

#endif