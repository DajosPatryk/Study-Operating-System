#include "thread/Scheduler.h"

	// cast von Schedulable* zu Chain* noetig um mit
    //Queue Methoden zu arbieten

void Scheduler::schedule(Schedulable* sched)
{
	Chain* tempSched = (Chain*)sched;
	readylist.enqueue(tempSched);
}

void Scheduler::remove(Schedulable* sched)
{
	Chain* tempSched = (Chain*)sched;
	readylist.remove(tempSched);
}

void Scheduler::reschedule()
{
	Schedulable* headSched = (Schedulable*)readylist.dequeue();
	this->activate(headSched);
}