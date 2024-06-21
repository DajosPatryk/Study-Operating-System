#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gefüllt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet für euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  müsst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
        read = 0;
        write = 0;
        length = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten müssen hier geweckt werden.
	 */
	void add(T& elem)
	{
        if(!((length != 0) && (read==write)))   //prüft, ob Buffer voll ist, schreibt wenn nicht
        {
            buffer[write] = elem;
            length++;
            if(write != (size -1)){
                write++;
            } else {
                write = 0;
            }

        }
        if (active =!0 && active->isBlocked())  //Aufwecken von wartender Activity
        {
            active->wakeup();
            active =0;

}
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
        /**
         * Die Methode wird vor Unterbrechungen durch Interrupts geschützt
         * damit Daten nicht überlesen oder mehrfach gelesen werden
         */

        IntLock lock;

        // Schlafenlegen des lesenden Prozesses, falls Puffer leer ist
        while(length==0){
            active = (Activity*)scheduler.active();
            active->sleep();
        }
        // Wenn der Buffer nicht leer ist, werden Daten gelesen
        length--;

        /*
         * Wenn read am Ende des Buffers ist, wird es nach dem Lesen auf den Anfang gesetzt.
         * Sonst wird es normal auf die nächste Position verschoben.
         */
        if(read==(size-1)){
            read=0;
            return buffer[size-1];
        } else {
            read=read+1;
            return buffer[read-1];
        }
	}

private:
	T buffer[size];
    int read;
    int write;
    int length;
    Activity* active;
};

#endif

