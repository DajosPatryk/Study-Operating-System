#include "thread/Scheduler.h"
#include "interrupts/IntLock.h"
#include "thread/Activity.h"

#include "thread/ActivityScheduler.h"

extern ActivityScheduler scheduler;

//manipulating ReadyList is critical and no other process can interrupt while manipulating it-->IntLocks needed
//with Monitor synchronisation safe through it --> intlocks weg

void Scheduler::schedule(Schedulable* sched) {
	
	readylist.enqueue(sched);
}

void Scheduler::remove(Schedulable* sched) {
	
	readylist.remove(sched);
}

void Scheduler::reschedule() {
	
	activate((Schedulable *)readylist.dequeue());
}

void Scheduler::checkSlice()
{

	//hier gelangen durch clock interrupt, prufen bo gerade laufende Prozess
	//weiter laufen kann wenn ihre zugewiesene Zeitscheibe nicht uberschritten hat
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