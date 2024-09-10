#include "sync/KernelSemaphore.h"

extern ActivityScheduler scheduler;

void KernelSemaphore::wait() {
    //signal konsumieren
    if (count > 0){
        count--; 
    }else {
        //wenn zaehler 0, lege activity zum schlafen
        Activity *sleeper = (Activity *)scheduler.active();
        sleepers.enqueue(sleeper);
        sleeper->sleep();
    }
}

void KernelSemaphore::signal() {
    //wenn nichts wartet, addiere signal
    if (sleepers.isEmpty()) {
        count ++;
    } else {
        //sonst wache auf  wartende activity
        Activity *waker = (Activity *)sleepers.dequeue();
        while (waker->isReady())
        {   
            //fur sicherheit sodass es korrekt in Liste kommt falls durch etwas
            //anderes schon aufgewacht war
            waker->yield();
        }
        waker->wakeup();
    }
}