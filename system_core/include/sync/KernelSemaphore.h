#ifndef KernelSemaphore_h
#define KernelSemaphore_h
#include "../include/lib/Queue.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"



/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore{
public:
	// Initialisierung des Zaehlers
	explicit KernelSemaphore(int count = 1){
		count = count;
	}

	void wait();
	void signal();

private:
    int count =1;
    Queue sleepers = Queue();
};

#endif

