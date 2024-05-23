#include "thread/Coroutine.h"
#include "device/CPU.h"
extern CPU cpu;

void Coroutine::startup(Coroutine* obj) {
	cpu.enableInterrupts(); //important for first clock tick to activate!
	obj->body();    // Call the main function of the given coroutine.
	obj->exit();    // Terminate the coroutine after the body completes.
}

void Coroutine::setup(void* tos) {
    // If tos is not nullptr, initialize a new stack from the given stack pointer.
	if (tos != 0) {
		Stack* stackTos = (Stack*)tos;

        // Initialize stack registers to 0 to prevent data corruption.
		stackTos->edi = 0;
		stackTos->esi = 0;
		stackTos->ebx = 0;
		stackTos->ebp = 0;

        // Set up the coroutine function pointer to the 'startup' method,
		stackTos->coroutine = &startup;
		stackTos->ret = 0;

		stackTos->arg = this;   // Store a pointer to this coroutine instance in 'arg' for use by 'startup'.
		this->sp = stackTos;    // Save the pointer to the initialized stack in the coroutine's stack pointer (sp).
	}
}