package lab10;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import sedgewick.StdDraw;

public class Slide {
	
	private Color color;
	
	public Slide(){
		this.color = genRandomColor();
	}
	
	/**
	 * this draw used to draw a reminder to prompt the player to go on
	 */
	public void clickFace(){
		String s = "~~Please Click~~";
		int oblique = 10;
		this.drawFace(s, oblique);
	}
	
	/**
	 * final slide
	 */
	public void gameFinished(){
		String s = "~~Game Completed~~";
		int oblique = 10;
		this.drawFace(s, oblique);
	}
	
	/**
	 * display the game over slide
	 */
	public void gameOver(){
		
		String s = "Game Over";
		int oblique = 5;
		this.drawFace(s, oblique);
	}
	
	/**
	 * the round 1 instruction
	 */
	public void contentRoundOne(){
		 
		String s1 = ">>> ROUND ONE: GROW  UPTO 200 IN TIME";
		String s2 = ">>> ROUND TWO:     << LOCKED >>               ";
		String s3 = ">>> ROUND TWO:     << LOCKED >>               ";
		this.content(s1, s2, s3);

	}
	/**
	 * round 2 instruction
	 */
	public void contentRoundTwo(){
	
		String s1 = ">>> ROUND ONE:       << PASSED >>                  ";
		String s2 = ">>> ROUND TWO: GROW  UPTO 200 IN TIME";
		String s3 = ">>> ROUND TWO:      << LOCKED >>                ";
		this.content(s1, s2, s3);
	}
	
	/**
	 * round 3 instruction
	 */
	public void contentRoundThree(){
		
		String s1 = ">>> ROUND ONE:       << PASSED >>                  ";
		String s2 = ">>> ROUND TWO:       << PASSED >>                  ";
		String s3 = ">>> ROUND TWO: GROW  UPTO 200 IN TIME";
		this.content(s1, s2, s3);
	}
	
	/**
	 * reminder the player that next gound is available, 
	 * if not respond after a certain time then game over
	 */
	public void nextRound(){
		FadingWigglingMessage nextRound = new FadingWigglingMessage(20, " Win ! ! !   Next Round ?", 10000, 0.005);
		boolean mousePressed = false;
		while(! nextRound.isDone() && !mousePressed){
			StdDraw.clear();
			nextRound.draw();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(20);
		}
		// wait for a certain time, if not click , game over
		while(! mousePressed){
			StdDraw.clear();
			this.gameOver();
			mousePressed = StdDraw.mousePressed();
			StdDraw.show(20);
		}
	}
	
	
	/**
	 *  draw method for the face use
	 */
	public void drawFace(String s, int oblique){
		StdDraw.setPenColor(this.color);
		StdDraw.filledCircle(0.5, 0.5, 0.35);
		StdDraw.setPenColor(Color.white);
		StdDraw.setFont();
		StdDraw.text(0.5, 0.485, "<<<<<<<<<~~oo", 270);
		Font f = new Font("serif", Font.BOLD, 22);
		StdDraw.setFont(f);
		StdDraw.text(0.55, 0.3, s, oblique);
		StdDraw.setPenRadius(0.005);
		StdDraw.filledEllipse(0.5015, 0.52, 0.02, 0.1);// this is the nose
		StdDraw.filledEllipse(0.65, 0.65, 0.08, 0.015);
		StdDraw.filledEllipse(0.35, 0.65, 0.08, 0.015);

		StdDraw.show(500);
	}
	
	/**
	 * put instruction during two round
	 * @param s1  instruction to round 1
	 * @param s2  instruction to round 2
	 * @param s3  instruction to round 3
	 */
	public void content(String s1, String s2, String s3){
		
		StdDraw.setPenColor(this.color);
		StdDraw.filledSquare(0.5, 0.5, 0.5);
		
		StdDraw.setPenColor(Color.white);
		Font f = new Font("serif", Font.BOLD, 20);
		StdDraw.setFont(f);
		StdDraw.text(0.1, 0.9, " A R G O R");
		StdDraw.text(0.5, 0.65, s1);
		StdDraw.text(0.5, 0.55, s2);
		StdDraw.text(0.5, 0.45, s3);
		StdDraw.text(0.9, 0.1, "C L I C K");
		
	}
	
	/**
	 * random color generator
	 * @return  a random color
	 */
	public Color genRandomColor(){
		Random r = new Random();
		int red = r.nextInt(256);
		int green = r.nextInt(256);
		int blue = r.nextInt(256);
		return new Color(red, green, blue);
	}

}
