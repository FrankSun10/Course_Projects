package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import sedgewick.StdDraw;

public class FadingWigglingMessage implements Anim {

	final private int stopAt;
	private int numtimes;
	final private String message;
	final private Color color;
	private double x, y;
	final private double wiggle;

	/**
	 * 
	 * @param showPauseTime time between calls to draw() in msecs
	 * @param message the message to be displayed
	 * @param msecs the time duration for the fading, wiggling message
	 * @param wiggle the amount of wiggle
	 */
	public FadingWigglingMessage(int showPauseTime, String message, int msecs, double wiggle) {
		this.stopAt = msecs / showPauseTime;
		this.numtimes = 0;
		this.message = message;
		this.color = genRandomColor();
		this.x = 0.5;
		this.y = 0.5;
		this.wiggle = wiggle;
	}
	
	/**
	 * Establish the current location for this message
	 * @param x
	 * @param y
	 */
	public void setSpot(double x, double y) {
		this.x = x;
		this.y = y;
	}

	@Override
	public boolean isDone() {
		return numtimes >= stopAt;
	}

	@Override
	public void draw() {

		if (!isDone()) {

			int red   = color.getRed();
			int green = color.getGreen();
			int blue  = color.getBlue();


			int transp = 255 - (int) ((1.0 * numtimes / stopAt)*255);
			Color fader = new Color(red, green, blue, transp);
			StdDraw.setPenColor(fader);
			StdDraw.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 28));
			StdDraw.text(x, y, message);
			x = x + randomNoise(-wiggle, wiggle);
			y = y + randomNoise(-wiggle, wiggle);
			++numtimes;
		}
	}

	private double randomNoise(double min, double max) {
		double range = max - min;
		double r = Math.random();
		return min + r * range;
	}

	public Color genRandomColor(){
		Random r = new Random();
		int red = r.nextInt(256);
		int green = r.nextInt(256);
		int blue = r.nextInt(256);
		return new Color(red, green, blue);
	}
	
	
	
	
	
	
	
	
	
	
	
	
}
