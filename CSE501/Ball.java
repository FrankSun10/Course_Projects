package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import sedgewick.StdDraw;

public class Ball implements  Food {

	private double x;
	private double y;
	private double radius;
	// initialYOfSine gives the initial y position of the sine wave, used in opening show
	private double initialYOfSine; 
	private boolean isDead;
	private Color color;

	/**
	 * 
	 * @param x coordinate
	 * @param y coordinate
	 * @param r radius
	 * @param initial  gives the initial y position of the sine wave, used in opening show
	 */
	public Ball(double x, double y, double r){
		this.x = x;
		this.y = y;
		this.radius = r;
		this.initialYOfSine = 0.5;
		this.isDead = false;
		this.color = genRandomColor();
	}
	
	/**
	 * some bsic setters and getters
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
	public double getInitialYOfSine(){
		return this.initialYOfSine;
	}
	public void setYOfSine(double d){
		this.initialYOfSine = d;
	}
	/**
	 * basic draw method, used mainly in opening show
	 */
	public void basicDraw(){
		StdDraw.setPenColor(genRandomColor());

		StdDraw.filledCircle(this.x, this.y, this.radius);
	}
	
	/**
	 * draw the mass and food
	 */
	public void draw(){
		StdDraw.setPenColor(this.color);
		StdDraw.filledCircle(this.x, this.y, this.radius);
		// draw text of mass
		StdDraw.setPenColor(Color.white);
		int size = (int)(this.radius * 500);
		Font f = new Font("serif", Font.BOLD, size);
		StdDraw.setFont(f);
		int mass = (int)(1000 * this.radius);
		StdDraw.text(this.x, this.y, Integer.toString(mass));
	}
	
	@Override
	/**
	 *  ball as a food
	 */
	public boolean beenEaten(SlowBlob b) {
		
		double x = b.x;
		double y = b.y;
		double dist = Math.sqrt(Math.pow(this.x - x, 2) + Math.pow(this.y - y, 2));
		if(this.radius + dist <= b.getRadius()){
			this.isDead = true;
			return true;
		}
		return false;
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
