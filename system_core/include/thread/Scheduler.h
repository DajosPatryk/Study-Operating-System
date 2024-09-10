#ifndef Scheduler_h
#define Scheduler_h
#include "lib/Queue.h"
#include "thread/Schedulable.h"

/**
 * Scheduler class:
 * Manages the scheduling of tasks in a multitasking environment. This class is responsible
 * for adding, removing, and selecting tasks for execution from a ready list, ensuring tasks
 * are managed efficiently according to scheduling algorithms.
 *
 * The Scheduler uses a queue (implemented in the Queue class) to manage the list of tasks
 * that are ready to be executed. Tasks in this context are represented by instances of the
 * Schedulable class, which allows them to be enqueued and dequeued in a linked-list manner.
 */
class Scheduler {
public:
    /**
     * Schedules a new task by adding it to the ready list.
     * This method enqueues a Schedulable task to the readylist, making it available for execution.
     * @param sched Pointer to the Schedulable task to be scheduled.
     */
	void schedule(Schedulable* sched);

    /**
     * Removes a task from the ready list.
     * This method is called to dequeue a specific Schedulable task from the readylist,
     * typically when the task is completed or needs to be suspended.
     * @param sched Pointer to the Schedulable task to be removed.
     */
	void remove(Schedulable* sched);

    /**
     * Reschedules tasks by selecting the next task to run.
     * This method is responsible for managing task transitions, dequeuing the next task
     * from the ready list and invoking activate to switch execution to it.
     */
	void reschedule();

    bool isQueueEmpty(){ return readylist.isEmpty(); }

    /**
     * Pruft ob das Zeitscheibe der gerade untebrochene Prozess abgelaufen ist
     * wenn ja fuhrt ein Prozzeswechsel, sonsts lass Prozess weiter laufen
     */
	void checkSlice();

    /**
     * Pure virtual function to activate a task.
     * This function must be implemented by derived classes to define how a task is activated
     * or switched to. This could involve context switching mechanisms or simply marking the
     * task as currently running.
     * @param to Pointer to the Schedulable task that is to be activated.
     */
	virtual void activate(Schedulable* to) = 0;

	Queue readylist;    // Queue used to manage the list of ready tasks.

};

#endif
