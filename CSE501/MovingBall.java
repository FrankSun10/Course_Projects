package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import sedgewick.StdDraw;

// this class diagonal ball implement a ball moving across the 
//   screen diagonally
public class MovingBall implements Food, Guard{
	
	private double x;
	private double y;
	private double radius;
	private String position;
	private Color color;
	private double velocity;
	private int direction;
	private boolean guard;
	
	/**
	 *  constructor
	 * @param x coordinate
	 * @param y coordinate
	 * @param r radius
	 * @param velocity of the moving ball 
	 */
	public MovingBall(double x, double y, double r, double velocity){
		this.x = x;
		this.y = y;
		this.radius = r;
		this.velocity = velocity;
		this.direction = genRandomDirection();
		this.color = genRandomColor();
		this.guard = false;
		String s1 = (y < 0.5)? "B" : "U";
		String s2 = (x < 0.5)? "L" : "R";
		this.position = s1 + s2;    // the argument of position should chose from "BL", "BR", "UL" and "UR"
	}
	
	/**
	 * basic setters and getters
	 */
	@Override
	public double getRadius() {
		return this.radius;
	}
	@Override
	public double getX() {
		return this.x;
	}
	@Override
	public double getY() {
		return this.y;
	}
	@Override
	public void setGuard(boolean guard){
		this.guard = guard;
	}

	/** 
	 * draw the moving ball
	 */
	@Override
	public void draw() {
		
		StdDraw.setPenColor(this.color);
		StdDraw.filledCircle(this.x, this.y, this.radius);
		// draw the text
		StdDraw.setPenColor(Color.white);
		int size = (int)(this.radius * 500);
		Font f = new Font("serif", Font.BOLD, size);
		StdDraw.setFont(f);
		int mass = (int)(1000 * this.radius);
		if(! this.guard){ // the movingball acts as food
			StdDraw.text(this.x, this.y, Integer.toString(mass));
		}
		else{ // the movingball acts as a guard
			StdDraw.text(this.x, this.y, "PC");
		}
		// change the position where to draw next ball
		// vertical ball will keep moving on the same path
		if(this.direction == 0){
			this.y = (this.position.equals("BL") || this.position.equals("BR"))? this.y + this.velocity : this.y - this.velocity;
			if(this.y >= 1.0) {
				this.y = 0.0001;
				this.position = "BL";
			}
			if(this.y <= 0.0) {
				this.y = 1.0;
				this.position = "UL";
			}
		}
		// horizontal ball 
		if(this.direction == 1){
			this.x = (this.position.equals("BL") || this.position.equals("UL"))? this.x + this.velocity : this.x - this.velocity;
			if(this.x >= 1.0){
				this.x = 0.00001;
				this.position = "BL";
			}
			if(this.x <= 0.0){
				this.x = 1.0;
				this.position = "BR";
			}
		}
		// diagonal ball wont' disappear by just moving out of the scene it keeps bouncing in the scene
		if(this.direction == 2){			
			this.x = (this.position.equals("BL") || this.position.equals("UL"))? this.x + this.velocity : this.x - this.velocity;
			this.y = (this.position.equals("BL") || this.position.equals("BR"))? this.y + this.velocity : this.y - this.velocity;
			if(this.x >= 1.0 && this.y >= 1.0) this.position = "UR";
			if(this.x <= 0.0 && this.y <= 0.0) this.position = "BL";
			if(this.x <= 0.0 && this.y >= 1.0) this.position = "UL";
			if(this.x >= 1.0 && this.y <= 0.0) this.position = "BR";
		}
		
	}

	/**
	 *   see if the food is eaten by a BLob
	 */
	public boolean beenEaten(SlowBlob b){
		// this is the SlowBlob's current location
//		double x = b.historyX[b.currentP];
//		double y = b.historyY[b.currentP];
		double x = b.x;
		double y = b.y;
		
		double dist = Math.sqrt(Math.pow(this.x - x, 2) + Math.pow(this.y - y, 2));
		if(this.radius > b.getRadius()){
			return false;
		}
		else if(dist + this.radius > b.getRadius()){
			return false;
		}
		else{
			//this.isDead = true;
			return true;
		}
	}
	
	/**
	 * random color generator
	 * @return
	 */
	public static Color genRandomColor(){
		Random r = new Random();
		int red = r.nextInt(256);
		int green = r.nextInt(256);
		int blue = r.nextInt(256);
		return new Color(red, green, blue);
	}
	
	/**
	 * this method randomly give a direction the moving ball move
	 * @return
	 */
	public static int genRandomDirection(){
		// 0 represent horizontal
		// 1 represent vertical
		// 2 represent diagonal
		Random r =  new Random();
		return r.nextInt(3);
	}

	/**
	 * guard eat blob and radius increase
	 */
	@Override
	public void setRadius(SlowBlob b) {
		
//		double x = b.historyX[b.currentP];
//		double y = b.historyY[b.currentP];
		double x = b.x;
		double y = b.y;
		double dist = Math.sqrt(Math.pow(this.x - x, 2) + Math.pow(this.y - y, 2));
		if(dist + b.getRadius() <= this.radius){
			this.radius = this.radius + b.getRadius() / 10.0;
		}
		
	}
	@Override
	public void basicDraw() {
		// FIXME Auto-generated method stub
		
	}


}