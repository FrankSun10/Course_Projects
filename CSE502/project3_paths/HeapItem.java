
public class HeapItem<T>{
	
	
	// a heapItem or a node of a priority queue has-a key, 
	//    value of type T, and a reference of Handle
	
	int key;
	T value;
	Handle h;
	
	public HeapItem(int key, T value){
		
		this.key = key;
		this.value = value;
		// handle should be update according to a particular item
		Handle h = new Handle();
		this.h = h;
	}
	
}

