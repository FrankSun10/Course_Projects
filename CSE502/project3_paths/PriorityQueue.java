
import java.util.ArrayList;

//
// PRIORITYQUEUE.JAVA
// A priority queue class supporting sundry operations needed for
// Dijkstra's algorithm.
//

class PriorityQueue<T> {

	ArrayList<HeapItem<T>> heap;
	int pqSize;
	
	
	// constructor
	//
	public PriorityQueue()
	{
		this.heap = new ArrayList<HeapItem<T>>();
		this.pqSize = 0;

	}

	// Return true iff the queue is empty.
	//
	public boolean isEmpty()
	{
		if(this.pqSize == 0) return true;
		else return false;
	}

	// Insert a pair (key, value) into the queue, and return
	// a Handle to this pair so that we can find it later in
	// constant time.
	//
	Handle insert(int key, T value)
	{
		//insert a heapItem with the given key and value
		this.heap.add(new HeapItem<T>(key,value));
		this.pqSize++;
		// update the heapItem's handle 
		this.heap.get(this.pqSize-1).h.ref = this.pqSize -1;
		// bubble up to fix the queue
		int child = this.pqSize - 1;
		int parent = (child-1) / 2;
		while(parent >= 0){
			if(this.heap.get(child).key < this.heap.get(parent).key){
				swap(this.heap.get(child), this.heap.get(parent));
				child = parent;
				parent = (parent-1) / 2;
			}
			else parent = -1;
		}
		return this.heap.get(child).h;
	}


	// Return the smallest key in the queue.
	//
	public int min()
	{
		if(this.heap.isEmpty()){
			return Integer.MAX_VALUE;
		}
		return this.heap.get(0).key;
	}

	// Extract the (key, value) pair associated with the smallest
	// key in the queue and return its "value" object.
	//
	public T extractMin()
	{
		if(this.isEmpty()){
			return null;
		}
		T extract = this.heap.get(0).value;
		swap(this.heap.get(this.pqSize - 1), this.heap.get(0));
		this.heap.get(this.pqSize - 1).h.ref = -1;
		this.heap.remove(this.pqSize - 1);
		this.pqSize--;
		// with heapify method to fix up the queue
		heapify(0);
		return extract;
	}


	// Look at the (key, value) pair referenced by Handle h.
	// If that pair is no longer in the queue, or its key
	// is <= newkey, do nothing and return false.  Otherwise,
	// replace "key" by "newkey", fixup the queue, and return
	// true.
	//
	public boolean decreaseKey(Handle h, int newkey)
	{
		// no more in the queue
		if(h.ref == -1 || h.ref > this.heap.size()){
			return false;
		}
		// new key is bigger
		else if(this.heap.get(h.ref).key <= newkey){
			return false;
		}
		//otherwise
		else{
			this.heap.get(h.ref).key = newkey; 
			// bubble up to fix up the queue
			int current = h.ref;
			int parent = (current-1) / 2;
			while(parent >= 0){
				if(this.heap.get(current).key < this.heap.get(parent).key){
					swap(this.heap.get(current), this.heap.get(parent));
					current = parent;
					parent = (parent-1) / 2;
				}
				else parent = -1;
			}
			return true;
		}
	}

	// Get the key of the (key, value) pair associated with a 
	// given Handle. (This result is undefined if the handle no longer
	// refers to a pair in the queue.)
	//
	public int handleGetKey(Handle h)
	{
		return this.heap.get(h.ref).key;
	}

	// Get the value object of the (key, value) pair associated with a 
	// given Handle. (This result is undefined if the handle no longer
	// refers to a pair in the queue.)
	//
	public T handleGetValue(Handle h)
	{
		if(h.ref == -1){
			return null;
		}
		return this.heap.get(h.ref).value;
	}


	// Print every element of the queue in the order in which it appears
	// in the implementation (i.e. the array representing the heap).
	public String toString()
	{
		String s = "";
		for(int i = 0; i <= this.pqSize - 1; i++){
			s = s + "(" + this.heap.get(i).key + ", " + this.heap.get(i).value +")" + "\n" ;
		}
		return s;
	}

	/**
	 *  heapify method, bubble down to fix up the queue
	 * @param i the starting location to bubble down
	 */
	public void heapify( int i){
		// if i has left child
		if(i*2+1 <= this.pqSize-1){
			int smallest;
			// if i has right child
			if(2*i + 2 <= this.pqSize - 1 && heap.get(2*i+2).key < heap.get(2*i + 1).key){
				smallest = 2*i + 2;
			}
			else{
				smallest = 2*i + 1;
			}
			if(heap.get(smallest).key < heap.get(i).key){
				swap(heap.get(smallest), heap.get(i));
				heapify(smallest);
			}
		}
	}

	/**
	 * swap two heapItem in the queue, including handle 
	 * @param child
	 * @param parent
	 */
 	public void swap(HeapItem<T> child, HeapItem<T> parent){
		int temp = child.h.ref;
		child.h.ref = parent.h.ref;
		heap.set(child.h.ref, child);
		parent.h.ref = temp;
		heap.set(parent.h.ref, parent);
	}

 	/**
 	 * firstly I use this swap method, it does not work, I still cannot figure out the problem
 	 * @param child
 	 * @param parent
 	 */
 	//	public void swap (HeapItem<T> child, HeapItem<T> parent){
 	//		Handle temp = child.h;
 	//		child.h = parent.h;
 	//		heap.set(child.h.ref, child);
 	//		parent.h = temp;
 	//		heap.set(parent.h.ref, parent);
 	//		
 	//	}
}
