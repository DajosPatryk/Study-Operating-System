#include "system/Semaphore.h"
#include "sync/Monitor.h"

Semaphore::Semaphore(int count)
        : KernelSemaphore(count)
{}

void Semaphore::wait() {
    // Call the wait (P operation) method from KernelSemaphore
    KernelSemaphore::p();
}

void Semaphore::signal() {
    // Call the signal (V operation) method from KernelSemaphore
    KernelSemaphore::v();
}
