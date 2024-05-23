#ifndef Queue_h
#define Queue_h
#include "lib/Chain.h"

/**
 * Queue class:
 * Implements a basic queue structure for managing elements in a FIFO (First-In, First-Out) order.
 * This class is designed to handle items of type Chain, making it suitable for linked list operations
 * where each element can be dynamically added or removed.
 */
class Queue {
public:
    /**
     * Constructor for the Queue.
     * Initializes the queue to an empty state with the head pointer set to nullptr and
     * the tail pointer set to point at the head, indicating an empty queue.
     */
	Queue () { head = 0; tail = &head; }

    /**
     * Adds an item to the end of the queue.
     * This method enqueues an item by adjusting the tail to point to the new item,
     * ensuring that items are kept in the order they are added.
     * @param item Pointer to the Chain item to be enqueued.
     */
	void enqueue(Chain* item);

    /**
     * Removes and returns the item at the front of the queue.
     * This method dequeues the front item, advancing the head to the next item in the queue.
     * If the queue becomes empty, it ensures the tail is reset correctly.
     * @return Pointer to the Chain item removed from the front of the queue.
     */
	Chain* dequeue();

    /**
     * Removes a specific item from the queue.
     * This method searches for and removes the specified item from the queue.
     * It handles the adjustment of pointers to maintain queue integrity.
     * @param item Pointer to the Chain item to be removed from the queue.
     */
	void remove(Chain* item);

    bool isEmpty() { return head == nullptr; }

private:
	Chain* head;    // Pointer to the first item in the queue.
	Chain** tail;   // Pointer to the last item's next pointer in the queue.
};

#endif
