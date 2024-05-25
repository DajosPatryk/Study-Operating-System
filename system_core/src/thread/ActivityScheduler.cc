#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "device/CPU.h"
#include "device/Clock.h"
extern CPU cpu;
extern Clock clock;

void ActivityScheduler::start(Activity* act) {

	act->changeTo(Activity::RUNNING);   // Scheduler
	Dispatcher::init(act);            // Dispatcher
	
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
	act->changeTo(Activity::ZOMBIE);                  // Set the state to 'ZOMBIE', marking the process as terminable.
	remove((Schedulable*)act);                       // Remove the process from the ready list.
	Activity* activeProcess = getRunning(); // Load a new process only if the active process is the one being killed.
	if (activeProcess->isRunning() && activeProcess == act) reschedule();
}

void ActivityScheduler::exit() {
	IntLock lock;
	Activity* activeProcess = getRunning();  // Retrieve and store the currently active process.
	kill(activeProcess);
	
}


void ActivityScheduler::activate(Schedulable* to) {
    // Retrieve the currently running process and prepare the next activity to be activated.
	Activity* currentProcess = getRunning();

	//little difference in handling depending on state of current process
	if (currentProcess->isBlocked() || currentProcess->isZombie()){
		//list empty, go into while to wait for new ready activity
		if(to == nullptr){
			Schedulable *next;
			clock.listempty = true;
			while (true)
			{
				cpu.enableInterrupts(); //Interrupts on!
				next = (Schedulable *)scheduler.readylist.dequeue();

				// break from while if next is not nullptr (smth joined readylist)
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
			// schedule current again if readylist empty
			((Activity *)currentProcess)->changeTo(Activity::RUNNING);
			dispatch((Activity *)currentProcess);

		}else{
			// move current to the ready list and start to
			currentProcess->changeTo(Activity::READY);
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