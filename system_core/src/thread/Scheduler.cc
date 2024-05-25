#include "thread/Scheduler.h"
#include "interrupts/IntLock.h"
#include "../include/thread/Activity.h"

#include "thread/ActivityScheduler.h"

extern ActivityScheduler scheduler;

//manipulating ReadyList is critical and no other process can interrupt while manipulating it-->IntLocks needed

void Scheduler::schedule(Schedulable* sched) {
	IntLock lock;
	readylist.enqueue(sched);
}

void Scheduler::remove(Schedulable* sched) {
	IntLock lock;
	readylist.remove(sched);
}

void Scheduler::reschedule() {
	IntLock lock;
	activate((Schedulable *)readylist.dequeue());
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