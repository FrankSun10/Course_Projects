package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.biojava.bio.structure.align.util.SynchronizedOutFile;

import cse131.ArgsProcessor;
import sedgewick.StdDraw;

public class MyGrame {

	public static void main(String[] args) {

		final int showPauseTime = 20;
		// wait for the mouse click
		boolean mousePressed = false;
		while(!mousePressed){
			// do nothing, wait
			mousePressed = StdDraw.mousePressed();
			StdDraw.pause(20);
		}
		
////////////////////////////////////////////////////////// OPENING SHOW

		// Illustration <1> static food, moving food and PC will acts as background
		//              <2> wiggling welcome message will show up
		//              <3> a sine wave of static food without mass info will acts as a smile face, although not much like
		//              <4> a blob will come up from no where to eat the food one by one
		//              <5> after the blob disappear, a slide show round info will come next

		// opening show 
		OpeningShow openingShow = new OpeningShow(0.7, 0.5);
		openingShow.sineWaveBalls();
		openingShow.goAgar();
	
		// draw a slide to reminder player to go on
		// give the slide that contain the content of round 1
		mousePressed = false;
		Slide s1 = new Slide();
		while(! mousePressed){
			StdDraw.clear();		
			s1.contentRoundOne();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(showPauseTime);
		}


/////////////////////////////////////////////////////////////////////////  ROUND 1		

		// Instruction:  <1> Food is static 
		//               <2> you can set the maximum size and minimum size of the food
		//               <3> you can set whether the blob get slow by eating food, it does by default
		//               <4> need to grow to 200, with in 10000 / 20 msecs = 500 s

		// set blob become slow or not by setting false or true
		// 45 is the initial size of the max food, 3 is the initial size of min food
		// the maximum size of food is changing according to the size of blob
		Round roundOne =  new Round(45,3,true); 
		// give a name to your blob
		ArgsProcessor ap = new ArgsProcessor(args);
		String name = ap.nextString("What's your name?");
		roundOne.blob.setName(name);

		// go on before win and game over
		while(!roundOne.win && !roundOne.gameOver){
			//   how many food do you want initially 
			//   without less than three food afterwards, and without more than five food afterward
			roundOne.roundOne(8);
			StdDraw.show(showPauseTime);
		}

		//  check is win or game over
		//  if not win, display game over slide, stop the game (nothing else can be done
		boolean isWin1 = roundOne.win;
		while(!isWin1){
			StdDraw.clear();
			new Slide().gameOver();
			StdDraw.show(showPauseTime);
		}
		// if win go to the win celebration slide
		// but without response in a certain time, game over automatically
		mousePressed = false;
		while(isWin1 && ! mousePressed){
			StdDraw.clear();
			new Slide().nextRound();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(showPauseTime);
		}

		StdDraw.clear();
		StdDraw.show(showPauseTime);


////////////////////////////////////////////////////////////////////////////   ROUND 2
		
		// Instruction <1> food is moving in different directions with different velocity
		//             <2> you can set the maximum and minimum food size 
		//             <3> you can set whether the blob get slow because of eating, it does not by default
		//             <4> grow up to 200 with in 7000 / 20 = 350 s 

		// give the slide that contains the content of round 2
		Slide s2 = new Slide();
		s2.contentRoundTwo();
		mousePressed = false;
		while(! mousePressed){
			// do nothing, wait for clicking
			StdDraw.show(50);
			mousePressed = StdDraw.mousePressed();
		}

		// set blob become slow or not by setting false to true
		// 45 is the initial size of the max food, 3 is the initial size of min food
		Round roundTwo = new Round(45,3,false);
		roundTwo.blob.setName(name);

		// go on before win or game over 
		while(! roundTwo.win && ! roundTwo.gameOver){
			StdDraw.clear();
			roundTwo.roundTwo(6);;
			StdDraw.show(showPauseTime);
		}
		// check is win or game over
		boolean isWin2 = roundTwo.win;
		while(!isWin2){
			StdDraw.clear();
			new Slide().gameOver();
			StdDraw.show(showPauseTime);
		}
		// if win go to the win celebration slide
		// but without response in a certain time, game over automatically
		mousePressed = false;
		while(isWin2 && ! mousePressed){
			StdDraw.clear();
			new Slide().nextRound();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(showPauseTime);
		}

		StdDraw.clear();
		StdDraw.show(showPauseTime);

/////////////////////////////////////////////////////////////////////////   ROUND 3

		// Instruction <1> food can be both moving or static
		//             <2> you can set the maximum or minimum food size
		//             <3> you can set whether the blob get slow because of eating, it does not by default
		//             <4> so call police PC will show up, when it show up, its size is bigger than the blob
		//             <5> no time limit, as long as the blob does not get eaten by PC
		//             <6> the blob can also eat PC whose size is smaller
		
		
		// display the slide that gives the round 3's instruction
		Slide s3 = new Slide();
		s3.contentRoundThree();
		mousePressed = false;
		while(! mousePressed){
			// do noting, wait
			StdDraw.show(20);
			mousePressed = StdDraw.mousePressed();
		}

		// set blob become slow or not by setting false to true
		// 45 is the initial size of the max food, 3 is the initial size of min food
		Round roundThree = new Round(45,5,false); 
		roundThree.blob.setName(name);
		
		while(! roundThree.win && ! roundThree.gameOver){
			StdDraw.clear();
			roundThree.roundThree(6);
			StdDraw.show(showPauseTime);
		}

		// check is win or game over
		boolean isWin3 = roundThree.win;
		while(!isWin3){
			StdDraw.clear();
			new Slide().gameOver();
			StdDraw.show(showPauseTime);
		}
		// if win go to the win celebration slide
		mousePressed = false;
		while(isWin3 && ! mousePressed){
			StdDraw.clear();
			new Round(45,5,true).finished();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(showPauseTime);
		}


		
		
		
	}

}
