public class ClosestPairNaive {
    
    public final static double INF = java.lang.Double.POSITIVE_INFINITY;
    
    //
    // findClosestPair()
    //
    // Given a collection of nPoints points, find and ***print***
    //  * the closest pair of points
    //  * the distance between them
    // in the form "NAIVE (x1, y1) (x2, y2) distance"
    //
    
    // INPUTS:
    //  - points sorted in nondecreasing order by X coordinate
    //  - points sorted in nondecreasing order by Y coordinate
    //
    
    public static void findClosestPair(XYPoint points[], boolean print)
    {
    	double minDist = Double.POSITIVE_INFINITY;
		double dist;
		int j = 0;
		int k =0;
		int n1 =0;
		int n2 =0;
		while ( j <= points.length - 2){		
			k = j + 1;
			while(k <= points.length - 1){
				dist = Math.sqrt(Math.pow(points[k].x - points[j].x, 2) +
						Math.pow(points[k].y - points[j].y, 2));
				if (dist < minDist){
					minDist = dist;	
					n1 = k;
					n2 = j;
				}
				k += 1;
			}
			j += 1;
		}
		if (print)
		System.out.println("NAIVE " + points[n1] + " " + points[n2] + " " + minDist);
    }
}
