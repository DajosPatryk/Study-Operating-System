#include "sync/KernelSemaphore.h"

KernelSemaphore::KernelSemaphore(int count) : count(count) {
}

void KernelSemaphore::wait() {
    if (count > 0) count -= 1;
    else {
        Thread* self = Thread::self();
        sleepers.enqueue((Chain) self);
        Thread::sleep();
    }
}

void KernelSemaphore::signal() {
    if (sleepers.isEmpty()) {
        count ++;
    } else {
        Thread* next = (Thread*)sleepers.dequeue();
        next -> wakeup();
    }
}