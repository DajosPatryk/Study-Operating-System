#ifndef Dispatcher_h
#define Dispatcher_h
#include "thread/Coroutine.h"

/**
 * Dispatcher class manages the currently running coroutine in a multitasking environment.
 * This class is responsible for switching the active coroutine and maintaining a reference
 * to the currently active coroutine.
 */
class Dispatcher {
public:
    /**
     * Default constructor that initializes the dispatcher with no currently active coroutine.
     */
	Dispatcher() { running = 0; }

    /**
     * Initializes the dispatcher with the first active coroutine.
     * This method sets the provided coroutine as the currently active one.
     * Typically called at system startup to begin coroutine execution.
     * @param act Pointer to the coroutine to be set as the initial active coroutine.
     */
	void init(Coroutine* act) { running = act; }

    /**
     * Returns the currently active coroutine.
     * This function allows other components of the system to access the currently active coroutine.
     * @return Pointer to the currently active coroutine.
     */
	Coroutine* active() { return running; }

    /**
     * Dispatches to a new coroutine, switching the context from the current coroutine to the next.
     * This method updates the running pointer and invokes the resume method on the current coroutine
     * to switch to the next coroutine. It ensures the current coroutine's state is saved and the next
     * coroutine's state is restored.
     * @param next Pointer to the coroutine that will become the new active coroutine.
     */
	void dispatch(Coroutine* next) {
		Coroutine* curr = running;
		running = next;
		curr->resume(next);
	}

protected:
	Coroutine* running; // Pointer to the currently active coroutine.

};

#endif
