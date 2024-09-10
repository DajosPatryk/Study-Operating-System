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


bool Clock::prologue() {
    clockTicks++; //erhöhen von Ticks
    pic.ack();
    return true; //wir wollen immer epilog haben fur Prozesswechsel
}

void Clock::epilogue() {
    scheduler.checkSlice();
}