#ifndef Activity_h
#define Activity_h
#include "thread/Schedulable.h"
#include "thread/Coroutine.h"

/**
 * Activity class that extends Schedulable and Coroutine to implement task management
 * in a cooperative multitasking environment. It handles the lifecycle and state management
 * of processes/tasks.
 */
class Activity: public Schedulable, public Coroutine {
public:
	enum State {
		BLOCKED,    // Processes waiting on a resource or condition.
		READY,      // Processes that can be activated.
		RUNNING,    // The current active process.
		ZOMBIE      // Terminated child processes that outlive their parent.
	};

    /**
     * Explicit constructor for initializing an Activity with a specific stack pointer.
     * This constructor sets up the initial stack context for the coroutine.
     * @param tos Pointer to the top of stack space allocated for this coroutine.
     */
	explicit Activity(void* tos);

    /**
     * Default constructor for Activity, initializes state to BLOCKED.
     */
	Activity();

    /**
     * Virtual destructor for cleaning up resources or performing specific actions
     * when an Activity is destroyed, such as removing from scheduler if needed.
     */
	virtual ~Activity();

    /**
     * Puts the current process into a sleep state, effectively marking it as BLOCKED.
     */
	void sleep();

    /**
     * Wakes up the activity if it is blocked, changing its state to READY.
     */
	void wakeup();

    /**
     * Yields the CPU by allowing the scheduler to select another process to run.
     * The current process state is set to READY.
     */
	void yield();

    /**
     * Terminates the current activity and removes it from the scheduler.
     */
	void exit();

    /**
     * Allows one activity to wait for the completion of another. If the other activity is
     * not finished, the current activity is suspended.
     */
	void join();

    /**
     * Changes the current state of the activity to the specified state.
     * @param state The new state for this activity.
     */
	void changeTo(State state) {
		this->state = state; 
	}

    /**
     * Checks if the activity is in a BLOCKED state.
     * @return true if the activity is BLOCKED, false otherwise.
     */
	bool isBlocked() { return this->state == BLOCKED; }

    /**
     * Checks if the activity is in a READY state.
     * @return true if the activity is READY, false otherwise.
     */
	bool isReady() { return this->state == READY; }

    /**
     * Checks if the activity is in a RUNNING state.
     * @return true if the activity is RUNNING, false otherwise.
     */
	bool isRunning() { return this->state == RUNNING; }

    /**
     * Checks if the activity is in a ZOMBIE state.
     * @return true if the activity is ZOMBIE, false otherwise.
     */
	bool isZombie() { return this->state == ZOMBIE; }

    /**
     * Overloaded delete operator to handle specific deallocation needs for activities,
     * possibly to prevent deletion or manage memory pools.
     * @param p Pointer to the activity object to be deleted.
     */
    static void operator delete(void* p) {}

    /**
     * Gets the activity that this one is joined with (waiting on).
     * @return Pointer to the joined activity.
     */
	Activity* getJoined() { return this->joined; }

    /**
     * Sets the activity that this one is joined with (waiting on).
     * @param activity Pointer to the activity to join with.
     */
	void setJoined(Activity* activity) { this->joined = activity; }

private:
State state;        // Current state of the activity.
Activity* joined;   // Pointer to another activity that this one may be waiting on.

};

#endif
