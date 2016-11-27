//
// RECORD.JAVA
// Record type for string hash table
//
// A record associates a certain string (the key value) with 
// a list of sequence positions at which that string occurs.
//

import java.util.*;

public class Record {
    public String key;
    public ArrayList<Integer> positions;
    public int hashKey;
    
    public Record(String s)
    {
	key = s;
	positions = new ArrayList<Integer>(1);
	hashKey = 0;
    }

	public String getKey() {
		return this.key;
	}

	public int getHashKey() {
		return hashKey;
	}

	public void setKey(String key) {
		this.key = key;
	}

	public void setPositions(ArrayList<Integer> positions) {
		this.positions = positions;
	}

	public void setHashKey(int hashKey) {
		this.hashKey = hashKey;
	}
	
	


	
    
}
