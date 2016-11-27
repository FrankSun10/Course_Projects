#include "stdafx.h"
#include "CommonHeader.h"
#include "pieceHeader.h"
#include "BoardHeader.h"


// the following function takes a piece_game, and return a corresponding string
string piece_color_lowercase(piece_color piece){
	string temp = "";
	switch (piece){
	case red:
		temp = "red";
		lowercase(temp);
		break;
	case black:
		temp = "black";
		lowercase(temp);
		break;
	case white:
		temp = "white";
		lowercase(temp);
		break;
	case invalidColor:
		temp = "invalidColor";
		lowercase(temp);
		break;
	case noColor:
		temp = "noColor";
		lowercase(temp);
		break;
	}
	return temp;
}


// enumType function take a string as a parameter and return the corresponding enum type
piece_color enumType(string s){
	lowercase(s);
	//check if s contains only spaces
	if (s.find_first_not_of(' ') == string::npos){
		return noColor;
	}
	//if not only spaces, check what color it is
	vector<piece_color> vec = { red, black, white};
	for (auto c : vec){
		if (s == piece_color_lowercase(c)){
			return c;
		}
	}
	// after all checks, return invalid color
	return invalidColor;

	
}
