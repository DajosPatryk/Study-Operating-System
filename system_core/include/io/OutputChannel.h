#ifndef OutputChannel_h
#define OutputChannel_h

/**
 * Abstract class representing an output channel.
 *
 * This class includes a pure virtual function 'write', making it abstract.
 * Special characters such as newline, carriage return, backspace need to be properly handled.
 */
class OutputChannel {
public:
    /**
     * Pure virtual function to write data to the output channel.
     * Must be implemented by derived classes.
     * @param data const char*: Data to be written.
     * @param size int: Number of characters to write.
     * @return int: Number of characters written.
     */
	virtual int write(const char* data, int size) = 0;

    /**
     * Convenience method to write a single character.
     * Utilizes the 'write' method for actual output.
     * @param c char: Character to write.
     * @return int: Number of characters written (always 1).
     */
   	int write(char c) {
		return write(&c, sizeof(c));
	}

    /**
     * Pure virtual function to display a blue screen with an error message.
     * Must be implemented by derived classes.
     * @param error const char*: Error message to display.
     */
	virtual void blueScreen(const char* error) = 0;
};

#endif
