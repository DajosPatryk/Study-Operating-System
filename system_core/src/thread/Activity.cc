#include "thread/Activity.h"
#include "interrupts/IntLock.h"
#include "thread/ActivityScheduler.h"

#include "device/CPU.h"
extern CPU cpu;

// Initial state is blocked so thread doesn't immediately run.
Activity::Activity(void* tos) : Coroutine(tos){
	this->state=BLOCKED;
}

Activity::Activity() : Coroutine() {
	this->state = RUNNING;
	scheduler.start(this);  // Initializes first activity.
}

Activity::~Activity() {
	scheduler.kill(this);   // Terminates activity.
}

void Activity::sleep() { scheduler.suspend(); }

void Activity::wakeup() {
	IntLock lock;
	if (isBlocked()) {
		this->state = READY;
		scheduler.schedule(this);
	}
}

void Activity::yield() { this->state = READY;scheduler.reschedule(); }

void Activity::exit() {
	IntLock lock;
	// Wakes-up next joined activities.
	if (joined != nullptr) {
		joined->wakeup();
		joined = nullptr;
	}

	scheduler.exit();   // Terminates current activities.
}

void Activity::join() {
	IntLock lock;
    // Retrieves and stores the currently active process from the scheduler's ready list.
	Activity* activeProcess = (Activity*)scheduler.running;

    // Check if the caller is not a zombie and is not attempting to join itself.
    // If conditions are met, link this activity to the currently running process and suspend it.
	if (!(this->isZombie()) || this == activeProcess) {
		this->joined = activeProcess;
		activeProcess->sleep();
	}
}