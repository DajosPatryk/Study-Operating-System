#ifndef ActivityScheduler_h
#define ActivityScheduler_h
#include "lib/Queue.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"
#include "thread/Scheduler.h"

/**
 * ActivityScheduler class that extends both Dispatcher and Scheduler to integrate task
 * scheduling with the dispatch mechanism. This class manages the lifecycle and execution
 * state of activities, coordinating when they run, suspend, or terminate.
 */
class ActivityScheduler: public Dispatcher, public Scheduler {
public:
    /**
     * Default constructor for ActivityScheduler.
     * Initializes a new instance of the ActivityScheduler.
     */
	ActivityScheduler() {
	}

    /**
     * Starts the execution of an activity. This method sets the activity's state to RUNNING,
     * and uses the Dispatcher to make it the currently active process.
     * @param act Pointer to the Activity to be started.
     */
	void start(Activity* act);

    /**
     * Suspends the currently active activity, changing its state to BLOCKED and scheduling
     * another activity to run. Uses the Scheduler's reschedule method to find and activate
     * the next available activity.
     */
	void suspend();

    /**
     * Terminates a specified activity, setting its state to ZOMBIE and removing it from the
     * scheduling queue. If the activity being killed is the current one, it triggers a
     * rescheduling to activate another activity.
     * @param act Pointer to the Activity to be terminated.
     */
	void kill(Activity*);

    /**
     * Exits the currently active activity, effectively calling `kill` on it and then
     * rescheduling to continue with another activity.
     */
	void exit();

protected:
    /**
     * Activates a new activity to run. This method is called by the Scheduler's rescheduling
     * mechanism and uses the Dispatcher's dispatch method to switch the context to the new
     * activity. This is a virtual method, allowing for customization in derived classes.
     * @param to Pointer to the Schedulable (activity) to be activated.
     */
	virtual void activate(Schedulable* to);

};

/**
 * Global instance of ActivityScheduler.
 * Provides a system-wide accessible scheduler that can be used to manage all activities.
 */
extern ActivityScheduler scheduler;

#endif
