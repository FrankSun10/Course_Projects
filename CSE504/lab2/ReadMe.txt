
Lab2_Frank. Author: Frank Sun (Yanqing Sun). Id: 443269

Grader: Daniel Lerner (d.lerner@wustl.edu)
Grade: 104/100 (extra credit +5)
-signed/unsigned warning in tic_tac_toe.cpp - TicTacToeGame::almost_win (-1)
-Note: While you used rand() to generate a random move for the auto player's first move, you didn't 'seed' the number generator
This makes the first move of the auto player not actually random, when it should be (-0)

when I buit my program, I run into two warnings:

(1) not all control cases have return value for the the play() method
	 
	I fixed the warning by returning a not-finish err which was defined in EnumHeader at the end of the method

(2) signed / unsigned mismatch in a while loop (line 218) in auto_player() method
	
	I fixed the warning by changing the type of the indexes  to the game piece vector from int to unsinged int.
	But after that, the abs() function indicated error because taking unsigned type. I casted the unsigned arguments
	to int and fixed the error


Extra credit:

	I implemented this part by implementing two methods, auto_player() which returns int and takes no parameter execept 
	the instance member varialbes in the TicTacToeGame class, almost_win() method which is a void method but takes a vector
	of int, two unsigned int references, two int, and a string type variable as parameters. The almost_win() mehtod determines
	what is the next spot to move to win the game.
	
	The first move of the auto player is made randomly. Starting from the second move, the auto player would make a random
	move based on the previous moves, after that move, there would be a almost-win situation which means with another more
	possible move, the auto-player could win the game. In addition to just constructing almost-win situation, the auto player
	method allows the auto player to prevent the user_driven player from win by detecting and spoiling the almost-win situation 
	for the user-driven player with the almost_win() method. At last, the auto_palyer() method allows the auto player to take 
	every chance to win.