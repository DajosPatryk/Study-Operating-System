#include "thread/Scheduler.h"
#include "interrupts/IntLock.h"
#include "../include/thread/Activity.h"

#include "thread/ActivityScheduler.h"

extern ActivityScheduler scheduler;

void Scheduler::schedule(Schedulable* sched) {
	IntLock lock;
	Chain* tempSched = (Chain*)sched;
	readylist.enqueue(tempSched);
}

void Scheduler::remove(Schedulable* sched) {
	IntLock lock;
	Chain* tempSched = (Chain*)sched;
	readylist.remove(tempSched);
}

void Scheduler::reschedule() {
	IntLock lock;
	Schedulable* headSched = (Schedulable*)readylist.dequeue();
	this->activate(headSched);
}

void Scheduler::checkSlice()
{
	IntLock lock;
	Activity *current = (Activity *)scheduler.running;
	if (current->currentCount < current->slice)
	{
		current->currentCount++;
		return;
	}
	else
	{
		current->currentCount = 0;
		scheduler.reschedule();
	}
}