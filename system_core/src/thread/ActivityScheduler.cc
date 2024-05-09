#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"

void ActivityScheduler::start(Activity* act)
{
	// Scheduler
	act->changeTo(Activity::RUNNING);
	// Dispatcher
	init((Coroutine*)act);
}

void ActivityScheduler::suspend()
{
	// aktuelle Prozess aufrufen und zwishenspeichern
	Activity* activeProcess = (Activity*)this->active();
	// Ihrer Ausfuehrungszustand aendern
	activeProcess->changeTo(Activity::BLOCKED);
	// naeschte Prozess vom ReadyList zum scheduler ubermitteln
	reschedule();
}

void ActivityScheduler::kill(Activity* act)
{
	// Zustand 'Zombie' setzen (also loeschbar machen)
	act->changeTo(Activity::ZOMBIE);
	// Prozess von ReadyList entfernen.
	remove((Schedulable*)act);
	// Neuen Prozess laden nur wenn kein aktive Prozess gibt.
	Activity* activeProcess = (Activity*)(this->active());
	if (activeProcess->isRunning() && activeProcess == act)
	{
		reschedule();
	}
}

void ActivityScheduler::exit()
{
	// aktuelle Prozess aufrufen und inzwischenspeichern
	Activity* activeProcess = (Activity*)active();
	// dieses Prozess terminieren
	kill(activeProcess);
	// naeschte Prozess vom ReadyList zum scheduler ubermitteln
	reschedule();
}

void ActivityScheduler::activate(Schedulable* to)
{
    //gerade laufende Prozzess und der zu aktivieren als Activities bereiten
	Activity* currentProcess = (Activity*)(this->active());
	Activity* nextProcess = (Activity*)to;

    //wenn gerade laufende Prozess nicht blocked oder zombie ist kann es wieder in ReadyList
	if ((!(currentProcess->isBlocked()) && currentProcess->isRunning()) &&
	    (!(currentProcess->isZombie())))
	{
		// gerade laufende Prozess in Ready Liste stellen
		currentProcess->changeTo(Activity::READY);
		Schedulable* tempSched = (Schedulable*)currentProcess;
		scheduler.schedule(tempSched);
	}

	// solange es gibt kein zu aktivieren Prozzess
	// standig versuchen ein aus ReadyList zu bekommen
	while (nextProcess == 0)
	{
		// es muss kein laufende Prozess uberschrieben.
		if (!currentProcess->isRunning())
		{
			nextProcess = (Activity*)(readylist.dequeue());
            //hier moglich das gerade eingefugte in ReadyList vorher gerannte
            //Prozess geholt wird wenn es einziger Prozess ist
		}
	}

	// Die zu aktivierende Prozess muss existieren. Dann status aendern
	// und mittels Dispatch uebergeben
	if (nextProcess != 0)
	{
		nextProcess->changeTo(Activity::RUNNING);
		dispatch(nextProcess);
	}
}