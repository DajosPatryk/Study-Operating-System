#ifndef CgaChannel_h
#define CgaChannel_h

#include "io/OutputChannel.h"
#include "device/CgaScreen.h"

/**
 * CgaChannel: Manages output to a CGA screen by implementing an OutputChannel interface.
 * Provides methods for text output, handling special characters, and displaying blue screens for errors.
 */
class CgaChannel: public OutputChannel, public CgaScreen {
private:
    /**
     * Calculates the length of a C-style null-terminated string.
     * @param str const char*: The string whose length is to be calculated.
     * @return int: The length of the string, not including the null terminator.
     */
    int strlen(const char* str);

public:
    /**
     * Constructor for CgaChannel, initializes the channel with default attributes.
     */
	CgaChannel();

    /**
     * Constructor for CgaChannel, initializes the channel with specific attributes.
     * @param attr CgaAttr: The attributes to initialize the channel with.
     */
	explicit CgaChannel(const CgaAttr& attr);

    /**
     * Writes data to the CGA screen.
     * @param data const char*: Pointer to the data to be written.
     * @param size int: The number of characters to write.
     * @return int: The number of characters actually written.
     */
	virtual int write(const char* data, int size);

    /**
     * Displays a blue screen with a standard error message.
     */
	void blueScreen(){ this->blueScreen("ERROR"); }

    /**
     * Displays a blue screen with a custom error message.
     * @param error const char*: The error message to display.
     */
	virtual void blueScreen(const char* error);

};

#endif
