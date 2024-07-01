#include "system/Console.h"
#include "sync/Monitor.h"

extern Monitor consoleMonitor;

Console::Console(InputChannel& input, OutputChannel& output)
        : input(input), output(output) {}

void Console::attach() {
    consoleMonitor.enter()
}

void Console::detach() {
    consoleMonitor.leave();
}

int Console::write(const char* data, int size) {
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
        }
        count++;
    }

    return count;
}

char Console::read() {
    char ch;
    input.read(&ch, 1); // Liest
    output.write(&ch, 1); // Echo
    return ch;
}

void Console::blueScreen(const char* msg) {
    output.blueScreen(msg);
}

