Graded by: Christopher Ogle (cogle@wustl.edu)

Score: 104/100

-1 -> When a bad file was input the program returned 0. However you should consider this an error and returna  unique non-zero return code.


This is the lab 0 ReadMe file



Regular part:



In this lad, the program takes two command lines from the terminal window, the first one is the name of the program and the 

second is the the name of the input file. If the number of the command lines is not exactly two, the program calls a function 

which give an instruction about what the command lines should be.



The program takes the strings in the input file, which are seperated by whitespace tab or new lines, then push them back into 

a vector one by one.Then the program iterates through the string vector which contains the string from the input file, and 

distinguish the strings that only contain digit character. After that, the program uses istringstream library to convert the 

all-digit-character to an integer and push it in to a vector of integer.At last the programs print out these integers.





Extra Credit part:



(1) Attempting to create directory /home/warehouse/yanqing.sun/perl5



(2) After make, an error appears like:

    Lab0_Frank.cpp:5:20: fatal error: stdafx.h: No such file or directory

    #include "stdafx.h"

                    ^

    compilation terminated.

(3) Another warning:

    Lab0_Frank.cpp: In function âint main(int, char**)â:

    Lab0_Frank.cpp:68:36: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]

    for (int i = 0; i < current.size(); ++i){



(4) Same trials as on Windows, the out put is:

    [yanqing.sun@shell lab0]$ ./Lab0_Frank.exe inputFile.txt

    Strings in the input file have been push to the vector



    Strings that not only are consist of digit characters: 

    7string  str4ing  string2  more  strings  strings

    Strings that only contain numeric digit characters: 

    0  1  2  3  5  7  11  13  17  19