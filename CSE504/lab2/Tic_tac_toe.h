#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H


#include "EnumHeader.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class TicTacToeGame{
	// declare the the ostream operator as friend 
	friend ostream & operator << (ostream & out, TicTacToeGame & t);
private:  int height;
		  int width;
		  string piece_1;
		  string piece_2;
		  string win_piece;
	      vector<string> game_piece;
		  string piece_next;
		  vector<int> moves_1_hor, moves_1_ver;
		  vector<int> moves_2_hor, moves_2_ver;
		  bool auto_triger;
		  vector<int> moves_auto_hor, moves_auto_ver;
		  
public:
	TicTacToeGame();
	bool done();
	bool draw();
	int prompt(unsigned int &, unsigned int&);
	int turn();
	int play();
	int auto_player();
	void set_auto();
	void almost_win(vector<int>, unsigned int &, unsigned int &, int, int, string);
};

// declare the ostream opertor 
ostream & operator << (ostream &out, TicTacToeGame & t);




#endif