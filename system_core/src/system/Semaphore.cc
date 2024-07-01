#include "system/Semaphore.h"

Semaphore::Semaphore(int count) : KernelSemaphore(count), count(count) {
}

