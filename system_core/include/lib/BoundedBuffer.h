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
		head = 0;
		tail = 0;
		length = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T& elem)
	{
		//when buffer is not full we can add elem to it
		if(!(length == size)){
			buffer[head] = elem;
			length++;

			if(head == (size -1)){
				head=0;
			}else{
				head=head+1;
			}
		}
		//when this method is called wakeup activity waiting for input
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
		IntLock lock; //multiple adding to buffer is ok but read is critical and
		//needs to be protected

		//if buffer is empty, block activity until input comes
		if(length==0){
			active = (Activity*)scheduler.active();
			active->sleep();
		}
		//otherwise retrieve from buffer
		length--;

		if(tail==(size-1)){
			tail=0;
			return buffer[size-1];
		}else{
			tail=tail+1;
			return buffer[tail-1];
		}
	}

private:
	T buffer[size];
	int head;
	int tail;
	int length;
	Activity* active;
};

#endif

