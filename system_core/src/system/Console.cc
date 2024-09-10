#include "system/Console.h"
#include "user/Environment.h"


void Console::attach() {
    mutex.wait();
}

void Console::detach() {
    mutex.signal();
}

int Console::write(const char* data, int size) {
    KernelLock lock;
    return output.write(data, size);
}

int Console::read(char* data, int size) {
    int count = 0;
    
    while (count < size) {
        char ch = Console::read();

        data[count] = ch;
        output.write(ch);
        count++;

        if (ch == '\n') {
            break;
        }
       
    }

    return count;
}

char Console::read() {
    char ch;
    input.read(&ch, 1);
    return ch;
}



