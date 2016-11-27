public class ClosestPairDC {   
	public final static double INF = java.lang.Double.POSITIVE_INFINITY;

	//
	// findClosestPair()
	//
	// Given a collection of nPoints points, find and ***print***
	//  * the closest pair of points
	//  * the distance between them
	// in the form "DC (x1, y1) (x2, y2) distance"
	//

	// INPUTS:
	//  - points sorted in nondecreasing order by X coordinate
	//  - points sorted in nondecreasing order by Y coordinate
	//
	static double minDist = INF;
	static XYPoint [] closestPoints = new XYPoint[2];

	public static void findClosestPair(XYPoint pointsByX[], 
			XYPoint pointsByY[],
			boolean print)
	{
		int nPoints = pointsByX.length;
		closestPoints = closestPair( pointsByX, pointsByY, nPoints );
		double minDist = closestPoints[0].dist( closestPoints[1] );
		if(print)
			System.out.println("DC " + closestPoints[0] + " " + closestPoints[1] + " " + minDist);

	}
	public static XYPoint[] closestPair( XYPoint pointsByX[], XYPoint pointsByY[], int nPoints ){
		if(nPoints == 1){
			closestPoints[0] = pointsByX[0];
			closestPoints[1] = new XYPoint( (int)INF, (int)INF );
		}
		if(nPoints == 2){
			closestPoints[0] = pointsByX[0];
			closestPoints[1] = pointsByX[1];
			minDist = closestPoints[0].dist( closestPoints[1] );
		}
		if (nPoints > 2){
			int mid = (int)Math.ceil((double)nPoints/2) - 1;
			XYPoint[] XL = new XYPoint[mid + 1];
			XYPoint[] XR = new XYPoint[nPoints - mid -1];
			XYPoint[] YL = new XYPoint[mid + 1];
			XYPoint[] YR = new XYPoint[nPoints - mid -1];

			//copy pointsByX and  to XL and XR
			for(int i = 0; i < mid+1; i++){
				XL[i] = pointsByX[i];
			}
			for(int i = mid + 1; i < nPoints; i++){
				XR[i-mid-1] = pointsByX[i];
			}

			//copy pointsByY to YL and YR
			int yLLength = 0;
			int yRLength = 0;
			for(int i = 0; i < nPoints; i++){
				
				if((pointsByY[i].isLeftOf(pointsByX[mid])) || pointsByY[i] == XL[mid]){
					YL[yLLength] = pointsByY[i];
					yLLength += 1;
				}
				else{
					YR[yRLength] = pointsByY[i];
					yRLength += 1;
				}
			}

			//find the closest pairs in XL and XR
			XYPoint[] closestL = new XYPoint[2];
			XYPoint[] closestR = new XYPoint[2];
			
			closestL = closestPair(XL, YL, XL.length);
			closestR = closestPair(XR, YR, XR.length);

			double distL = closestL[0].dist(closestL[1]);
			double distR = closestR[0].dist(closestR[1]);
			if( distL < distR ){
				minDist = distL;
				closestPoints = closestL;
			}
			else{
				minDist = distR;
				closestPoints = closestR;
			}
			
			// From here the next combine method is called, to give the closest pairs in the 
			//combined area and the distance between them.
			XYPoint[] combineArea = new XYPoint[2];
			combineArea = combine(pointsByY, pointsByX[mid]);
			return combineArea;
		}
		
		return closestPoints;
	}
	//construct an array yStrip which can contains every points that fall into the combined area.
	//Also, yStrip is sorted in increasing y order.
	//First determine the length of yStrip. Then find the points in yStrip. Last, find the closest points
	// in yStrip and the distance between them.

	public static XYPoint[] combine( XYPoint pointsByY[], XYPoint midPointValue ){
		XYPoint [] closestPairsCombineArea = closestPoints;
		int yStripLength = 0;
		int ylength = pointsByY.length;

		//how big does yStrip need to be?
		for( int i = 0; i <= ylength - 1; i++ ){
			if( Math.abs( midPointValue.x - pointsByY[i].x ) <= minDist ){
				yStripLength++;
			}
		}
		XYPoint yStrip [] = new XYPoint[yStripLength];

		// fill up our yStrip
		int r = 0;
		while( yStripLength > 0){
			if( Math.abs( midPointValue.x - pointsByY[r].x ) <= minDist && yStripLength > 0 ){
				yStrip[yStrip.length - yStripLength] = pointsByY[r];
				yStripLength--;
			}
			r++;
		}

		//build a new closest pairs in the combined area and return it.
				// determine the shortest distance in combined area		
				for(int i = 0; i < yStrip.length - 1 ; i++){
					for(int k = i + 1; k < yStrip.length; k++){
						double distCombineArea = yStrip[k].dist(yStrip[i]);
						if(Math.abs(yStrip[k].y - yStrip[i].y) <= minDist){
							if(distCombineArea < minDist){
								minDist = distCombineArea;
								closestPairsCombineArea[0] = yStrip[i];
								closestPairsCombineArea[1] = yStrip[k];
							}
						}
					}
					
				}
		return closestPairsCombineArea;
		// Then combine the divided two parts and the combined area to find the final 
		//closest pairs and the distance between them.
		//So this method should be called before.
	}
}
