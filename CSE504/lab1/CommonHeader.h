#ifndef	COMMONHEADER_H
#define COMMONHEADER_H

#include <string>
#include <cctype>

using namespace std;

enum valueToReturn{
	success = 0,
	errOpenFile = 1,
	errNumCommandLines = 2,
	errGetLineFunction = 3,
	errExtract = 4,
	errBadFormatedFile = 5,
	errMismatchDimension = 6,
	errGetDimension =7

};

int usage(string, string);
void lowercase(string & );




#endif
