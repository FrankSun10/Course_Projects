package lab10;

import java.awt.Color;
import java.awt.Font;

import sedgewick.StdDraw;

// SlowBlob is a Blob, which can move slowly 

public class SlowBlob extends Blob {

	int  historyPosition;
	int currentP;
	private double factor;
	private boolean getSlow;

	/**
	 *  constructor
	 * @param radius  the radius of the slow blob
	 */
	public SlowBlob(double radius) {
		super(radius);
		this.factor = 0.5;
		int size = (int) (this.mass * this.factor);
		this.historyPosition = 0;
		this.currentP = 0;
		this.getSlow = true;
	}

	/**
	 * player can set if the blob will get slow due to mass growth
	 * @param getSlow
	 */
	public void setGetSlow(boolean getSlow){
		this.getSlow = getSlow;
	}
	/**
	 *  reset the radius of the blob by eating food
	 */
	public void setRadius(Food food){
		
		double x = this.x;
		double y = this.y;
		double dist = Math.sqrt(Math.pow(x - food.getX(), 2) + Math.pow(y - food.getY(), 2));
		if(food.getRadius() + dist < this.radius){
			this.radius = this.radius + food.getRadius() / 10.0;
		}
	}
	/**
	 * the blob can also be eaten by a guard
	 */
	public boolean beenEaten(Guard g){

		double guardX = g.getX();
		double guardY = g.getY();
		double dist = Math.sqrt(Math.pow(this.x - guardX, 2) 
				+ Math.pow(this.y - guardY, 2));
		if(dist + this.radius <= g.getRadius()){
			return true;
		}
		return false;
	}

	/**
	 * draw the blob, 
	 */
	@Override
	public void draw(){
		if(this.getSlow){
			
			double x = StdDraw.mouseX();
			double y = StdDraw.mouseY();
			// call the drawHelper method to draw the blob
			drawHelper();
			// by making a vector to make the blob slow
			this.x = this.x + (x - this.x) / (this.mass / 2.0);
			this.y = this.y + (y - this.y) / (this.mass / 2.0);	
		}
		else{
			this.x = StdDraw.mouseX();
			this.y = StdDraw.mouseY();
			drawHelper();
		}
	}

	/**
	 * draw the blob, help method
	 */
	public void drawHelper(){
		StdDraw.setPenColor(this.color);	
		StdDraw.filledCircle(this.x, this.y, this.radius);
		this.mass = (int)(1000 * this.radius);
		Font f = this.setText(300);
		StdDraw.setFont(f);
		double variationOfText = 0.011 * (this.radius / 0.03);
		StdDraw.text(this.x + variationOfText, this.y + variationOfText, this.name);
		StdDraw.text(this.x - variationOfText, this.y - variationOfText, Integer.toString(this.mass));
	}
	
	/**
	 * just draw the blob and name at a particular location
	 * @param x coordinate
	 * @param y coordinate
	 */
	public void basicDraw(double x, double y){
		StdDraw.setPenColor(Color.CYAN);
		this.x = x;
		this.y = y;
		StdDraw.filledCircle(this.x, this.y, this.radius);
		Font f = this.setText(400);
		StdDraw.setFont(f);
		StdDraw.text(this.x, this.y, this.name);
	}

}
