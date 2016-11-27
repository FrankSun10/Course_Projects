package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;

//import lab7solved.Point;
//import lab7solved.Vector;
import sedgewick.StdDraw;

/**
 * The Blob is like a HorzBall or VertBall except that it moves to
 *   where the mouse currently is when draw() is called.
 *   
 * @author roncytron
 *
 */
public class Blob implements Anim{

	protected double x;
	protected double y;
	protected double radius;   // NOT final, so you can change it as it eats or vomits food
	protected Color color;
	protected String name;
	protected int mass;

	/**
	 *  constructor
	 * @param radius
	 */
	public Blob(double radius) {
		this.radius = radius;
		this.color  = genRandomColor();
		this.x      = 0.5;
		this.y      = 0.5;
		this.name = "";
		this.mass = (int)(1000 * this.radius);
	}

	/**
	 * below goes a series of setters and getters
	 * @return
	 */

	public double getRadius() {
		return radius;
	}
	public int getMass() {
		return mass;
	}
	public double getX() {
		return x;
	}
	public double getY() {
		return y;
	}
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * every time when the Blob eat some food, its size change according to the mass of the food;
	 * @param food
	 */
	public void setRadius(Food food) {
		double x = food.getX();
		//System.out.println(food.getX());
		double y = food.getY();
		double dist = Math.sqrt(Math.pow(this.x - x, 2) + Math.pow(this.y - y, 2));
		if(food.getRadius() > this.radius){
			return;
		}
		else if(food.getRadius() + dist > this.radius){
			return;
		}
		else{
			this.radius = this.radius + food.getRadius()/10.0;
		}
	}

	/**
	 * basic draw method, used in the opening show
	 * @param x
	 * @param y
	 */
	public void basicDraw(double x, double y){
		StdDraw.setPenColor(Color.CYAN);
		this.x = x;
		this.y = y;
		StdDraw.filledCircle(this.x, this.y, this.radius);
	}

	@Override
	/**
	 *  draw with the Blob with mouse 
	 */
	public void draw() {

		this.x = StdDraw.mouseX();
		this.y = StdDraw.mouseY();
		StdDraw.setPenColor(color);
		StdDraw.filledCircle(this.x, this.y, this.radius); //
		// draw the mass 
		this.mass = (int)(1000 * this.radius);
		Font f = this.setText(300);
		StdDraw.setFont(f);
		double variationOfText = 0.011 * (this.radius / 0.03);
		StdDraw.text(this.x + variationOfText, this.y + variationOfText, this.name);
		StdDraw.text(this.x - variationOfText, this.y - variationOfText, Integer.toString(this.mass));
		//StdDraw.show(2);
	}

	/**
	 * Blob blob can also be eaten by guard
	 */
	public boolean beenEaten(Guard guard){
		double guardX = guard.getX();
		double guardY = guard.getY();
		double dist = Math.sqrt(Math.pow(this.x - guardX, 2) + Math.pow(this.y - guardY, 2));
		if(dist + this.radius <= guard.getRadius()){
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

	/**
	 * used to form a particular font
	 * @param size
	 * @return
	 */
	public Font setText(int size){
		int s = (int) (this.radius * size);
		Font f = new Font("serif", Font.BOLD, s);
		StdDraw.setPenColor(Color.white);
		return f;

	}
	
	@Override
	public boolean isDone() {
		return false;
	}

}