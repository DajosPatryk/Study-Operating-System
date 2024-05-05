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
    //0 can be immediately be solved
    if(x ==0){
        char c = x +'0';

        if(base ==2){
            print("0b");
            print(c);
        }else if(base == 16){
            print("0x");
            print(c);
        }else{
            print(c);
        }

    }else{
        //only accept numbers with acceptable base of 2, 10 or 16
        if(base == 2 || base ==10 || base == 16){
            //invert x to positive value if negative but save information it was negative
            bool negativ = false;
            if(x<0){
                negativ = true;
                x = -(x);
            }

            //https://www.geeksforgeeks.org/how-to-convert-given-number-to-a-character-array/
            //no string as object in c, need to do algorithm "per hand"
            // Count digits in number x
            int m = x;
            int digit = 0;
            while (m) {

                // Increment number of digits
                digit++;

                // Truncate the last
                // digit from the number
                m /= base;
            }

            // Declare char array for result
            char arr[digit];
            // Declare duplicate char array
            char arr1[digit];
            //those are important because we will reverse array for final result

            // Separating integer into digits and
            // accommodate it to character array
            int index = 0;
            while (x) {
                // Separate last digit from
                // the number and add ASCII
                // value of character '0' is 48
                if(x%base <10){
                    arr1[++index] = x % base + '0';
                }else{
                    int result = x%base;
                    switch (result){
                        case 10: arr1[++index] = 'A';break;
                        case 11: arr1[++index] = 'B';break;
                        case 12: arr1[++index] = 'C';break;
                        case 13: arr1[++index] = 'D';break;
                        case 14: arr1[++index] = 'E';break;
                        case 15: arr1[++index] = 'F';
                    }
                }
                // Truncate the last
                // digit from the number
                x /= base;
            }

            // Reverse the array for result
            int i;
            for (i = 0; i < index; i++) {
                arr[i] = arr1[index - i];
            }

            // Char array truncate by null
            arr[i] = '\0';

            if(negativ==false){
                if(base == 2){
                    print("0b");
                    print(arr);
                }else if(base ==16){
                    print("0x");
                    print(arr);
                }else{
                    print(arr);
                }


            }else{
                if(base == 2){
                    print('-');
                    print("0b");
                    print(arr);
                }else if(base ==16){
                    print('-');
                    print("0x");
                    print(arr);
                }else{
                    print('-');
                    print(arr);
                }

            }
        }else{
            print("falsche Basis");
        }
    }
}


void PrintStream::print(unsigned x, int base) {
    //similar to previous one, don't need to care for negative
    //but needs separate function as unsigned int can store bigger number
    if(x ==0){
        char c = x +'0';
        if(base ==2){
            print("0b");
            print(c);
        }else if(base == 16){
            print("0x");
            print(c);
        }else{
            print(c);
        }
    }else{

        if(base == 2 || base ==10 || base == 16){
            // Count digits in number x
            unsigned int m = x;
            unsigned int digit = 0;
            while (m) {

                // Increment number of digits
                digit++;
                // Truncate the last
                // digit from the number
                m /= base;
            }

            // Declare char array for result
            char arr[digit];
            // Declare duplicate char array
            char arr1[digit];

            // Separating integer into digits and
            // accommodate it to character array
            unsigned int index = 0;
            while (x) {
                // Separate last digit from
                // the number and add ASCII
                // value of character '0' is 48
                if(x%base <10){
                    arr1[++index] = x % base + '0';
                }else{
                    int result = x%base;

                    switch (result){
                        case 10: arr1[++index] = 'A';break;
                        case 11: arr1[++index] = 'B';break;
                        case 12: arr1[++index] = 'C';break;
                        case 13: arr1[++index] = 'D';break;
                        case 14: arr1[++index] = 'E';break;
                        case 15: arr1[++index] = 'F';
                    }
                }
                // Truncate the last
                // digit from the number
                x /= base;
            }
            // Reverse the array for result
            unsigned int i;
            for (i = 0; i < index; i++) {
                arr[i] = arr1[index - i];
            }
            // Char array truncate by null
            arr[i] = '\0';


            if(base == 2){
                print("0b");
                print(arr);
            }else if(base ==16){
                print("0x");
                print(arr);
            }else{
                print(arr);
            }
        }else{
            print("falsche Basis");
        }}
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

