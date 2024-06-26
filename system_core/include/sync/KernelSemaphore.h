#ifndef KernelSemaphore_h
#define KernelSemaphore_h


/**
 * KernelSemaphore: Semaphorenimplementation für kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	explicit KernelSemaphore(int count = 1)
	{
	}

	void wait();
	void signal();

private:

};

#endif

