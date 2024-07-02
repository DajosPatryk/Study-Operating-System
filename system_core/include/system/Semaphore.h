#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"



/**
 *  Semaphore: Die Semaphorenimplementation f�r Benutzerprozesse
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1): KernelSemaphore(1)
	{}

	void wait()
	{
		//KernelLock lock;
        KernelSemaphore::wait();
	}

	void signal()
	{
		//KernelLock lock;
        KernelSemaphore::signal();
	}

};


#endif
