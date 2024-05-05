#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/**
 * CgaChar: Represents a character on the CGA display, consisting of the character itself and its display attributes.
 */
class CgaChar {

public:

    /**
     * Sets the character to be displayed.
     * @param c char: The character to display.
     */
	void setChar(char c) {
		 this->c = c; 
	}

    /**
     * Retrieves the current character.
     * @return char: The displayed character.
     */
	char getChar() {
		return this->c;
	}

    /**
     * Sets the display attributes for the character.
     * @param attr const CgaAttr&: The attributes to apply.
     */
	void setAttr(const CgaAttr& attr) {
		this->attr = attr;
	}

    /**
     * Retrieves the display attributes of the character.
     * @return CgaAttr: The current attributes of the character.
     */
	CgaAttr getAttr() {
		return this->attr;
	}

private:
    char c;
    CgaAttr attr = CgaAttr();


};

#endif

