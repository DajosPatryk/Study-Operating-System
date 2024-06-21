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

        switch (c) {
            case LEFT:
                moveLeft();
                break;

            case RIGHT:
                moveRight();
                break;

            case BACKSPACE:
                backspace();
                break;

            case ENTER:
                enter();
                break;

            default:
                if (bufferIndex < EXPR_SIZE_MAX) {
                    insert(c);
                } break;
        }
    } while ((int)c != END);
}
void Calculator::backspace()
{
    /**
     * Backspace Funktion löscht das Zeichen links vom Cursor,
     * und verschiebt alle weiteren dementsprechend nach Links
     */
    int x, y;
    cga.getCursor(x,y);
    if(x>0) {
        x--;
        for (int i = x; i < EXPR_SIZE_MAX; i++) {
            buffer[i] = buffer[i + 1];
            cga.setCursor(i, y);
            cga.show(buffer[i]);
        }
        cga.setCursor(x, y);
        bufferIndex--;
    }
}

void Calculator::insert(char c)
{
    /**
    * Insert Funktion fügt neues Zeichen an Stelle des Cursors ein,
    * falls dieser nicht am Ende des Buffers ist,
    * und verschiebt alle Zeichen rechts dementsprechend weiter nach rechts
    * wenn der Buffer nicht bereits voll ist
    */
    int x,y;
        cga.getCursor(x,y);

        int size = 0;
        if(buffer[size] > 0) {
            size++;
        }
        if (size == EXPR_SIZE_MAX) {
            return;
        }
    for (int i = EXPR_SIZE_MAX; i > x ; --i) {
        buffer[i] = buffer[i-1];
        cga.setCursor(i,y);
        cga.show(buffer[i]);

    }
    cga.setCursor(x, y);
    buffer[bufferIndex++] =c;
    out.print(c);

}

void Calculator::enter()
{
    /**
    * Evaluiert den eingegebenen Ausdruck und leert den Buffer
    */

    int res = 0;
    unsigned status = interp.eval(buffer,res);

    if(status !=0) {
        out.println();
        printErrorMsg(status);
        return;
    }
    out.print("\nResult: \n");
    out.print(res);
    out.println();
    clearBuffer();
}

void Calculator::moveLeft()
{
    /**
     * Bewegt den Cursor nach Links, wenn der nicht bereits ganz links it.
     */
    int x,y;
    cga.getCursor(x,y);
    x--;

    if (x<0)
    return;

    bufferIndex=x;
    cga.setCursor(x,y);
}

void Calculator::moveRight()
{
    /**
    * Bewegt den Cursor nach Rechts, wenn der nicht bereits ganz rechts,
    * oder am Ende des Buffers ist.
    */
    int x,y;
    cga.getCursor(x,y);
    x++;

    int size =0;
    while(buffer[size]) !=0 {
        size++;
    }
    if (x>=EXPR_SIZE_MAX || x > size)
        return;

    bufferIndex=x;
    cga.setCursor(x,y);
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
}
