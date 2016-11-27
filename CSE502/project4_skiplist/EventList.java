//
// EVENTLIST.JAVA
// Skeleton code for your EventList collection type.
//
import java.util.*;

class EventList {

	Random randseq;
	ListNode head;
	ListNode tail;
	int highestLevelUsed;
	int highestLevel;

	////////////////////////////////////////////////////////////////////
	// Here's a suitable geometric random number generator for choosing
	// pillar heights.  We use Java's ability to generate random booleans
	// to simulate coin flips.
	////////////////////////////////////////////////////////////////////

	int randomHeight()
	{
		int v = 1;
		while (randseq.nextBoolean()) { v++; }
		return v;
	}


	//
	// Constructor
	//
	public EventList()
	{
		randseq = new Random(58243); // You may seed the PRNG however you like.
		// in the same constructor to initialize other instance variable
		Event first = new Event(Integer.MIN_VALUE,"head");
		Event last = new Event(Integer.MAX_VALUE,"tail");
		this.head = new ListNode(first);
		this.tail = new ListNode(last);
		this.head.next = this.tail;
		//this.tail.prev = this.head;
		this.highestLevelUsed = 1; // here the first level is given as 1, because of the doublesize method
		this.highestLevel = 1;
	}

	//
	// Add an Event to the list.
	//
	public void insert(Event e)
	{
		// already existing event have the same year
		if(find(e.year) != null){
			ListNode exist = find(e.year);
			while(exist.down != null){
				exist.events.add(e);
				exist = exist.down; 
			}
			exist.events.add(e);
			return;
		}

		//if not found, make a new ListNode and give it a height randomly
		int height = randomHeight();
		if(height > this.highestLevelUsed){
			this.highestLevelUsed = height;
			while(height > this.highestLevel){	
				this.doubleSize(height);
			}
		}
		ListNode insert = new ListNode(e);
		for(int i = 0; i < height; i++){
			insert = insert.addLevel();
		}
		ListNode current = head;
		int t = highestLevel-1;
		while(current.down != null){
			if(t < height){
				while(current.next.events.get(0).year < e.year){
					current = current.next;
				}
				ListNode nextOne = current.next;
				nextOne = insert; // I don't quite understand this statement, just got it by tuition
				insert.next = current.next.next;
				//				insert.prev = current;
				//				nextOne.prev = insert;
				insert = insert.down;
			}
			t--;
			current = current.down;
		}
		insert = insert.down;
		while(current.next.events.get(0).year < e.year){
			current = current.next;
		}
		ListNode nextOne = current.next;
		current.next = insert;
		//insert.prev = current;
		insert.next = nextOne;
		//nextOne.prev = insert;
	}


	//
	// Remove all Events in the list with the specified year.
	//
	public void remove(int year)
	{
		// below I comment out the previous version with prev pointers
		//		if(find(year) == null){
		//			return;
		//		}
		//		else{
		//			ListNode exist = find(year);
		//			while(exist.down != null){
		//				ListNode prevOne = exist.prev;
		//				ListNode nextOne = exist.next;
		//				prevOne.next = nextOne;
		//				nextOne.prev = prevOne;
		//				exist = exist.down;
		//			}
		//			ListNode prevOne = exist.prev;
		//			ListNode nextOne = exist.next;
		//			prevOne.next = nextOne;
		//			nextOne.prev = prevOne;
		//			exist = exist.down;	
		//     }
		
		
		ListNode current = this.head;
		int t = this.highestLevel - 1;
		while(t >= 0){
			ListNode nextOne = current.next;
			if(nextOne.events.get(0).year == year){
				current.next = nextOne.next;
				current = current.down;
				t--;
			}
			else if(nextOne.events.get(0).year < year){
				current = current.next;
			}
			else{
				current = current.down;
				t--;
			}
		}
	}

	//
	// Find all events with greatest year <= input year
	//
	public Event[] findMostRecent(int year){
		// if the node with the given year has already exist, just return that node's event
		if(find(year) != null){
			int size = find(year).events.size();
			Event[] mostRecent = new Event[size];
			for(int i = 0; i < size; i++){
				mostRecent[i] = find(year).events.get(i);
			}
			return mostRecent;
		}
		// if not exist find the node with event's year just smaller than the given year
		else{
			ListNode current = head;
			while(current.down != null){
				current = current.down;
			}
			if(current.next.events.get(0).year > year){
				return null;
			}
			while(current.next.events.get(0).year < year){
				current = current.next;
			}
			int size = current.events.size();
			Event[] mostRecent = new Event[size];
			for(int i = 0; i < size; i++){
				mostRecent[i] = current.events.get(i);
			}
			return mostRecent;
		}
	}

	//
	// Find all Events within the specific range of years (inclusive).
	//
	public Event [] findRange(int first, int last)
	{
		//if event with "first" has already exist, find that node start return events  
		//from that node until reach the node with "last" or just smaller than "last"
		ArrayList<Event> ans = new ArrayList<Event>();
		if(find(first) != null){
			ListNode exist = find(first);
			while(exist.events.get(0).year <= last){
				ans.addAll(exist.events);
				exist = exist.next;
			}
			int size = ans.size();
			Event[] range = new Event[size];
			for(int i = 0; i < size; i++){
				range[i] = ans.get(i);
			}
			return range;
		}
		// otherwise, find the just greater one 
		else{
			ListNode current = head;
			while(current.down != null){
				current = current.down;
			}
			while(current.events.get(0).year < first){
				current = current.next;
			}
			if(current!= tail){
				while(current.events.get(0).year <= last){
					ans.addAll(current.events);
					current = current.next;
				}
				int size = ans.size();
				Event[] range = new Event[size];
				for(int i = 0; i < size; i++){
					range[i] = ans.get(i);
				}
				return range;
			}
			else return null;
		}
	}

	// double size the highestLevel until it is greater than the given value
	public int doubleSize(int height){
		while(height >= this.highestLevel){
			int t = this.highestLevel;
			for(int i = 1; i <= t; i++){
				this.head = this.head.addLevel();
				this.tail = this.tail.addLevel();
				this.head.next = this.tail;
				//this.tail.prev = this.head;
				this.highestLevel++;
			}
		}

		return highestLevel;
	}

	// find method, find a particular year of an event;
	public ListNode find(int year){
		ListNode current = head;
		int t = this.highestLevel - 1;
		while(t >= 0){
			if(current.next.events.get(0).year == year){
				return current.next;
			}
			else if(current.next.events.get(0).year < year){
				current = current.next; 
			}
			else{
				t--;
				current = current.down;
			}
		}
		return null;
	}
}