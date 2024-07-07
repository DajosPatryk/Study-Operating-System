#ifndef KernelSemaphore_h
#define KernelSemaphore_h
#include "../include/lib/Queue.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "sync/KernelLock.h"


/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore{
public:
	// Initialisierung des Zaehlers
	explicit KernelSemaphore(int count = 1){
		this->count = count;
	}

	void wait();
	void signal();

private:
    int count;
    Queue sleepers = Queue();
};

#endif

