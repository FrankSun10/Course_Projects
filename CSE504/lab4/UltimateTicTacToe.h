
// UltimateTicTacToe.h
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	TICTACTOE_H_ULT
#define TICTACTOE_H_ULT


#include "EnumHeader.h"
#include "Game_Base.h"
#include "TicTacToe.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

class UltimateTicTacToe : public GameBase{
	friend ostream & operator << (ostream & out, UltimateTicTacToe & u);

public:
	vector<TicTacToe> tvector; // vector to store all the individual tictactoe
	void setActiveCell();	// method used to ge the active individual tictactoe in ultimatetictactoe 
	UltimateTicTacToe();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	bool isCoorValid(unsigned int, unsigned int, string); // tell whether the inputing coordinate is valid or not
	bool hasActiveTicTacToe(); // tell whether there is an active tictactoe in the UltimateTictactoe
	void checkStillActive(TicTacToe &); // use reference because, we could change the original value 
	bool isCoorValidHelper(TicTacToe &, int, string); // use reference
	void fillIndividualTicTacToe(); // used to fill an individual TicTacToe
	void fillIndividualTicTacToeHelper(int, int, string); // fill all individual tictactoe 


	UltimateTicTacToe(const UltimateTicTacToe &) = delete;
	UltimateTicTacToe(const UltimateTicTacToe &&) = delete;
	void operator=(UltimateTicTacToe) = delete;
	void operator=(UltimateTicTacToe &&) = delete;

};

ostream & operator << (ostream & out, UltimateTicTacToe & u);

#endif
