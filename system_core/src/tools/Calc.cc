#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void* sp)
    : Activity(sp)
{
    init();
    wakeup();
}

void Calculator::init()
{
    clearBuffer();
    cga.clear();
}

void Calculator::body()
{
    char c;
	Key key;
	do {
		key = keyboard.read();
		c = key.getValue();

		if (c == ENTER) {
			enter();
			continue;
		}

		if (c == LEFT) {
			moveLeft();
			continue;
		}

		if (c == RIGHT) {
			moveRight();
			continue;
		}

		if (c == BACKSPACE) {
			int x, y;
			cga.getCursor(x, y);

			x--;

			if(x < 0) continue;

			for(int i = x; i < EXPR_SIZE_MAX; i++){
				buffer[i] = buffer[i + 1];

				cga.setCursor(i, y);

				cga.show(buffer[i]);
			}

			cga.setCursor(x, y);

			bufferIndex--;

			continue;
		}
        //write only if there is still place left in line
		if(bufferIndex < EXPR_SIZE_MAX){
			insert(c);
		}

	} while ((int)c != END);

}

void Calculator::insert(char c)
{
    int x, y;
	cga.getCursor(x, y);

	int size = 0;
	while(buffer[size] != 0){
		size++;
	}
   
   if(size == EXPR_SIZE_MAX){
		return;
	}	
	// move consecutive one to the right
	for (int i = EXPR_SIZE_MAX - 1; i > x; i--) {
		buffer[i] = buffer[i - 1];

		cga.setCursor(i, y);

		cga.show(buffer[i]);
	}

	cga.setCursor(x, y);

	buffer[bufferIndex++] = c;
	out.print(c);
}

void Calculator::enter()
{
    int res = 0;
	unsigned status = interp.eval(buffer, res);

	if (status != 0) {
		printErrorMsg(status);
		return;
	}

	out.println();
	out.print("Result: ");

	out.print(res);

	out.println();
	clearBuffer();
}

void Calculator::moveLeft()
{
    int x, y;
	cga.getCursor(x, y);
	x--;

	if (x < 0)
		return;

	bufferIndex = x;

	cga.setCursor(x, y);
}

void Calculator::moveRight()
{
    int x, y;
	cga.getCursor(x, y);
	x++;
	
	int size = 0;
	while(buffer[size] != 0){
		size++;
	}


	if (x > EXPR_SIZE_MAX || x > size)
		return;

	bufferIndex = x;

	cga.setCursor(x, y);
}

void Calculator::renderBuffer()
{
    // Cursor sichern
    int column, row;
    cga.getCursor(column, row);

    // Zeile schreiben
    cga.setCursor(0, row);
    cga.write(buffer, EXPR_SIZE_MAX);

    // Cursor wiederherstellen
    cga.setCursor(column, row);
}

void Calculator::clearBuffer()
{
    bufferIndex = 0;
	interp.numberStackIndex = 0;
	interp.operatorStackIndex = 0;
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i)
        buffer[i] = 0;
}

void Calculator::printErrorMsg(unsigned code)
{
    switch (code) {
    case Interpreter::UNEXP_EOT:
        out.print("Error: Unexpected end of expression!");
        break;

    case Interpreter::UNEXP_SYMBOL:
        out.print("Error: Unexpected symbol!");
        break;

    case Interpreter::ARITHM_ERROR:
        out.print("Error: Arithmetic error!");
        break;

    case Interpreter::BAD_BUFFER:
        out.print("Error: Invalid buffer!");
        break;

    default:
        break;
    }
    out.println();
    clearBuffer();
}
