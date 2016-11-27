package lab10;

import java.util.Random;

import sedgewick.StdDraw;

//
//   WigglyBlob "is a" Blob (plus more behavior, in this case,
//     wiggling part)
//
public class WigglyBlob extends Blob implements Anim {

	private double wiggle;

	public WigglyBlob(double radius) {
		super(radius);
		this.wiggle = radius / 6;
	}

	private double randomNoise(double min, double max) {
		double range = max - min;
		double r = Math.random();
		return min + r * range;
	}
	@Override
	public void draw() {
		super.draw();   // calls Blob's draw first
		for (int i=0; i < 4; ++i) {
			if (Math.random() < 0.5)
				drawBlob(x+randomNoise(-wiggle, wiggle), y + randomNoise(-wiggle, wiggle));
		}

	}

	protected void drawBlob(double x, double y) {
		StdDraw.setPenColor(color);
		StdDraw.filledCircle(x, y, radius);
	}

}
