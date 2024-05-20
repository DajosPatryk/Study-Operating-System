#include "lib/Queue.h"

/**
 * Enqueues an item to the end of the queue.
 * @param item Pointer to the Chain item to be added to the queue.
 */
void Queue::enqueue (Chain* item) {
	item->next = 0; 
	*tail = item;    
	tail = &(item->next); 
}

/**
 * Dequeues an item from the front of the queue.
 * @return Pointer to the dequeued Chain item, or NULL if the queue was empty.
 */
Chain* Queue::dequeue () {
	Chain* item;

	item = head;   
	if (item) {
		head = item->next;

		if (!head) tail = &head;
		else item->next = 0;
	}

	return item;
}

/**
 * Removes a specific item from the queue.
 * @param item Pointer to the Chain item to be removed from the queue.
 */
void Queue::remove (Chain* item) {
	Chain* curr;

	if (head) {
		curr = head;

		if (item == curr) dequeue ();
		else {
			while (curr->next && item != curr->next) curr = curr->next;

			if (curr->next) {
				curr->next = item->next; 
				item->next = 0;      

				if (!curr->next) tail = &(curr->next);
			}
		}
	}
}

