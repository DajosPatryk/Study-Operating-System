#include "thread/Activity.h"
#include "io/PrintStream.h"
#include "thread/ActivityScheduler.h"

// Initialer Zustand ist blocked, damit der Thread
// nicht sofort laeuft
Activity::Activity(void* tos) : Coroutine(tos), state(BLOCKED)
{
	//  Aktivierung durch der abgeleiteten Klasse (Activity) mittels
	//  "wakeup".
}

Activity::Activity()
{
	// setzen Prozesszustand auf BLOCKED.
	this->state = BLOCKED;
	// initialisieren der ersten Aktivität, des Schedulers und des
	// Dispatchers
	scheduler.start(this);
}

Activity::~Activity()
{
	scheduler.kill(this); // explizites Terminieren dieses Prozesses
}

void Activity::sleep() { scheduler.suspend(); }

void Activity::wakeup()
{
    //aufwachen von Blockierten Activities nur sinvoll
	if (isBlocked())
	{
		this->state = READY;
		scheduler.schedule(this);
	}
}

void Activity::yield() { scheduler.reschedule(); }

void Activity::exit()
{
	// wartende Prozesse aufwachen
	if (joined != 0)
	{
		joined->wakeup();
		joined = 0;
	}

	// aktuell wach oder aktive Prozess dann terminieren
	scheduler.exit();
}

void Activity::join()
{
	// aufgerufene Prozess (von ReadyList) ermitteln und zwischenspeichern
	Activity* activeProcess = (Activity*)scheduler.active();

	// Ueberpruefen ob Aufrufer kein Zombie und kein Aufgerufener selbst ist
	// wenn ja join gerade laufende Prozess und suspendiere
	if (!(this->isZombie()) && this != activeProcess)
	{
		this->joined = activeProcess;
		scheduler.suspend();
	}
}