package lab10;

import java.util.Iterator;
import java.util.LinkedList;

import cse131.ArgsProcessor;
import sedgewick.StdDraw;

public class Round {

	private LinkedList<Food> food;
	private double maxFoodRadius;
	private double minFoodRadius;
	SlowBlob blob;
	Guard player;
	boolean win;
	boolean gameOver;

	/**
	 *  constructor
	 * @param maxFoodSize, the player can set the maximum food size
	 * @param minFoodSize  the player can set the minimum food size
	 */
	public Round(int maxFoodSize, int minFoodSize, boolean setSlow){

		this.blob = new SlowBlob(0.03); // the default radius of blob
		this.blob.setGetSlow(setSlow); // give player a choice to get slow or not
		this.food = new LinkedList<Food>();
		this.maxFoodRadius = (double)maxFoodSize / 1000.0;
		this.minFoodRadius = (double)minFoodSize / 1000.0;
		this.win = false;
		this.gameOver = false;

	}

	/**
	 *  ROUND 1, food is static
	 * @param player can choose how many food displayed at first
	 */
	public void roundOne(int numFood){
		// make a food list randomly
		for(int i = 0; i < numFood; i++){
			Food f = makeFood(0);
			this.food.add(f);
		}
		this.animation(food, 100000, 1);

	}

	/**
	 *  ROUND 2, food is moving
	 * @param player can choose how many food will be displayed at first
	 */
	public void roundTwo(int numFood){

		// add the  food into the food list
		for(int i = 0; i < numFood; i++){
			Food f = makeFood(1);
			this.food.add(f);
		}

		this.animation(food, 70000, 2);

	}

	/**
	 *  ROUND 3, <1> food can be static or moving
	 *           <2> Policemen(PC) or Guard will come up to catch blob, 
	 *               when blob got captured, game over
	 *           <3> big blob can also eat small PC
	 * @param numFood
	 */
	public void roundThree(int numFood){

		//this.blob = new Blob(0.03); // in this round, blob don't slow down due to grow

		LinkedList<Food> food = new LinkedList<Food>();
		int numStatic = (int)(numFood / 2.0);
		int numMoving = numFood - numStatic;
		// add static food to food list
		for(int i = 0; i < numStatic; i++){
			Food f = makeFood(0);
			food.add(f);
		}
		// add moving food to food list
		for(int i = 0; i < numMoving; i++){
			Food f = makeFood(1);
			food.add(f);
		}
		// make a guard list 
		LinkedList<Guard> guard = new LinkedList<Guard>();
		for(int i = 0; i < 0; i++){
			Guard g = makeGuard();
			guard.add(g);
		}
		// animation
		int showPauseTime = 20;
		int timeLimit = 40000;
		int numTimes = timeLimit / showPauseTime;
		while(! this.win && ! this.gameOver){
			StdDraw.clear();
			//draw food
			for(Food f : food){
				f.draw();
			}
			// draw guard 
			for(Guard g : guard){
				g.draw();
			}
			// draw blob
			this.blob.draw();

			// check if  food is eaten
			Iterator<Food> irF = food.iterator();
			while(irF.hasNext()){
				Food f = irF.next();
				if(f.beenEaten(this.blob)){
					this.blob.setRadius(f);
					irF.remove();
				}
			}
			if(food.size() <= 3){
				food.add(makeFood(0));
				food.add(makeFood(0));
				food.add(makeFood(1));
				food.add(makeFood(1));
				guard.add(makeGuard());

			}
			// check if some old guard gotten eaten, and 
			//  simultaneously, check if this blob is got eaten by the guard
			Iterator<Guard> irG = guard.iterator();
			while(irG.hasNext()){
				Guard g = irG.next();
				if(this.blob.beenEaten(g)){
					g.setRadius(this.blob);
					this.gameOver = true;
				}
				if(g.beenEaten(this.blob)){
					irG.remove();
				}
			}		
			//check if win
			if(this.blob.getMass() >= 200){
				this.win = true;
			}
			// check if game over
			numTimes--;
			if(numTimes <= 0){
				this.gameOver = true;
			}
			StdDraw.show(20);
		}
	}


