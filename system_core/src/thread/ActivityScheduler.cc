#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "device/CPU.h"
#include "device/Clock.h"
extern CPU cpu;
extern Clock clock;

void ActivityScheduler::start(Activity* act) {
	
	Dispatcher::init(act);            // Dispatching first activity
	
}

void ActivityScheduler::suspend() {
	IntLock lock;
	Activity* activeProcess = getRunning();  // Retrieves and stores the currently active process.
	activeProcess->changeTo(Activity::BLOCKED);
	remove(activeProcess);
	reschedule();                                         // Delegate to the scheduler and transition to the next process from the ready list.
}

void ActivityScheduler::kill(Activity* act) {
	IntLock lock;
	act->changeTo(Activity::ZOMBIE);// Set the state to 'ZOMBIE', marking the process as terminable.
	Activity* activeProcess = getRunning(); // Load a new process only if the active process is the one being killed.
	// Remove the process from the ready list.
	remove(act); 
	if (activeProcess == act){
		reschedule();}
	
}

void ActivityScheduler::exit() {
	IntLock lock;
	Activity* activeProcess = getRunning();  // Retrieve and store the currently active process.
	kill(activeProcess);
	
}


void ActivityScheduler::activate(Schedulable* to) {
    // Retrieve the currently running process
	Activity* currentProcess = getRunning();

	//little difference in handling depending on state of current process
	if (currentProcess->isBlocked() || currentProcess->isZombie()){
		//list empty, go into while to wait for new ready activity
		if(to == nullptr){
			Schedulable *next;
			clock.listempty = true; //clock interrupt won't call checkSlice in while
			while (true)
			{
				cpu.enableInterrupts(); //Interrupts on!
				next = (Schedulable *)scheduler.readylist.dequeue();
				// break from while if next is not nullptr (which means ready activity was added to readylist)
				if (next != nullptr)
				{
					break;
				}
			}
			cpu.disableInterrupts(); //interrupts off!
			clock.listempty = false; 
			// activate new activity
			activate(next);
		}else{
			//if to  exists then activate it normally
			((Activity *)to)->changeTo(Activity::RUNNING);
			dispatch((Activity *)to);
		}
	}
	//current process runninng
	else
	{
		if(to==nullptr){
			// wenn nur gerade laufende Prozess lauffahig,
			//kein Kontextwechsel noetig, einfach return
			return;
		}else{
			// move current to the ready list and start to
			schedule(currentProcess);
			((Activity *)to)->changeTo(Activity::RUNNING);
			dispatch((Activity *)to);
		}
	}

}

Activity *ActivityScheduler::getRunning()
{
	return (Activity *)Dispatcher::active();
}