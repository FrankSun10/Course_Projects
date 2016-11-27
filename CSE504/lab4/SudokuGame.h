
// SudokuGame.h
// Lab 4
// Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
// CSE 332
// Professor Miller

#ifndef	SODOKU_H
#define SODOKU_H


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

//sudoku game
class SudokuGame : public GameBase{
	friend ostream & operator << (ostream & out, SudokuGame & s);
public:
	SudokuGame();
	int sudokuReadFile();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	SudokuGame(const SudokuGame &) = delete;
	SudokuGame(const SudokuGame &&) = delete;
	void operator=(SudokuGame) = delete;
	void operator=(SudokuGame &&) = delete;
};


ostream & operator << (ostream & out, SudokuGame & s);

#endif