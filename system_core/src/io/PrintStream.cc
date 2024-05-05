#include "../include/io/PrintStream.h"

PrintStream::PrintStream(OutputChannel *chan) : channel(*chan) {}

PrintStream::PrintStream(OutputChannel &chan) : channel(chan) {}

void PrintStream::print(const char *str) {
    int i = 0;
    while (str[i++] != 0);    // Finds size of C-style string
    channel.write(str, i - 1);
}

void PrintStream::print(char ch) {
    channel.write(&ch, 1);
}

void PrintStream::println(const char *str) {
    print(str);
    println();
}

void PrintStream::println() {
    channel.write((const char*) "\n", 1);
}

void PrintStream::print(int x, int base) {
    // Solving 0 immediately
    if (x == 0) {
        char c = x + '0';
        if (base == 2) {
            print("0b");
            print(c);
        } else if (base == 16) {
            print("0x");
            print(c);
        } else print(c);
        return;
    }

    if (base != 2 && base != 10 && base != 16) {
        print("Error: Unknown digit base.");
        return;
    }

    // Inverts x, saves information
    bool negativ = false;
    if (x < 0) {
        negativ = true;
        x = -(x);
    }

    /**
     * Source: https://www.geeksforgeeks.org/how-to-convert-given-number-to-a-character-array/
     *
     * No string as object in C, only C-Style strings, need to do run algorithm
     * Counts digits in number x
     */
    int m = x;
    int digit = 0;
    while (m) {
        digit++;    // Increments number of digits
        m /= base;  // Truncates the last digit from the number
    }

    char arr[digit];    // Result
    char arr1[digit];   // Duplicate, important as array will be reversed for final result

    // Separating integer into digits and accommodating to char arr
    int index = 0;
    while (x) {
        // Separate last digit from the number and add ASCII val of char, '0' is 48
        if (x % base < 10) {
            arr1[++index] = x % base + '0';
        }
        else {
            int result = x % base;
            switch (result) {
                case 10: arr1[++index] = 'A'; break;
                case 11: arr1[++index] = 'B'; break;
                case 12: arr1[++index] = 'C'; break;
                case 13: arr1[++index] = 'D'; break;
                case 14: arr1[++index] = 'E'; break;
                case 15: arr1[++index] = 'F';
            }
        }

        // Truncates the last digit from the number
        x /= base;
    }

    // Reverses the array for result
    int i;
    for (i = 0; i < index; i++) { arr[i] = arr1[index - i]; }
    arr[i] = '\0';  // Char array truncates by null

    if (negativ == false) {
        if (base == 2) {
            print("0b");
            print(arr);
        } else if (base == 16) {
            print("0x");
            print(arr);
        } else print(arr);



    } else {
        if (base == 2) {
            print('-');
            print("0b");
            print(arr);
        } else if (base == 16) {
            print('-');
            print("0x");
            print(arr);
        } else {
            print('-');
            print(arr);
        }

    }
}


void PrintStream::print(unsigned x, int base) {
    // Solving 0 immediately
    if (x == 0) {
        char c = x + '0';
        if (base == 2) {
            print("0b");
            print(c);
        } else if (base == 16) {
            print("0x");
            print(c);
        } else print(c);
        return;
    }

    if (base != 2 && base != 10 && base != 16) {
        print("Error: Unknown digit base.");
        return;
    }

    /**
     * Source: https://www.geeksforgeeks.org/how-to-convert-given-number-to-a-character-array/
     *
     * No string as object in C, only C-Style strings, need to do run algorithm
     * Counts digits in number x
     */
    unsigned int m = x;
    unsigned int digit = 0;
    while (m) {
        digit++;    // Increments number of digits
        m /= base;  // Truncates the last digit from the number
    }

    char arr[digit];    // Result
    char arr1[digit];   // Duplicate, important as array will be reversed for final result

    // Separating integer into digits and accommodating to char arr
    unsigned int index = 0;
    while (x) {
        // Separate last digit from the number and add ASCII val of char, '0' is 48
        if (x % base < 10) {
            arr1[++index] = x % base + '0';
        } else {
            int result = x % base;
            switch (result) {
                case 10: arr1[++index] = 'A'; break;
                case 11: arr1[++index] = 'B'; break;
                case 12: arr1[++index] = 'C'; break;
                case 13: arr1[++index] = 'D'; break;
                case 14: arr1[++index] = 'E'; break;
                case 15: arr1[++index] = 'F';
            }
        }
        // Truncates the last digit from the number
        x /= base;
    }

    // Reverses the array for result
    int i;
    for (i = 0; i < index; i++) { arr[i] = arr1[index - i]; }
    arr[i] = '\0';  // Char array truncates by null


    if (base == 2) {
        print("0b");
        print(arr);
    } else if (base == 16) {
        print("0x");
        print(arr);
    } else {
        print(arr);
    }
}


void PrintStream::print(void *p) {
    if (p == nullptr) {
        print("Error: Empty address.");
        return;
    }

    // Already implemented method, translates pointer to int
    int addr = reinterpret_cast<int>(p);

    // Results in output "0x0x", "0x" => hex, "0x0x" => address
    print("0x");
    print(addr, 16);

}

