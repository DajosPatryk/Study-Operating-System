#include "thread/Scheduler.h"

void Scheduler::schedule(Schedulable* sched) {
	Chain* tempSched = (Chain*)sched;
	readylist.enqueue(tempSched);
}

void Scheduler::remove(Schedulable* sched) {
	Chain* tempSched = (Chain*)sched;
	readylist.remove(tempSched);
}

void Scheduler::reschedule() {
	Schedulable* headSched = (Schedulable*)readylist.dequeue();
	this->activate(headSched);
}