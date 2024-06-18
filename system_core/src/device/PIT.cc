#include "device/PIT.h"

PIT::PIT() : control(CONTROL_PORT), data(DATA_PORT) {}


PIT::PIT(int us) : control(CONTROL_PORT), data(DATA_PORT) { interval(us); }


void PIT::interval(int us)
{
	//Herz pro Takt, alle us Mikrosekunden wird ein interrupt ausgeloest
	this->interv = (1000 * us) / TIME_BASE;

	// niedrige bits schreiben
	char lowByte = (char)(this->interv & MASK);
	control.write(LOW_BYTE); 
	data.write(lowByte);

	// hoche bits schreiben
	char highByte = (char)((this->interv >> SHIFT) & MASK);
	control.write(HIGH_BYTE);
	data.write(highByte);
}