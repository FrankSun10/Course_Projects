
import java.util.ArrayList;

//
// SHORTESTPATHS.JAVA
// Compute shortest paths in a graph.
//
// Your constructor should compute the actual shortest paths and
// maintain all the information needed to reconstruct them.  The
// returnPath() function should use this information to return the
// appropriate path of edge ID's from the start to the given end.
//
// Note that the start and end ID's should be mapped to vertices using
// the graph's get() function.
//
// You can ignore the input and startTime arguments to the constructor
// unless you are doing the extra credit.
//
class ShortestPaths {
	
	Multigraph G;  // record the given parameter of Multigraph
	int startId; // record the given parameter of startId, to use in returnPath method
	Vertex[] parent; // record each vertex's parent
	int[] edge; // record the edge between each vertex and its parent
	int startTime;
	Input input;
    //
    // constructor, 
    //
    public ShortestPaths(Multigraph G, int startId, 
			 Input input, int startTime) 
    {
    	this.G = G;
    	this.startId = startId;
    	this.parent = new Vertex[this.G.nVertices()];
    	this.edge = new int[this.G.nVertices()];
    	this.startTime = startTime;
    	this.input = input;
    	
    	if(this.startTime == 0){
    		this.nonLayover();	
    	}
    	else{
    		this.layover();
    	}
    }
         
    //
    // returnPath()
    // Return an array containing a list of edge ID's forming
    // a shortest path from the start vertex to the specified
    // end vertex.
    //
    public int [] returnPath(int endId) 
    { 
    	// if the endId is the same as the startId, return zero
    	if(this.startId == endId){
    		return new int[0];
    	}
    	// otherwise return a path
    	Vertex end = this.G.get(endId);
    	ArrayList<Integer> edge = new ArrayList<Integer>();
    	int temp = endId;
    	while(temp != this.startId){
    		edge.add(this.edge[temp]);
    		temp = this.parent[temp].id();
    	}
    	// reversely put the edge into path
    	int[] path = new int[edge.size()];
    	int i = 0;
    	for(int j = edge.size() -1; j >= 0; j--){
    		path[i] = edge.get(j);
    		i++;
    	}
    	return path;
    }
    
    
    /**
     * this method is used for non-layover-aware model
     */
    public void nonLayover(){
    	
    	int[] distance = new int[this.G.nVertices()];
    	Handle[] handle = new Handle[this.G.nVertices()];
    	PriorityQueue<Vertex> queue = new PriorityQueue<Vertex>();
    	// initialize every vertex
    	for(int i = 0; i < this.G.nVertices(); i++){
    		Vertex u = this.G.get(i);
    		distance[u.id()] = Integer.MAX_VALUE;
    		this.parent[u.id()] = null;
    		handle[u.id()] = queue.insert(Integer.MAX_VALUE, u);
    		
    	}
    	// initialize the start vertex
    	Vertex s = this.G.get(this.startId);
    	distance[s.id()] = 0;
    	queue.decreaseKey(handle[s.id()], 0);
    	// update every adjacent vertex
    	while(!queue.isEmpty()){
    		Vertex u = queue.extractMin();
    		// check if u is connected with other vertex
    		if(distance[u.id()] == Integer.MAX_VALUE){
    			return;
    		}
    		Vertex.EdgeIterator ir = u.adj();
    		while(ir.hasNext()){
    			Edge e = ir.next();
    			Vertex v = e.to();
    			if(queue.decreaseKey(handle[v.id()], distance[u.id()] + e.weight())){
    				distance[v.id()] = distance[u.id()] + e.weight();
    				this.parent[v.id()] = u;
    				this.edge[v.id()] = e.id(); 
    			}
    		}    		
    	}
    }
    
    /**
     * this mehod is used for layover model
     */
    public void layover(){
    	
    	// for every vertex, the traveler will arrive at it at a particular time
    	// for the start vetex, it is the startTime given in the constructor, 
    	// for every other vertex, it is the prior flight's arrival time
    	int[] startTime = new int[this.G.nVertices()];
    	int[] distance = new int[this.G.nVertices()];
    	Handle[] handle = new Handle[this.G.nVertices()];
    	PriorityQueue<Vertex> queue = new PriorityQueue<Vertex>();
    	//initialize every vertex in the graph
    	for(int i = 0; i < this.G.nVertices(); i++){
    		Vertex u = this.G.get(i);
    		distance[u.id()] = Integer.MAX_VALUE;
    		this.parent[u.id()] = null;
    		handle[u.id()] = queue.insert(Integer.MAX_VALUE, u);
    		startTime[u.id()] = Integer.MAX_VALUE;
    	}
    	// initialize the start vertex
    	Vertex s = this.G.get(this.startId);
    	distance[s.id()] = 0;
    	queue.decreaseKey(handle[s.id()], 0);
    	startTime[s.id()] = this.startTime;
    	// update the adjacent vertex 
    	while(!queue.isEmpty()){
    		Vertex u = queue.extractMin();
    		// check if u is connect with other vertices
    		if(distance[u.id()] == Integer.MAX_VALUE){
    			return;
    		}
    		
    		Vertex.EdgeIterator ir = u.adj();
    		while(ir.hasNext()){
    			Edge e = ir.next();
    			// get the departure time from u to v
    			int departureTime = this.input.flights[e.id()].startTime; 
    			int layoverTime = layoverTime(startTime[u.id()], departureTime);
    			Vertex v = e.to();
    			if(queue.decreaseKey(handle[v.id()], distance[u.id()] + layoverTime + e.weight())){
    				distance[v.id()] = distance[u.id()] + layoverTime + e.weight();
    				startTime[v.id()] = this.input.flights[e.id()].endTime;
    				this.parent[v.id()] = u;
    				this.edge[v.id()] = e.id();
    			}
    		}
    	}
    }
    
    /**
     * calculate the lay over time at an airport
     * @param arrivalTime  when arrive at the airport(vertex)
     * @param departureTime when a flight starting from the airport departure
     * @return
     */
    public int layoverTime(int startTime, int departureTime){
    	int u = 45;
    	int layoverTime = u + (departureTime - startTime - u + 2880) % 1440;
    	return layoverTime;
    }
    
    
}

