#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/**
 * CgaScreen: Handles CGA screen operations including attribute management, cursor control, and display functionalities.
 */
class CgaScreen {

private:
	enum Ports  {
        INDEX = 0x3d4,
        DATA = 0x3d5
	};

	enum Cursor {
        HIGH = 14,
        LOW = 15
	};

	enum Video  {
        VIDEO_ADDRESS = 0x88000
	};

    /**
     * Fills the entire screen with a blank character using current attributes.
     */
    void fillScreen();

public:
	enum Screen {
		ROWS = 25,
		COLUMNS = 80
	};

    /**
     * Default constructor that initializes the screen with standard attributes and clears it.
     */
	CgaScreen();

    /**
     * Constructor that initializes the screen with specified attributes and clears it.
     * @param attr CgaAttr: Screen attributes to apply.
     */
	explicit CgaScreen(CgaAttr attr);

    /**
     * Clears the screen using default attributes.
     */
	void clear();

    /**
     * Clears the screen using specified attributes.
     * @param attr const CgaAttr&: Attributes to use when clearing.
     */
    void clear(const CgaAttr& attr);

    /**
     * Scrolls the screen content up by one row.
     */
	void scroll();

	/** Setter CgaAttr attribute. */
	void setAttr(const CgaAttr& attr) { this->attr = attr; }
    /** Getter CgaAttr attribute. */
	void getAttr(CgaAttr& attr) { attr = this->attr; }

    /**
     * Sets the cursor position on the screen.
     * @param column int: The column to place the cursor.
     * @param row int: The row to place the cursor.
     */
	void setCursor(int column, int row);

    /**
     * Retrieves the current cursor position from the screen.
     * @param column int&: Variable to store the cursor column.
     * @param row int&: Variable to store the cursor row.
     */
	void getCursor(int& column, int& row);


    /**
     * Displays a character at the current cursor position with specified attributes.
     * @param ch char: The character to display.
     * @param attr const CgaAttr&: The attributes to use for the character.
     */
	void show(char ch, const CgaAttr& attr){
        this->attr = attr;
        this->show(ch);
    }

    /**
     * Displays a character at the current cursor position using current screen attributes.
     * @param ch char: The character to display.
     */
	void show(char ch);

protected:
	CgaAttr attr;
	IOPort8 index = IOPort8(INDEX);
	IOPort8 data = IOPort8(DATA);
	CgaChar* screen;

};

#endif
