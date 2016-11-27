Grader: Cameron Wong (cameronwong203@yahoo.com)
Grade: 91/100
-2 Tic Tac Toe with O's did not work properly
-3 testing gomoku errored
-3 testing vertical caused abortion in code
-3 Abortion on wrong number of commandlines
-1 Ran on wrong colored names
-2 Ran on two arguments
+5 extra credit

good job!


Lab 1-Frank Sun (Yanqing Sun) ID; 443269 Email_address:yanqing.sun@wustl.edu

1. warnings and errors
	(1) the major warnings I ran into when I built the program were type mismatching where I used int type as the loop
	variables for indexing vectors or strings. I modified the type of loop variables in these cases to size_t.
	(2) the most notice-worthy error I ran into in this lab was out of range error in the game board display function.
	Previously,I used unsigned int as the type of loop variable for the height part and I reduced the varialbe by one 
	after each iteration within the condition that the variable was greater or equal to zero. I added another condition
	that the loop variable should be also less than the height (the maxium value the loop variable can reach) to fix the 
	the error.

2. I ran the given two well formated plain files (tic-tac-toe.txt and gomoku.txt) and three different badly formated files
   to test my program. The three different bad files are:
	(1) bad1.txt, in which blank lines and incompleted lines were included
	(2) bad2.txt, in which only one dimension could be found in the first line
	(3) bad3.txt, in which a smaller dimension were given than the number of valid input.
   Also, the case that different dimensions was also test.
   The program ran good in those cases.

Extra credit:

I used four for loops to check all the neighbors of a non-empty ( which means a valid display) spot. And print out the non-empty
neighbors' information following the examples in the instruction.