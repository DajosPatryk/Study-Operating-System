#include "../include/device/PIT.h"

/*	Hier muss zunächst der Timer-Baustein programmiert werden. Dies
 *geschieht in der Klasse PIT.h. Aufbauend auf dieser Klasse ist dann eine
 *Klasse Clock.h zu implementieren, welche den vom PIT.h generierten Interrupt
 *behandelt.
 */

/** Default-Konstruktor. Das Interval wird spaeter
 * mit der interval-Methode initialisiert */
PIT::PIT() : control(CONTROL_PORT), data(DATA_PORT) {}

/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
 * ausgeloest wird */
PIT::PIT(int us) : control(CONTROL_PORT), data(DATA_PORT) { interval(us); }

/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
 * ausgeloest wird.*/
void PIT::interval(int us)
{
	//  Herz pro Takt, alle us Mikrosekunden wird ein interrupt ausgeloest
	this->interv = (1000 * us) / TIME_BASE;

	// write the low bytes of interval Time
	char lowByte = (char)(this->interv & MASK);
	control.write(LOW_BYTE); // select Counter Zero
	data.write(lowByte);

	// write the high bytes of interval Time
	char highByte = (char)((this->interv >> SHIFT) & MASK);
	control.write(HIGH_BYTE); // select Counter Zero
	data.write(highByte);
}