// Lab1_Frank.cpp  Author: Frank Sun (yanqing.sun), ID:443269, Email address: yanqing.sun@wustl.edu 
//

#include "stdafx.h"
#include "CommonHeader.h"
#include "pieceHeader.h"
#include "BoardHeader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	cout << endl;
	// check number of command lines
	try{
		if (argc != 2)
			throw valueToReturn::errNumCommandLines;
	}
	catch (valueToReturn){
		string s = "the name of the input file";
		usage(argv[0], s);
	}
	// define input file stream and check if it could be open
	ifstream inputFile;
	inputFile.open(argv[1]);
	if (inputFile.fail()){
		cout << "The input file cannot be correctly openned!" << endl;
		return valueToReturn::errOpenFile;
	}
	// define the dimension and read from the input file
	unsigned int width, height;
	int verifyDimen = readDimension(inputFile, width, height);
	while (verifyDimen == valueToReturn::errExtract && verifyDimen != valueToReturn::errGetLineFunction){
	    verifyDimen = readDimension(inputFile, width, height);
	}
	if (verifyDimen == valueToReturn::errGetLineFunction){
		cout << "Dimensions could not be read from the input file!" << endl;
		return valueToReturn::errGetDimension;
	}

	// define game_piece vector and initialize it with empty pieces
	game_piece emptyPiece;
	emptyPiece.pieceColor = piece_color::noColor;
	emptyPiece.pieceName = " ";
	emptyPiece.pieceDisplay = " ";
	vector<game_piece> vecGame(width*height, emptyPiece);
	// read game piece to the vector 
	int verifyGamePiece = readGamePiece(inputFile, vecGame, width, height);
	if (verifyGamePiece == valueToReturn::errOpenFile){
		cout << "The input file cannot open!" << endl;
		return verifyGamePiece;
	}
	if (verifyGamePiece == valueToReturn::errBadFormatedFile){
		cout << "The input file is badly formated and no game piece could be read!" << endl;
		return verifyGamePiece;
	}

	// print out the game
	int verifyGameDisplay = displayGame(vecGame, width, height);
	// print out the neighbor info
	if (verifyGameDisplay == valueToReturn::success){
		unsigned heighExt = height + 2;
		unsigned widthExt = width + 2;
		game_piece emptyPiece1 = emptyPiece;
		vector<game_piece> vecExt(heighExt * widthExt, emptyPiece1);
		for (size_t t = 0; t < vecGame.size(); t++){
			unsigned tempH = t / height;
			unsigned tempW = t % height;
			unsigned tempIndex = (tempH + 1)*heighExt + (tempW + 1);
			vecExt[tempIndex] = vecGame[t];
		}
		cout << endl;
		displayNeighbor(vecExt, widthExt, heighExt);
	}
	try{
		if (verifyGameDisplay != valueToReturn::success)
			throw valueToReturn::errMismatchDimension;
	}
	catch (valueToReturn){
		cout << "Error: the index of the game_piece vector was out of range!" << endl;
	}
	// return the value of display game
	return verifyGameDisplay;

	
}

