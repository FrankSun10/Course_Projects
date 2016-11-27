package lab10;

public interface Food {
	
	public double getRadius();
	
	public void draw();
	
	//basic getters
	public double getX();
	public double getY();
	
	// food got eaten or not
	public boolean beenEaten(SlowBlob blob);

	// basic draw 
	public void basicDraw();
}
