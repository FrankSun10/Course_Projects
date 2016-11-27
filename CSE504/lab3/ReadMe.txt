========================================================================
    Lab3 Project Overview - ReadMe.txt
	Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
	CSE 332
	Professor Miller
========================================================================

Warnings/Errors:
1. Vector Subscript out of bounds
2. Uninitialized variables
3. Mismatched types

///////////

Test 1 (Diagonal Victory Condition 1):

Player B: 1,1; 2,10; 2,2; 7,7; 3,9; 4,8; 5,7; 6,7; 4,7; 11,5; 11,4
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,19]). Else if you want to quit, please input "quit"
6,9

19

18

17

16

15

14

13

12

11 W

10 W  B

 9        B        W        W

 8           B        W  W

 7        W  B  B  B  B  W

 6                 W        W

 5                             W  B

 4                                B

 3

 2     B

 1  B

 X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


Player W: 1,10; 9,9; 8,8; 9,6; 7,8; 6,6; 1,11; 8,7; 3,7; 10,5; 6,9
The Player W win the game !

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
0



Test 2 (Horizontal Victory Condition):

Player W: 19,19; 19,6; 19,7; 19,10; 19,9
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,19]). Else if you want to quit, please input "quit"
5,9

19                                                        W

18

17

16

15

14

13

12

11

10  B                                                     W

 9  B  B  B  B  B                                         W

 8

 7                                                        W

 6                                                        W

 5

 4

 3

 2

 1

 X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


Player B: 1,9; 2,9; 3,9; 4,9; 1,10; 5,9
The Player B win the game !

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
0


Test 3 (Vertical Victory Condition):


Player B: 1,1; 8,1; 3,10; 2,10; 1,10
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,19]). Else if you want to quit, please input "quit"
19,5

19

18

17

16

15

14

13

12

11

10  B  B  B

 9

 8

 7

 6

 5                                                        W

 4                                                        W

 3                                                        W

 2                                                        W

 1  B                    B                                W

 X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


Player W: 19,1; 19,2; 19,3; 19,4; 19,5
The Player W win the game !

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
0


Test 4 (Diagonal Victory Condition 2):

Player W: 1,1; 1,2; 1,4; 5,5
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,19]). Else if you want to quit, please input "quit"
15,15

19                                                        B

18                                                     B

17                                                  B

16                                               B

15                                            B

14

13

12

11

10

 9

 8

 7

 6

 5              W

 4  W

 3

 2  W

 1  W

 X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


Player B: 19,19; 18,18; 17,17; 16,16; 15,15
The Player B win the game !

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
0


Test 5 (Draw Condition using smaller board):

Player W: 1,3; 1,5; 2,2; 3,5; 1,1; 4,5; 5,4; 2,4; 3,2; 3,3; 4,2; 4,4
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,5]). Else if you want to quit, please input "quit"
5,2

 5 W B W W B

 4 B W B W W

 3 W B W B B

 2 B W W W B

 1 W B B B B

 X 1 2 3 4 5


Player B: 1,2; 1,4; 2,1; 2,5; 5,1; 5,5; 5,3; 2,3; 3,1; 4,1; 3,4; 4,3; 5,2
25 turn have been played. No winning moves remain.

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
4


Test 6 (Invalid Command Line Input):

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>Lab3.exe Gomoksug
Please input at least one argument which is "TicTacToe" or "Gomoku" in addition
to the program name

The command line is not correct
(1) The name of the program, which is  Lab3.exe
(2) Null pointer

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
5


Test 7 (User Quit):

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>Lab3.exe Gomoku 4
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,4]). Else if you want to quit, please input "quit"
1,1

 4

 3

 2

 1 B

 X 1 2 3 4


Player B: 1,1
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,4]). Else if you want to quit, please input "quit"
quit
1 turn have been played. Player W quited

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
2




TicTacToe Test

4

3      X   O   X

2      O   X   O

1      O   X   O

0

   0   1   2   3   4


Player O: 1,1; 1,2; 2,3; 3,1; 3,2
9 turn have been played. No winning moves remain.

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>echo %errorlevel%
4



EXTRA CREDIT:

///////////
H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>Lab3.exe Gomoku 3
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
1,1

 3

 2

 1 B

 X 1 2 3


Player B: 1,1
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
2,1

 3

 2

 1 B W

 X 1 2 3


Player W: 2,1
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
2,2

 3

 2   B

 1 B W

 X 1 2 3


Player B: 1,1; 2,2
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
3,1

 3

 2   B

 1 B W W

 X 1 2 3


Player W: 2,1; 3,1
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
3,3

 3     B

 2   B

 1 B W W

 X 1 2 3


Player B: 1,1; 2,2; 3,3
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
3,2

 3     B

 2   B W

 1 B W W

 X 1 2 3


Player W: 2,1; 3,1; 3,2
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
2,3

 3   B B

 2   B W

 1 B W W

 X 1 2 3


Player B: 1,1; 2,2; 3,3; 2,3
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
1,3

 3 W B B

 2   B W

 1 B W W

 X 1 2 3


Player W: 2,1; 3,1; 3,2; 1,3
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,3]). Else if you want to quit, please input "quit"
1,2

 3 W B B

 2 B B W

 1 B W W

 X 1 2 3


Player B: 1,1; 2,2; 3,3; 2,3; 1,2
9 turn have been played. No winning moves remain.

///////////

H:\My Documents\Visual Studio 2013\Projects\Lab3\Debug>Lab3.exe Gomoku 4 2
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,4]). Else if you want to quit, please input "quit"
1,1

 4

 3

 2

 1 B

 X 1 2 3 4


Player B: 1,1
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,4]). Else if you want to quit, please input "quit"
1,2

 4

 3

 2 W

 1 B

 X 1 2 3 4


Player W: 1,2
Please input a valid coordinate in forms of  "x,y"  (where the ranges for x and
y are [1,4]). Else if you want to quit, please input "quit"
2,1

 4

 3

 2 W

 1 B B

 X 1 2 3 4


Player B: 1,1; 2,1
The Player B win the game !

///////////