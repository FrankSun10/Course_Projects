Grader: Suyeon Kang (skang23@wustl.edu)Grade: 98/100 (96+2/100)-3: Hard coded constants especially in GameBase::real_play-1: Project file stdafx.h should not be submitted (No need to submit sudoku0 as well )+2: Extra Credit. Your extra credit game does not follow the rule of Ultimate TicTacToe... ========================================================================
    CONSOLE APPLICATION : lab4 Project Overview
========================================================================

 Lab3 Project Overview - ReadMe.txt
	Group Members: Connor Goggins, Frank Sun, Claire Heuckeroth
	CSE 332
	Professor Miller

Copy Control Design Decsions

Copy Constructor
	- TicTacToe: Feature was allowed in this class, because we needed to create instances of TicTacToe games within UltimateTicTacToe.  We enforced this decision by setting the copy constructor to default.  
	- GameBase: Feature allowed in this class, because the feature was essential to TicTacToe.  We enforced this decision by allowing the implicit copy constructor to remain active.
	- All other classes: Feature was not allowed, because we only use one instance of a game at a time and it would possibly allow memory to not be destroyed properly if two pointers to a single game failed to delete.  We enforced this decision by setting the copy constructor for each class equal to delete.
	
Move Constructor
	- TicTacToe: Feature was not allowed in this class, because we needed to use TicTacToe's copy constructor and didn't need to use the move constructor for this class.  We reinforced this decision by setting the copy constructor to default.
	- GameBase: Feature was not allowed in this class, because we did not support the use of the copy assignment operator.  We reinforced this decision by setting the destructor to default.
	- All other classes: Feature was not allowed in this class, because we did not want to create null pointers and never needed to move any of the games to a new pointer.  We reinforced this decision by setting the move constructor to delete.

Copy Assignment Operator:
	- TicTacToe and GameBase: Feature was not allowed in this class, because we needed to use TicTacToe's copy constructor and didn't need to use the copy assignment operator for either of these classes.  We reinforced this decision by setting the copy constructor to default.
	- All other classes: Feature was not allowed, because we only use one instance of a game at a time and it would possibly allow memory to not be destroyed properly if two pointers to a single game failed to delete.  We enforced this decision by setting the copy assignment operator for each class equal to delete.

Move Assignment Operator:
	- All classes: Feature was not allowed, because we did not want to create null pointers and never needed to move any of the games to a new pointer.  We reinforced this decision by setting the move assignment operator to delete.

Destructor:
	- GameBase: Feature was allowed for this class, because we do not need to use shared pointers for this class and instead explicitly deallocate memory.  We reinforced this decision by setting the destructor to default.
	- All other classes: Feature was not allowed for this class, because we use shared pointers and when those are deleted memory will automatically be deallocated.  We reinforced this decision by setting the destructor for each class to delete.


Warnings/Errors:
1. Vector Subscript out of bounds
2. Uninitialized variables
3. Mismatched types
4. Not all control paths contain a value - changed else if to else.


Testing (Sudoku):
1) Sudoku Win
 8 || 3 | 4 | 5 || 2 | 8 | 6 || 1 | 7 |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || 2 | 8 | 7 || 4 | 1 | 9 || 6 | 3 | 5 ||
 - || - | - | - || - | - | - || - | - | - ||
 6 || 9 | 6 | 1 || 5 | 3 | 7 || 2 | 8 | 4 ||
 = || = | = | = || = | = | = || = | = | = ||
 5 || 7 | 1 | 3 || 9 | 2 | 4 || 8 | 5 | 6 ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || 4 | 2 | 6 || 8 | 5 | 3 || 7 | 9 | 1 ||
 - || - | - | - || - | - | - || - | - | - ||
 3 || 8 | 5 | 9 || 7 | 6 | 1 || 4 | 2 | 3 ||
 = || = | = | = || = | = | = || = | = | = ||
 2 || 1 | 9 | 8 || 3 | 4 | 2 || 5 | 6 | 7 ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || 6 | 7 | 2 || 1 | 9 | 5 || 3 | 4 | 8 ||
 - || - | - | - || - | - | - || - | - | - ||
 0 || 5 | 3 | 4 || 6 | 7 | 8 || 9 | 1 | 2 ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 ||


