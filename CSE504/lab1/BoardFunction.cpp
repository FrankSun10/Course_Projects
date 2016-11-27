#include "stdafx.h"
#include "CommonHeader.h"
#include "pieceHeader.h"
#include "BoardHeader.h"
#include <sstream>
#include <vector>


int readDimension(ifstream & inputFile, unsigned int & width, unsigned int & height){
	string firstLine;
	// check if the getline function works
	if (!getline(inputFile, firstLine)){
		cout << "It was not able to read a line with the getline function!" << endl;
		return valueToReturn::errGetLineFunction;
	}
	istringstream stream (firstLine);
	// check if we could extract the input file stream
	if (!(stream >> width) || !(stream >> height)){
		cout << "It was able to read a line but could not extract the board dimensions!" << endl;
		return valueToReturn::errExtract;
	}
	return valueToReturn::success;
}

// read the input file and sign the game pieces
int readGamePiece(ifstream & inputFile, vector<game_piece> & vec, unsigned int & width, unsigned int & height){
	string line;
	int numFormatedLines = 0;
	if (inputFile.is_open()){
		while (getline(inputFile, line)){
			istringstream stream(line);
			unsigned int count = 0;
			string temp;
			int coordinate;
			piece_color color;
			string name, display;
			unsigned int xRow, yCol;
			if (stream >> temp){
				count++;
			    color = enumType(temp);
			}
			if (stream >> temp){
				count++;
				name = temp;
			}
			if (stream >> temp){
				count++;
				display = temp;
			}
			if (stream >> coordinate){
				count++;
				xRow = coordinate;
			}
			if (stream >> coordinate){
				count++;
				yCol = coordinate;
			}
			while (!stream.eof()){
				stream >> temp;
				count++;
			}
			if (count != 5 || color == invalidColor || xRow >= width || yCol >= height){
				// do nothing just simply skip this line
			}
			else{
				int index = height*xRow + yCol;
				vec[index].pieceColor = color;
				vec[index].pieceName = name;
				vec[index].pieceDisplay = display;
				numFormatedLines++;		
			}
		}
		// check if any line in the input file is well formated
		if (numFormatedLines != 0){
			return valueToReturn::success;
		}
		else{
			return valueToReturn::errBadFormatedFile;
		}
		inputFile.close();
	}
	return valueToReturn::errOpenFile;
	
}
// display the game 
int displayGame(vector<game_piece> & vecGame, unsigned int & width, unsigned int & height){
	for (unsigned int h = height - 1; h >= 0 && h < height; h--){
		for (unsigned int w = 0; w <= width - 1; w++){
			size_t i = height*w + h;
			if (i >= vecGame.size()){
				return valueToReturn::errMismatchDimension;
			}
			cout << vecGame[i].pieceDisplay << "  ";
		}
		cout << endl;
	}
	return valueToReturn::success;
}

//display the neighbors
int displayNeighbor(vector<game_piece> & vecExt, unsigned int & widthExt, unsigned int & heightExt){
	for (unsigned int h = heightExt - 2; h >= 1 && h < heightExt - 1; h--){
		for (unsigned w = 1; w <= widthExt - 2; w++){
			size_t index = heightExt * h + w;
			// check to make sure a particular cell is not empty
			if (vecExt[index].pieceDisplay.find_first_not_of(" ") != string::npos){
				// print out the cell itself
				cout << (w - 1) << "," << (h - 1) <<" "<< piece_color_lowercase(vecExt[index].pieceColor) << " " << vecExt[index].pieceName;
				// check the neighbor
				vector<game_piece> temp;
				for (unsigned int hh = h - 1; hh <= h + 1; hh++){
					for (unsigned int ww = w - 1; ww <= w + 1; ww++){
						size_t i = heightExt * ww + hh;
						// check if neighbor is the cell itself, and when the neighbor is not empty then push to the temp vector
						bool itself = (hh == h) && (ww == w);
						if (!itself && vecExt[i].pieceDisplay.find_first_not_of(" ") != string::npos){
							temp.push_back(vecExt[i]);
							// print out the first non-empty neighbor
							if (temp.size() == 1){
								cout << " : " << (ww - 1) << "," << (hh - 1) << " " << piece_color_lowercase(temp[0].pieceColor) << "  " << temp[0].pieceName;
							}
							// print out the latest discovered non-empty neighbor after the first non-empty neighbor
							if (temp.size() > 1){
								cout << " ; " << (ww - 1) << "," << (hh - 1) << " " << piece_color_lowercase(temp[temp.size() - 1].pieceColor) << " " << temp[temp.size() - 1].pieceName;
							}
						}
					}
				}
				// print out a empty new line to seperate different cells
				cout << endl; 
			} // bracket of the outer if statement
		}
	}// bracket of the outer for loop


	return 0;
}