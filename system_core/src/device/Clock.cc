#include "device/Clock.h"
#include "io/PrintStream.h"

extern ActivityScheduler scheduler;
extern PIC pic;

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
	//erhohe ticks und danach bestatige Bearbeitung dieser Interrupt
	clockTicks++;
	pic.ack();
	//checkslice wo das reschedule nach Ablauf der Zeitscheibe passiert nur bei nicht leeren Readylist
	if (listempty == true)
	{
		return;
	}
	else
	{
		scheduler.checkSlice();
	}
}