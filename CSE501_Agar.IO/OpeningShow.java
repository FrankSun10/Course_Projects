package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;

import sedgewick.StdDraw;

public class OpeningShow {

	private FadingWigglingMessage welcomeText;
	private Ball ball;
	private SlowBlob blob;

	/**
	 * constructor
	 * @param yText y coordinate of the welcome text
	 * @param yBall y coordinate of sine wave ball
	 */
	public OpeningShow(double yText, double yBall){
		// default component 
		this.welcomeText = new FadingWigglingMessage(20, "Welcome", 6000, 0.005);
		this.welcomeText.setSpot(0.5, yText); // set the spot of welcome message
		this.ball = new Ball(0.025 ,0.5 ,0.015);
		this.ball .setYOfSine(yBall); // set the spot of sine wave ball
		this.blob = new SlowBlob(0.05);
		this.blob.setGetSlow(false);// set the blob won't get slow because of growth
		this.blob.setName("Agar"); // set the name of blob as Agar in opening show
	}

	// welcome message
	public void message(){
		this.welcomeText.draw();
	}
	// get 
	public FadingWigglingMessage getWelcomeText() {
		return welcomeText;
	}

	/**
	 *  one of the OPENSHOW parts (each openShow part should have the same parameter)
	 *  this method used to draw balls for the opening show
	 *  specifically, draw a sine wave as the welcome
	 *  Also, you can choose to draw lines between balls by uncomment the draw-line part
	 */
	public void sineWaveBalls(){

		// make some food and guard as background
		Round open = new Round(45, 5, true);
		LinkedList<Food> food = new LinkedList<Food>();
		food.add(open.makeFood(0));
		food.add(open.makeFood(0));
		food.add(open.makeFood(1));
		food.add(open.makeFood(1));
		food.add(open.makeFood(1));
		LinkedList<Guard> guard = new LinkedList<Guard>();
		guard.add(open.makeGuard());
		guard.add(open.makeGuard());
		guard.add(open.makeGuard());

		while(! this.welcomeText.isDone()){
			StdDraw.clear();
			for(Food f : food) f.draw();
			for(Guard g : guard) g.draw();
			this.welcomeText.draw();

			// parameters for the sine wave path
			int size = 310;
			double[] varY = new double[size];
			double  varX = 0.05;
			double altitude = 0.1;
			double frequency = 1.0 / 200.0;

			double xS = 0.025;
			double yS = this.ball.getInitialYOfSine();
			double xL = 0.025 + varX;  
			double yL = this.ball.getInitialYOfSine();

			for(int i = 0; i < size; i= i + 18){
				varY[i] = altitude * Math.sin(2 * Math.PI *frequency *i);
				yS = this.ball.getInitialYOfSine() + varY[i];
				xS = xS + varX;
				StdDraw.line(xL, yL, xS, yS);// draw lines to thread the balls
				xL = xS;
				yL = yS;
				// draw some food, each of them is a new ball
				Ball ball = new Ball(xS, yS, this.ball.getRadius());
				ball.basicDraw();
			}
			StdDraw.show(20);
			//StdDraw.setPenRadius(0.003);
		}
	}

	/**
	 * Basically, this part is used in the opening show
	 */
	public void goAgar(){

		// parameters for set up the sine wave path
		int size = 310;
		double[] varY = new double[size];
		double varX = 0.05;
		double atitude = 0.1;
		double frequency = 1.0 / 200.0;
		double xS = 0.025;
		double yS = this.ball.getInitialYOfSine();

		// initialize a list of food
		LinkedList<Food> food = new LinkedList<Food>();
		for(int i = 0; i < size; i = i + 18){
			varY[i] = atitude * Math.sin(2 * Math.PI * frequency * i);
			yS = this.ball.getInitialYOfSine() + varY[i];
			xS = xS + varX;
			Food ball = new Ball(xS, yS, 0.015);
			food.add(ball);
		}

		xS = 0.025;
		yS = this.ball.getInitialYOfSine();
		//Blob b = new SlowBlob(this.blob.getRadius());

		// <<1>> the first line part of drawing the trajectory of the SlowBlob
		double xL = -0.05;
		double increasement = (xS - xL) / 25;
		double yL = this.ball.getInitialYOfSine();
		while(xL <= xS){
			StdDraw.clear();
			// keep drawing the food 
			for(Food x : food){
				x.basicDraw();
			}
			// draw the blob
			this.blob.basicDraw(xL, yL);
			xL = xL + increasement;
			StdDraw.show(20);
		}

		// draw a Blob and simulating eating 
		double x1 = -1, y1 = -1;
		double x2 = -1, y2 = -1;
		double x3 = -1, y3 = -1;	
		for(int i = 0; i < size; i = i + 18){
			StdDraw.clear();
			xS = xS + varX;
			yS = this.ball.getInitialYOfSine() + varY[i];
			this.blob.basicDraw(xS, yS);
			// draw every ball in the food list
			for(Food f : food){
				f.basicDraw();
			}	
			// draw S U N 
			Font font = new Font("serif", Font.BOLD, 40);
			StdDraw.setFont(font);
			if(yS <= 0.6 && yS >= 0.599 && xS < 0.5){
				x1 = xS;
				y1 = yS;
			}
			StdDraw.text(x1, y1, "131");
			if(yS > 0.4 && yS <0.402){
				x2 = xS;
				y2 = yS;
			}
			StdDraw.text(x2, y2, "Lab");
			if(yS <= 0.6 && yS > 0.599 && xS > 0.5){
				x3 = xS;
				y3 = yS;
			}
			StdDraw.text(x3, y3, "10");
			// draw the blob
			this.blob.basicDraw(xS, yS);
			// check each food in the list if got eaten and if so, 
			//set Blob b's radius according food, every time only one food is eaten
			Iterator<Food> ir = food.iterator();
			while(ir.hasNext()){
				Food f = ir.next();
				// check if the food is eaten
				if(f.beenEaten(this.blob)){
					this.blob.setRadius(f);
					ir.remove();
				}
			}
			StdDraw.show(300);
		}

		// << 2>> second line part of trajectory
		while(xS < 1.15){
			StdDraw.clear();
			StdDraw.setPenColor(Color.black);
			Font font = new Font("serif", Font.BOLD, 50);
			StdDraw.setFont(font);
			StdDraw.text(x1 + 0.1, 0.5, "Frank");
			//StdDraw.text(x2, 0.5, "Frank");
			StdDraw.text(x3 - 0.1, 0.5, "Sun");
			this.blob.basicDraw(xS, yS);
			xS = xS + 0.02;
			StdDraw.show(100);
		}
	}

	/**
	 * used to form a particular font
	 * @param size
	 * @return
	 */
	public Font setText(int size){

		int s = (int) (this.blob.getRadius() * size);
		Font f = new Font("serif", Font.BOLD, s);
		StdDraw.setPenColor(Color.white);
		return f;
	}
	
	/**
	 * random color generator 
	 * @return
	 */
	public Color genRandomColor(){
		Random r = new Random();
		int red = r.nextInt(256);
		int green = r.nextInt(256);
		int blue = r.nextInt(256);
		return new Color(red, green, blue);
	}

}
