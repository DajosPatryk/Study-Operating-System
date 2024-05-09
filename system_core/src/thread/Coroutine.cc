#include "thread/Coroutine.h"

void Coroutine::startup(Coroutine* obj)
{
	obj->body(); // Aufruf der gegebenere Coroutine
	obj->exit(); // am Ende Coroutine terminieren
}

void Coroutine::setup(void* tos)
{
	if (tos != 0)
	{
		// Bei nullptr es geht auf stack von main, dadurch kein eigenen gebraucht
		Stack* stackTos = (Stack*)tos;

		// stack mit 0 initialisieren, vermeidet Datenanderung.
		stackTos->edi = 0;
		stackTos->esi = 0;
		stackTos->ebx = 0;
		stackTos->ebp = 0;

		// Methode coroutine() mit startup() Methode initialisieren,
		// da dieser die parameter Instanz benoetigt.
		stackTos->coroutine = &startup;
		stackTos->ret = 0;

		// arg, ein Instanz der Klasse Coroutine.
		stackTos->arg = this;
		this->sp = stackTos;
	}
}