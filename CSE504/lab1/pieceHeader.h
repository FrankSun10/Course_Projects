#ifndef	PIECEHEADER_H
#define PIECEHEADER_H

#include "CommonHeader.h"
#include <vector>
#include <string>

using namespace std;

// enumeration type for the piece color
enum piece_color{
	red, black, white, invalidColor, noColor
};
string piece_color_lowercase(piece_color);
piece_color enumType(string );

struct game_piece
{
	piece_color pieceColor;
	string pieceName;
	string pieceDisplay;
};

#endif
