#include "thread/ActivityScheduler.h"

void ActivityScheduler::start(Activity* act) {
	act->changeTo(Activity::RUNNING);   // Scheduler
	init((Coroutine*)act);               // Dispatcher
}

void ActivityScheduler::suspend() {
	Activity* activeProcess = (Activity*)this->active();  // Retrieves and stores the currently active process.
	activeProcess->changeTo(Activity::BLOCKED);
	reschedule();                                         // Delegate to the scheduler and transition to the next process from the ready list.
}

void ActivityScheduler::kill(Activity* act) {
	act->changeTo(Activity::ZOMBIE);                  // Set the state to 'ZOMBIE', marking the process as terminable.
	remove((Schedulable*)act);                       // Remove the process from the ready list.
	Activity* activeProcess = (Activity*)(this->active()); // Load a new process only if the active process is the one being killed.
	if (activeProcess->isRunning() && activeProcess == act) reschedule();
}

void ActivityScheduler::exit() {
	Activity* activeProcess = (Activity*)active();  // Retrieve and store the currently active process.
	kill(activeProcess);
	reschedule();                                   // Delegate to the scheduler and transition to the next process from the ready list.
}

void ActivityScheduler::activate(Schedulable* to) {
    // Retrieve the currently running process and prepare the next activity to be activated.
	Activity* currentProcess = (Activity*)(this->active());
	Activity* nextProcess = (Activity*)to;

    // If the current process is neither blocked nor a zombie and is running, then it can be returned to the ready list.
	if (
            (!(currentProcess->isBlocked()) &&
            currentProcess->isRunning()) &&
            (!(currentProcess->isZombie()))
            ) {
		currentProcess->changeTo(Activity::READY);
		Schedulable* tempSched = (Schedulable*)currentProcess;
		scheduler.schedule(tempSched);
	}

    // Continuously attempt to fetch an activity from the ready list if no next process is specified.
	while (nextProcess == 0) {
        // Ensure no active process is overwritten.
		if (!currentProcess->isRunning()) {
			nextProcess = (Activity*)(readylist.dequeue());
            // Note: It's possible that the process just added back to the ready list might be reselected if it is the only one.
		}
	}

    // The next process to be activated must exist. Change its state and pass control using dispatch.
	if (nextProcess != 0) {
		nextProcess->changeTo(Activity::RUNNING);
		dispatch(nextProcess);
	}
}