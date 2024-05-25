#include "thread/Coroutine.h"
#include "device/CPU.h"
extern CPU cpu;

#pragma GCC diagnostic ignored "-Wpmf-conversions"

void Coroutine::startup(Coroutine* obj) {
	cpu.enableInterrupts(); //important for first clock tick to activate!
	obj->body();    // Call the main function of the given coroutine.
	obj->exit();    // Terminate the coroutine after the body completes.
}

void Coroutine::resume(Coroutine *next)
{
	switchContext(this->sp, next->sp);
}

void Coroutine::setup(void* tos) {
    // if tos is not stack of main, setup frame is needed
	if (!(tos == 0x0))
	{

		this->sp = tos;

		SetupFrame frame = SetupFrame();
		frame.edi = 0;
		frame.esi = 0;
		frame.ebx = 0;
		frame.ebp = 0;
		frame.coroutine = &Coroutine::startup;
		frame.nirwana = 0;
		frame.arg = this;
		// save setup frame
		SetupFrame *ptr = (SetupFrame *)tos;
		ptr--;
		this->sp = ptr;
		*(ptr) = frame;
	}
}