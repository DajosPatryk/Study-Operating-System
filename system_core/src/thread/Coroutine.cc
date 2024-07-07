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
	if (tos != 0) {
		Stack* stackTos = (Stack*)tos;

		// stack mit 0 initialisieren, vermeidet Datenanderung.
        // Initialize stack registers to 0 to prevent data corruption.
		stackTos->edi = 0;
		stackTos->esi = 0;
		stackTos->ebx = 0;
		stackTos->ebp = 0;

		// Methode coroutine() mit startup() Methode initialisieren,
		// da dieser die parameter Instanz benoetigt.
        // Set up the coroutine function pointer to the 'startup' method,
		stackTos->coroutine = &startup;
		stackTos->ret = 0;

		// arg, ein Instanz der Klasse Coroutine.
		stackTos->arg = this;
		this->sp = stackTos;
		stackTos->arg = this;   // Store a pointer to this coroutine instance in 'arg' for use by 'startup'.
		this->sp = stackTos;    // Save the pointer to the initialized stack in the coroutine's stack pointer (sp).
	}
}