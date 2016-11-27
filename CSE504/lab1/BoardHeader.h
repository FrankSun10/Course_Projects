#ifndef BOARDHEADER_H
#define BOARDHEADER_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int readDimension(ifstream &, unsigned int &, unsigned int &);
int readGamePiece(ifstream &, vector<game_piece> &, unsigned int &, unsigned int &);
int displayGame(vector<game_piece> &, unsigned int &, unsigned int &);
int displayNeighbor(vector<game_piece> &, unsigned int &, unsigned int &);



#endif