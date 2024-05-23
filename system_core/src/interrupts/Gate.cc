#include "interrupts/Gate.h"
#include "interrupts/PanicGate.h"
#include "interrupts/PageFaultGate.h"
#include "interrupts/SpuriousGate.h"

PanicGate panicGate;
PageFaultGate pageFaultGate;
SpuriousGate spuriousGate;

#include "device/PIC.h"
extern PIC pic;

#include "interrupts/InterruptGuardian.h"
extern InterruptGuardian interruptGuardian;

Gate::Gate(int num)
{
	this->num = num;
	pic.enable(num);
	if (num > 0)
		interruptGuardian.registerGate(this,num);
}

Gate::~Gate()
{
	if (num > 0)
		interruptGuardian.registerGate(&panicGate,num);
}
