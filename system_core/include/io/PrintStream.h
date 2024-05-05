#ifndef PrintStream_h
#define PrintStream_h

#include "io/OutputChannel.h"

/**
 * Simulates Java's PrintStream for outputting characters and strings.
 * This class converts numeric values to readable chars and outputs them to a specified channel.
 */
class PrintStream {
private:
	enum Base {
		BINARY  = 2,
		DECIMAL = 10,
		HEX     = 16
	};

public:
    /**
     * Constructor using pointer to OutputChannel.
     * @param chan OutputChannel*: Pointer to output channel.
     */
	explicit PrintStream(OutputChannel* chan);

    /**
     * Constructor using reference to OutputChannel.
     * @param chan OutputChannel&: Reference to output channel.
     */
	explicit PrintStream(OutputChannel& chan);

    /**
     * Prints a null-terminated string to the output channel.
     * @param str const char*: Null-terminated C-Style string.
     */
	void print(const char* str);

    /**
     * Prints a single character to the output channel.
     * @param ch char: Character to print.
     */
	void print(char ch);

    /**
     * Prints string followed by a newline to the output channel.
     * @param str const char*: C-Style String to print.
     */
	void println(const char* str);

    /***
     * Outputs a newline character to the output channel.
     */
	void println();

    /**
     * Prints an integer in specified base to the output channel.
     * @param x int: Integer to print.
     * @param base int (default DECIMAL): Base for number representation.
     */
	void print(int x, int base = DECIMAL);

    /**
     * Prints an unsigned integer in specified base to the output channel.
     * @param x unsigned: Unsigned integer to print.
     * @param base int (default DECIMAL): Base for number representation.
     */
	void print(unsigned x, int base = DECIMAL);

    /**
     * Prints a pointer in hexadecimal format to the output channel.
     * @param p void*: Pointer to print.
     */
	void print(void* p);

private:
	OutputChannel& channel;

};

#endif
