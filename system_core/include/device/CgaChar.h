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
	void setChar(char c) { this->ch_ = c; }

    /**
     * Retrieves the current character.
     * @return char: The displayed character.
     */
	char getChar() { return this->ch_; }

    /**
     * Sets the display attributes for the character.
     * @param attr const CgaAttr&: The attributes to apply.
     */
	void setAttr(const CgaAttr& attr) { this->attr_ = attr; }

    /**
     * Retrieves the display attributes of the character.
     * @return CgaAttr: The current attributes of the character.
     */
	CgaAttr getAttr() { return this->attr_; }

private:
    char ch_;
    CgaAttr attr_;

};

#endif

