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

int i = 0;
const char chars[] = {'/', '-', '\\', '|'};
//propeller
void interruptTest()
{
	i %= sizeof(chars);
	const char c = chars[i++];

	int width = 0, height = 0;
	cga.getCursor(width, height);

	cga.setCursor(0, 0);
	cga.show(c);

	cga.setCursor(width, height);
}

void Clock::handle()
{

	clockTicks++;
	pic.ack();
	//while waiting for ready activity no need to call checkSlice
	if (listempty == true)
	{
		return;
	}
	else
	{
		//interruptTest();
		scheduler.checkSlice();
	}
}