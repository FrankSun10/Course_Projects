// TicTacToe.h
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	TICTACTOE_H
#define TICTACTOE_H

#include "EnumHeader.h"
#include "Game_Base.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

using namespace std;

class TicTacToe : public GameBase{
	friend ostream & operator << (ostream & out, TicTacToe & t);

public:
	bool isActive = false; // used in the ultimate tictactoe
	TicTacToe();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	vector<string>& get_game_piece(); // return game_piece vector used in UltimateTicTacToe
	string & get_win_piece();    // retrun the piece that win the game, used in UltimateTicTacToe 
	TicTacToe(const TicTacToe &) = default;

	void operator=(TicTacToe) = delete;
	void operator=(TicTacToe &&) = delete;

};

// declare the ostream operator
ostream & operator << (ostream & out, TicTacToe & t);


#endif