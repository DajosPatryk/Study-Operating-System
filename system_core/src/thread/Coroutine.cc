#include "thread/Coroutine.h"
#include "device/CPU.h"
#include "sync/Monitor.h"
extern CPU cpu;

#pragma GCC diagnostic ignored "-Wpmf-conversions"

void Coroutine::resume(Coroutine *next)
{
    switchContext(this->sp, next->sp);
}

void Coroutine::startup(Coroutine* obj) {
	monitor.leave(); // Monitor statt Interrupts.
	obj->body();    // Call the main function of the given coroutine.
	obj->exit();    // Terminate the coroutine after the body completes.
}


// Bei nullptr es geht auf stack von main, dadurch kein eigenen gebraucht
void Coroutine::setup(void* tos) {
    // If tos is not nullptr, initialize a new stack from the given stack pointer.
	if (!(tos == 0x0)) {
		this->sp = tos;
		Stack stackTos = Stack();

		// stack mit 0 initialisieren, vermeidet Datenanderung.
        // Initialize stack registers to 0 to prevent data corruption.
		stackTos.edi = 0;
		stackTos.esi = 0;
		stackTos.ebx = 0;
		stackTos.ebp = 0;

		// Methode coroutine() mit startup() Methode initialisieren,
		// da dieser die parameter Instanz benoetigt.
        // Set up the coroutine function pointer to the 'startup' method,
		stackTos.coroutine = &Coroutine::startup;
		stackTos.ret = 0;

		// arg, ein Instanz der Klasse Coroutine.
		stackTos.arg = this;
		//jetzt so vorbereitete Stack speichern
		Stack *st = (Stack *)tos;
		st--;
		this->sp = st;
		*(st) = stackTos;
		}
}