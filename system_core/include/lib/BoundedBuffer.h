#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
		write = 0;
		read = 0;
		length = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T& elem)
	{
		//wenn buffer nicht voll kann man Inhalte einschreiben
		if(!((write==read)&& length!=0)){
			buffer[write] = elem;
			length++;
			if(write == (size -1)){
				write=0;
			}else{
				write=write+1;
			}
		}
		//nach dem addieren wecke wartende auf input activity
		if(active !=0 && active->isBlocked()){
			active->wakeup();
			active=0;
		}
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
		IntLock lock;
		//manipulation von gleicher Variable length hier und in add
		//kritisch zu schutzen in einer Funktion, da add kommt aus Interrupt
		//diese Methode ist besser dafur geeignet

		//wenn buffer leer ist lege aufrufer zu schlafen
		if(length==0){
			active = (Activity*)scheduler.active();
			active->sleep();
		}
		//nachdem buffer nicht leer ist oder die wartende prozess war aufgewacht weil Eingabe gekommen ist
		//lese das inhalt von buffer
		length--;

		if(read==(size-1)){
			read=0;
			return buffer[size-1];
		}else{
			read=read+1;
			return buffer[read-1];
		}
	}

private:
	T buffer[size];
	int write;			//"schreibkopf"
	int read;			//"lesekopf"
	int length;			//hilfsvariable um sicher zu stellen ob puffer leer oder voll ist
	Activity* active;	//gemerkte Activity die auf Eingabe wartet
};

#endif

