#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "device/CPU.h"
#include "device/Clock.h"
extern CPU cpu;
extern Clock clock;
#include "sync/KernelLock.h"
#include "sync/Monitor.h"
#include "user/Environment.h"

void ActivityScheduler::start(Activity* act) {
	
	Dispatcher::init(act);// Dispatching first activity
    act->changeTo(Activity::RUNNING);
	spinLock = false;
}

void ActivityScheduler::suspend() {
	Activity* activeProcess = getRunning();  // Retrieves and stores the currently active process.
	activeProcess->changeTo(Activity::BLOCKED);
	remove(activeProcess);
	reschedule(); // Delegate to the scheduler and transition to the next process from the ready list.
}

void ActivityScheduler::kill(Activity* act) {
	act->changeTo(Activity::ZOMBIE);// Set the state to 'ZOMBIE', marking the process as terminable.
	Activity* activeProcess = getRunning(); // Load a new process only if the active process is the one being killed.
	// Remove the process from the ready list.
	remove(act); 
	if (activeProcess == act){
		reschedule();}
	
}

void ActivityScheduler::exit() {
	Activity* activeProcess = getRunning();  // Retrieve and store the currently active process.
	kill(activeProcess);
	
}


void ActivityScheduler::activate(Schedulable* to) {
	//wenn in aktiven Warten zuruckkehren
	if(spinLock){
		return;
	}
    // Retrieve the currently running process
	Activity* currentProcess = getRunning();
	Activity* next = (Activity*) to;

	//sinvoller erst schauen ob *to naechste  gultige activity ist
	if(next == nullptr){
		//little difference in handling depending on state of current process
		if (currentProcess->isBlocked() || currentProcess->isZombie())
			{
				//aktives Warten fur neue Ready activity
				while (true)
				{	//aktives warten merken
					spinLock = true;
					//mit dieser Stuck Code erlauben wir Interrupt epiloge bearbeitet zu sein
					monitor.leave();
                	cpu.halt();
                	monitor.enter();

					next = (Activity *)readylist.dequeue();
					// break von while wenn etwas reingekommen ist
					// und nicht aktiv (da anfangs sind sie blockiert)
					if (next != nullptr && !next->isReady())
					{
						break;
					}
				}
				//aktives warten ende
				spinLock = false;
				// activate new activity
				next->changeTo(Activity::RUNNING);
				dispatch(next);
		}
		//wenn die gerade laufende Prozess normal war und kein nachfolger da ist,
		//wird einfach diese Methode verlassen und es lauft weiter
	}else
		{
			if(currentProcess->isRunning())
			{
				//jetzige lauffahige Prozess zu ReadyList addieren
				currentProcess->changeTo(Activity::READY);
				scheduler.schedule(currentProcess);
			}
			//aktiviere naechste Activity
			next->changeTo(Activity::RUNNING);
			dispatch(next);

		}

}

Activity *ActivityScheduler::getRunning()
{
	return (Activity *)Dispatcher::active();
}