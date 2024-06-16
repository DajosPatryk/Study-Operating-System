#include "device/Clock.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "device/PIC.h"
#include "device/CgaChannel.h"

extern ActivityScheduler scheduler;
extern PIC pic;
extern CgaChannel cga;

Clock::Clock() : Gate(InterruptVector::Timer), PIT()
{
	windup(STANDARD_INTERVAL);
}

Clock::Clock(int us) : Gate(InterruptVector::Timer), PIT(us)
{
	windup(us);
}

void Clock::windup(int us)
{
	interval(us);
	pic.enable(PIC::Interrupts::PIT);
}


void Clock::handle()
{
	//ticks up and acknowledge interrupt so next one of same type can come
	clockTicks++;
	pic.ack();
	//while waiting for ready activity to join readylist no need to call checkSlice
	if (listempty == true)
	{
		return;
	}
	else
	{
		scheduler.checkSlice();
	}
}