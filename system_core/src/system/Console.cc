#include "system/Console.h"


void Console::attach() {
    mutex.wait();
}

void Console::detach() {
    mutex.signal();
}

int Console::write(const char* data, int size) {
    //analog zu cga
    KernelLock lock;
    return output.write(data, size);
}

int Console::read(char* data, int size) {
    int count = 0;
    char ch;

    while (count < size) {
        ch = data[count];
        if (ch == '\n') {
            break;
        } else {
            output.write(&ch, 1); 
            count++;
        }
       
    }

    return count;
}

char Console::read() {
    char ch;
    input.read(&ch, 1);
    return ch;
}