Please input a valid coordinate in the form of  "x,y"  (where the ranges for x
nd y are [0,8]). Else if you want to quit, please input "quit"
8,8
Please input a valid digit 1-9
9

 8 || 3 | 4 | 5 || 2 | 8 | 6 || 1 | 7 | 9 ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || 2 | 8 | 7 || 4 | 1 | 9 || 6 | 3 | 5 ||
 - || - | - | - || - | - | - || - | - | - ||
 6 || 9 | 6 | 1 || 5 | 3 | 7 || 2 | 8 | 4 ||
 = || = | = | = || = | = | = || = | = | = ||
 5 || 7 | 1 | 3 || 9 | 2 | 4 || 8 | 5 | 6 ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || 4 | 2 | 6 || 8 | 5 | 3 || 7 | 9 | 1 ||
 - || - | - | - || - | - | - || - | - | - ||
 3 || 8 | 5 | 9 || 7 | 6 | 1 || 4 | 2 | 3 ||
 = || = | = | = || = | = | = || = | = | = ||
 2 || 1 | 9 | 8 || 3 | 4 | 2 || 5 | 6 | 7 ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || 6 | 7 | 2 || 1 | 9 | 5 || 3 | 4 | 8 ||
 - || - | - | - || - | - | - || - | - | - ||
 0 || 5 | 3 | 4 || 6 | 7 | 8 || 9 | 1 | 2 ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 ||



You win!


2) Full board but not a win
 8 || 3 | 4 | 5 || 2 | 8 | 6 || 1 | 7 |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || 2 | 8 | 7 || 4 | 1 | 9 || 6 | 3 | 5 ||
 - || - | - | - || - | - | - || - | - | - ||
 6 || 9 | 6 | 1 || 5 | 3 | 7 || 2 | 8 | 4 ||
 = || = | = | = || = | = | = || = | = | = ||
 5 || 7 | 1 | 3 || 9 | 2 | 4 || 8 | 5 | 6 ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || 4 | 2 | 6 || 8 | 5 | 3 || 7 | 9 | 1 ||
 - || - | - | - || - | - | - || - | - | - ||
 3 || 8 | 5 | 9 || 7 | 6 | 1 || 4 | 2 | 3 ||
 = || = | = | = || = | = | = || = | = | = ||
 2 || 1 | 9 | 8 || 3 | 4 | 2 || 5 | 6 | 7 ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || 6 | 7 | 2 || 1 | 9 | 5 || 3 | 4 | 8 ||
 - || - | - | - || - | - | - || - | - | - ||
 0 || 5 | 3 | 4 || 6 | 7 | 8 || 9 | 1 | 2 ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 ||


Please input a valid coordinate in the form of  "x,y"  (where the ranges for x a
nd y are [0,8]). Else if you want to quit, please input "quit"
8,8
Please input a valid digit 1-9
4

 8 || 3 | 4 | 5 || 2 | 8 | 6 || 1 | 7 | 4 ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || 2 | 8 | 7 || 4 | 1 | 9 || 6 | 3 | 5 ||
 - || - | - | - || - | - | - || - | - | - ||
 6 || 9 | 6 | 1 || 5 | 3 | 7 || 2 | 8 | 4 ||
 = || = | = | = || = | = | = || = | = | = ||
 5 || 7 | 1 | 3 || 9 | 2 | 4 || 8 | 5 | 6 ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || 4 | 2 | 6 || 8 | 5 | 3 || 7 | 9 | 1 ||
 - || - | - | - || - | - | - || - | - | - ||
 3 || 8 | 5 | 9 || 7 | 6 | 1 || 4 | 2 | 3 ||
 = || = | = | = || = | = | = || = | = | = ||
 2 || 1 | 9 | 8 || 3 | 4 | 2 || 5 | 6 | 7 ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || 6 | 7 | 2 || 1 | 9 | 5 || 3 | 4 | 8 ||
 - || - | - | - || - | - | - || - | - | - ||
 0 || 5 | 3 | 4 || 6 | 7 | 8 || 9 | 1 | 2 ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 ||



