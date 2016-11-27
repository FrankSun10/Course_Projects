// Gomoku.h
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	GOMOKU_H
#define GOMOKU_H

#include "EnumHeader.h"
#include "Game_Base.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

class GomokuGame : public GameBase{
	// friend of ostream operator
	friend ostream & operator << (ostream & out, GomokuGame & g);

	// member variable
private:

public:
	// public methods in GomokuGame
	GomokuGame(int dimension = 19, int k = 5);
	int numWins;
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	GomokuGame(const GomokuGame &) = delete;
	GomokuGame(const GomokuGame &&) = delete;
	void operator=(GomokuGame) = delete;
	void operator=(GomokuGame &&) = delete;

};
// declare the ostream operator
ostream & operator << (ostream & out, GomokuGame & g);


#endif