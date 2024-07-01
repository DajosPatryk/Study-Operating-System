#ifndef KernelSemaphore_h
#define KernelSemaphore_h
#include "system/Thread.h"
#include "lib/Queue.h"


/**
 * KernelSemaphore: Semaphorenimplementation für kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore: public Thread {
public:
	// Initialisierung des Zaehlers
	explicit KernelSemaphore(int count = 1);

	void wait();
	void signal();

private:
    int count;
    Queue sleepers = Queue();
};

#endif

