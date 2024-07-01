#ifndef Semaphore_h
#define Semaphore_h
#include "system/Thread.h"
#include "lib/Queue.h"

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"

/**
 *  Semaphore: Die Semaphorenimplementation für Benutzerprozesse
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1)
	{}

	void wait()
	{
	}

	void signal()
	{
	}
private:
    int count;
    Queue sleepers = Queue();
};


#endif