	/**
	 *  text will be displayed when used when game is completed, as a celebration
	 *  this is also used in the opening show in MyGame, text will not show then 
	 */
	public void finished(){

		FadingWigglingMessage  finishWin  = new FadingWigglingMessage(20, "Win !!!", 3000,0.005);
		finishWin.setSpot(0.5, 0.7);
		FadingWigglingMessage  finishGame =  new FadingWigglingMessage(20, "Game Completed", 3000,0.005);
		finishGame.setSpot(0.5, 0.5);
		LinkedList<Guard> g = new LinkedList<Guard>();
		g.add(makeGuard());
		g.add(makeGuard());
		g.add(makeGuard());
		g.add(makeGuard());
		LinkedList<Food> f = new LinkedList<Food>();
		f.add(makeFood(0));
		f.add(makeFood(0));
		f.add(makeFood(0));
		f.add(makeFood(1));
		f.add(makeFood(1));
		f.add(makeFood(1));
		f.add(makeFood(1));
		f.add(makeFood(1));
		//animation
		boolean mousePressed = false;
		while(!finishWin.isDone() && !mousePressed){
			StdDraw.clear();
			for(Guard guard : g){
				guard.draw();
			}
			for(Food food : f){
				food.draw();
			}
			finishWin.draw();
			finishGame.draw();
			
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(40);
		}
	}

	/**
	 *   this method is mainly used in ROUND 1 and ROUND 2 as animation part
	 * @param food list
	 * @param timeLimit, how much times the player have to finish the particular round
	 * @param roundNumber, given the roundNumber, to determine the food would be added is moving or static
	 */
	public void animation(LinkedList<Food> food, int timeLimit, int roundNumber){

		// give the palyer a certain amount of time, without finish in the given time, game over
		int showPauseTime = 20;
		int numTimes = timeLimit / showPauseTime;
		while(! this.win && ! this.gameOver){
			StdDraw.clear();
			// draw the food
			for(Food f : food){
				f.draw();
			}
			// draw Blob
			this.blob.draw();
			// check if food is eaten and set Blob's radius
			Iterator<Food> ir = food.iterator();
			while(ir.hasNext()){
				Food f = ir.next();
				if(f.beenEaten(this.blob)){
					this.blob.setRadius(f);
					ir.remove();
				}
			}
			// maintain there will be 5 food on the screen
			if(food.size() <= 3){
				if(roundNumber == 1){
					this.roundOne(3);					
				}
				else if (roundNumber == 2){
					this.roundTwo(3);
				}
			}
			// check if win or not
			if(this.blob.getMass() >= 200){ // the default stadard for roundOne is 200
				this.win = true;
			}
			// check if game over
			numTimes = numTimes - 1;
			if(numTimes <= 0){
				this.gameOver = true;
			}
			StdDraw.show(showPauseTime);

		}

	}

	/**
	 *  make a single particular type of food
	 * @param foodType, 0 stands for static food, otherwise moving food
	 * @return  a single particular food
	 */
	public Food makeFood(int foodType){
		if(foodType == 0){ // this is the static food
			//dynamically change the largest food's size
			this.maxFoodRadius = 0.5 * this.maxFoodRadius +  Math.random() * this.blob.getRadius();
			// make a food list randomly
			double x = Math.random();
			double y = Math.random();
			double r = Math.random() * (this.maxFoodRadius - this.minFoodRadius) + this.minFoodRadius;
			Food f = new Ball(x, y, r);
			return f;
		}
		else{ // this is the moving ball
			double x = Math.random();
			double y = Math.random();
			double r = Math.random() *(this.maxFoodRadius - this.minFoodRadius) + this.minFoodRadius;
			double velocity = 0.008 * Math.random();
			Food f = new MovingBall(x, y, r, velocity);
			return f;		
		}
	}

	/**
	 * make a single particular guard
	 * @return a guard or PC
	 */
	public Guard makeGuard(){
		double x = Math.random();
		double y = Math.random();
		double r = (1 + Math.random()) * this.blob.getRadius();
		double velocity = 0.006 * Math.random();
		Guard g = new MovingBall(x, y, r, velocity);
		g.setGuard(true);
		return g;
	}




}
