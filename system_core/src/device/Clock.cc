#include "device/Clock.h"
#include "interrupts/InterruptVector.h"

#include "io/PrintStream.h"
extern PrintStream out;

#include "thread/ActivityScheduler.h"
extern ActivityScheduler scheduler;

#include "device/PIC.h"
extern PIC pic;

#include "interrupts/IntLock.h"

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

#include "device/CgaChannel.h"
extern CgaChannel cga;

int state = 0;
const char chars[] = {'/', '-', '\\', '|'};

void testProp()
{
	state %= sizeof(chars);
	const char c = chars[state++];

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

	if (listempty == true)
	{
		return;
	}
	else
	{
		// testProp();
		scheduler.checkSlice();
	}
}