Board is full - incorrect solution.  Please modify your solution.
Please input a valid coordinate in the form of  "x,y"  (where the ranges for x a
nd y are [0,8]). Else if you want to quit, please input "quit"


3) Trying to overwrite piece that is part of the template

H:\My Documents\Visual Studio 2013\Projects\lab4\Debug>lab4 Sudoku

 8 || 5 | 3 |   ||   | 7 |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || 6 |   |   || 1 | 9 | 5 ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 6 ||   | 9 | 8 ||   |   |   ||   | 6 |   ||
 = || = | = | = || = | = | = || = | = | = ||
 5 || 8 |   |   ||   | 6 |   ||   |   | 3 ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || 4 |   |   || 8 |   | 3 ||   |   | 1 ||
 - || - | - | - || - | - | - || - | - | - ||
 3 || 7 |   |   ||   | 2 |   ||   |   | 6 ||
 = || = | = | = || = | = | = || = | = | = ||
 2 ||   | 6 |   ||   |   |   || 2 | 8 |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 ||   |   |   || 4 | 1 | 9 ||   |   | 5 ||
 - || - | - | - || - | - | - || - | - | - ||
 0 ||   |   |   ||   | 8 |   ||   | 7 | 9 ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 ||


Please input a valid coordinate in the form of  "x,y"  (where the ranges for x a
nd y are [0,8]). Else if you want to quit, please input "quit"
0,3
Please input a valid digit 1-9
1
Cannot modify elements of the original template.
Please input a valid coordinate in the form of  "x,y"  (where the ranges for x a
nd y are [0,8]). Else if you want to quit, please input "quit"


4) Badly formed command lines

H:\My Documents\Visual Studio 2013\Projects\lab4\Debug>lab4
Please input at least one argument which is "TicTacToe" or "Gomoku" or  "Sudoku"
 or "UltimateTicTacToe" in addition to the program name

H:\My Documents\Visual Studio 2013\Projects\lab4\Debug>lab4 Sudokuasgj
Please input at least one argument which is "TicTacToe" or "Gomoku" or  "Sudoku"
 or "UltimateTicTacToe" in addition to the program name



 Extra Credit Testing (Ultimate TicTacToe):
 1) Ultimate TicTacToe Win - Diagonal
Player O: 1,1; 2,2; 3,3; 5,5; 6,5; 4,5; 7,9; 8,8
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
8,7

 9 ||   |   |   ||   |   |   || O |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 ||   |   |   ||   |   |   || X | O |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 ||   |   |   ||   |   |   || X | X |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 ||   |   |   ||   |   | X ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 ||   |   |   || O | O | O ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 ||   |   |   ||   | X | X ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   |   | O ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 ||   | O |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player X: 2,1; 3,1; 5,4; 6,4; 6,6; 7,7; 7,8; 8,7
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
9,7

 9 ||   |   |   ||   |   |   || O |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 ||   |   |   ||   |   |   || X | O |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 ||   |   |   ||   |   |   || X | X | O ||
 = || = | = | = || = | = | = || = | = | = ||
 6 ||   |   |   ||   |   | X ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 ||   |   |   || O | O | O ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 ||   |   |   ||   | X | X ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   |   | O ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 ||   | O |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player O: 1,1; 2,2; 3,3; 5,5; 6,5; 4,5; 7,9; 8,8; 9,7
The Player O win the game !


2) Ultimate TicTacToe Win - Horizontal

Player O: 5,5; 5,4; 5,6; 7,6; 8,5; 8,6; 9,6; 1,6; 2,5
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
2,6

 9 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 || O | X |   ||   | O |   || O | O | O ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || X | O |   || X | O |   || X | O | X ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || X |   |   ||   | O | X || X |   | X ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player X: 4,5; 6,4; 7,5; 7,4; 9,4; 9,5; 1,5; 1,4; 2,6
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
3,4

 9 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 || O | X |   ||   | O |   || O | O | O ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || X | O |   || X | O |   || X | O | X ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || X |   | O ||   | O | X || X |   | X ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player O: 5,5; 5,4; 5,6; 7,6; 8,5; 8,6; 9,6; 1,6; 2,5; 3,4
