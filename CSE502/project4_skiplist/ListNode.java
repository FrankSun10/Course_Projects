import java.util.ArrayList;

public class ListNode {

	ArrayList<Event> events;
	ListNode next;
	ListNode down;
	//ListNode prev;


	public ListNode(Event event) {
		this.events = new ArrayList<Event>();
		this.events.add(event);
		this.next = null;
	//	this.prev = null;
		this.down = null;
	}
	
	// build a method to add a new level upward
	public ListNode addLevel(){
		ListNode upper = new ListNode(events.get(0));
		upper.down = this;
		upper.next = null;
	//	upper.prev = null;
		return upper;
	}
}