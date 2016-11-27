package lab10;

public interface Guard {
	
	// the guard can eat Blob, then size change
	public void setRadius(SlowBlob blob);
	
	// get the guard's radius
	public double getRadius();
	
	// get the guard's x and y coordinate
	public double getX();
	public double getY();
	
	// to see if it is a guard, because object MovingBall acts as guard
	public void setGuard(boolean guard);
	
	// to see if guard is eaten by blob
	public boolean beenEaten(SlowBlob b);
	
	// draw the guard
	public void draw();

}