The Player O win the game !


3) Ultimate TicTacToe Win - Vertical

Player X: 2,1; 3,2; 3,1; 3,3; 1,6; 2,5; 3,4; 2,8; 3,7
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
1,8

 9 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 || O | X |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || O | O | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 || X |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || O | X |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || O | O | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   | O | X ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 || O | O | X ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player O: 1,1; 2,3; 2,2; 1,2; 1,4; 1,5; 2,4; 1,7; 2,7; 1,8
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
1,9

 9 || X |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 || O | X |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || O | O | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 || X |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || O | X |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || O | O | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   | O | X ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 || O | O | X ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | X ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player X: 2,1; 3,2; 3,1; 3,3; 1,6; 2,5; 3,4; 2,8; 3,7; 1,9
The Player X win the game !


3) Ultimate TicTacToe Draw

Player X: 2,1; 3,3; 3,2; 1,3; 4,1; 6,1; 5,2; 6,3; 8,1; 8,2; 7,3; 8,3; 2,4; 1,5;
3,5; 1,7; 3,7; 2,8; 1,9; 5,4; 5,5; 7,4; 8,4; 9,4; 7,8; 9,9; 8,7; 9,7; 4,7; 4,8
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
5,8


 9 || X |   |   ||   |   |   || O | O | X ||
 - || - | - | - || - | - | - || - | - | - ||
 8 || O | X | O || X | O |   || X | O | O ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || X | O | X || X | O |   || O | X | X ||
 = || = | = | = || = | = | = || = | = | = ||
 6 ||   |   | O || O |   |   || O | O |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || X | O | X || O | X |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || O | X | O || O | X |   || X | X | X ||
 = || = | = | = || = | = | = || = | = | = ||
 3 || X | O | X ||   |   | X || X | X |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 || O | O | X || O | X | O || O | X | O ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | O || X | O | X || O | X | O ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player O: 1,1; 2,2; 2,3; 3,1; 1,2; 5,1; 4,2; 6,2; 7,1; 9,1; 7,2; 9,2; 1,4; 3,4;
2,5; 3,6; 2,7; 1,8; 3,8; 4,4; 4,5; 4,6; 7,6; 8,6; 7,7; 8,8; 9,8; 8,9; 7,9; 5,7;
5,8
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
4,9


 9 || X |   |   || X |   |   || O | O | X ||
 - || - | - | - || - | - | - || - | - | - ||
 8 || O | X | O || X | O |   || X | O | O ||
 - || - | - | - || - | - | - || - | - | - ||
 7 || X | O | X || X | O |   || O | X | X ||
 = || = | = | = || = | = | = || = | = | = ||
 6 ||   |   | O || O |   |   || O | O |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 || X | O | X || O | X |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 || O | X | O || O | X |   || X | X | X ||
 = || = | = | = || = | = | = || = | = | = ||
 3 || X | O | X ||   |   | X || X | X |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 || O | O | X || O | X | O || O | X | O ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O | X | O || X | O | X || O | X | O ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player X: 2,1; 3,3; 3,2; 1,3; 4,1; 6,1; 5,2; 6,3; 8,1; 8,2; 7,3; 8,3; 2,4; 1,5;
3,5; 1,7; 3,7; 2,8; 1,9; 5,4; 5,5; 7,4; 8,4; 9,4; 7,8; 9,9; 8,7; 9,7; 4,7; 4,8;
4,9
62 turn have been played. No winning moves remain.


4) Ultiamte ticTacToe - Entering invalid coordinate, while you still have another active cell.


If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
1,1

 9 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 8 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 7 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 6 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 5 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 4 ||   |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 3 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 2 ||   |   |   ||   |   |   ||   |   |   ||
 - || - | - | - || - | - | - || - | - | - ||
 1 || O |   |   ||   |   |   ||   |   |   ||
 = || = | = | = || = | = | = || = | = | = ||
 # || 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||


Player O: 1,1
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"
5,6
If a game is active in one cell, please input a valid coordinate in forms of  "x
,y"  within that cell. If you have just completed a game within a cell, feel fre
e to move on to another board of your choice.  Else if you want to quit, please
input "quit"


