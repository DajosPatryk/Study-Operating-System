#ifndef PIT_h
#define PIT_h

#define STANDARD_INTERVAL 20000 //20ms

/*
 * PIT: Der Treiber fuer den Programmable Interval Timer
 *
 *	Wenn der PIT richtig programmiert wurde,
 *	liefert er alle "us" Mikrosekunden einen Interrupt
 */

#include "io/IOPort.h"

class PIT {
public:

	/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
	PIT ();

	/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird */
	explicit PIT (int us);

	/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  * 
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void interval (int us);

protected:
	int us = STANDARD_INTERVAL;

private:
	enum Values {
		TIME_BASE = 838,  // Dauer eines Zaehlticks in ns 
		//hier gleich Steurworter vorbereiten
		/* Zähler0 00,high byte 10,periodische impulse 010, 
		binäre Zählung von 16 Bit 0*/
		HIGH_BYTE = 0b00100100,
		/* Zähler0 00,low byte 01,periodische impulse 010, 
		binäre Zählung von 16 Bit 0*/
		LOW_BYTE = 0b00010100,
		MASK = 0x00FF,
		SHIFT = 8
	};

	// Die I/O Ports des PIC
	enum Ports {
		CONTROL_PORT 	= 0x43,
		DATA_PORT 	= 0x40
	};

	// Verbindungs ports zu Hardware.
	IOPort8 control;
	IOPort8 data;

	// Variable, Zeit-Interval fuers PIT
	unsigned int interv;
};

extern PIT pit;
#endif
