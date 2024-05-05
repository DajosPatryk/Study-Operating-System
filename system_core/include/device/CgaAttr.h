#ifndef CgaAttr_h
#define CgaAttr_h

/**
 * CgaAttr is class of a singular CGA pixel.
 * |7|6 5 4|3|2 1 0|
 * |B|R G B|I|R G B|
 *
 * 7: Blinking Foreground.
 * 6, 5, 4: Background Color.
 * 3: Intensity Foreground.
 * 2, 1, 0: Foreground Color.
 */
class CgaAttr {
private:
	enum AttrMaskAndShifts {
        FGPOS            = 0,
        BGPOS            = 4,
        FGCLEAR          = 0b11110000,
        BGCLEAR          = 0b10001111,
        BLCLEAR          = 0b01111111,
		ENABLE_BLINKING  = 0b10000000,
		DISABLE_BLINKING = 0b01111111
	};


public:
	enum Color {
		BLACK         = 0xb0000,
		BLUE          = 0b0001,
		GREEN         = 0b0010,
		CYAN          = 0b0011,
		RED           = 0b0100,
		MAGENTA       = 0b0101,
		BROWN         = 0b0110,
		LIGHT_GRAY    = 0b0111,
		GRAY          = 0b1000,
		LIGHT_BLUE    = 0b1001,
		LIGHT_GREEN   = 0b1010,
		LIGHT_CYAN    = 0b1011,
		LIGHT_RED     = 0b1100,
		LIGHT_MAGENTA = 0b1101,
		YELLOW        = 0b1110,
		WHITE         = 0b1111
	};


    /**
    * Constructor for CgaAttr, initializing with optional parameters.
    * @param fg Color (default WHITE): foreground color.
    * @param bg Color (default BLACK): background color.
    * @param blink bool (default false): blink state.
    */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false) {
        this->setForeground(fg);
		this->setBackground(bg);
		this->setBlinkState(blink);
	}

    /**
     * Sets the foreground color.
     * @param col Color: The new foreground color.
     */
	void setForeground(Color col) {
		this->fg = col;
		byte &= AttrMaskAndShifts::FGCLEAR;
		byte |= col;
	}

    /**
     * Sets the background color.
     * @param col Color: The new background color.
     */
	void setBackground(Color col) {
		this->bg = col;
		byte &= AttrMaskAndShifts::BGCLEAR;
		char backgroundByte = col << AttrMaskAndShifts::BGPOS;
		backgroundByte &= AttrMaskAndShifts::BLCLEAR;
		byte |= backgroundByte;
	}

    /**
     * Sets the blink state.
     * @param blink bool: The new blink state (true enables blinking).
     */
	void setBlinkState(bool blink) {
		this->blink = blink;
		byte = blink ? byte | AttrMaskAndShifts::ENABLE_BLINKING : byte & AttrMaskAndShifts::DISABLE_BLINKING;
	}

    /**
     * Sets all attributes from another CgaAttr object.
     * @param attr CgaAttr: The other CgaAttr object to copy attributes from.
     */
	void setAttr(CgaAttr attr) {
		Color fg = attr.getForeground();
		Color bg = attr.getBackground();
		bool blink = attr.getBlinkState();

		setForeground(fg);
		setBackground(bg);
		setBlinkState(blink);
	}

    /**
     * Retrieves the current foreground color.
     * @return Color: The current foreground color.
     */
	Color getForeground() {
		return this->fg;
	}

    /**
     * Retrieves the current background color.
     * @return Color: The current background color.
     */
	Color getBackground() {
		return this->bg;
	}

    /**
     * Retrieves the current blinking state.
     * @return bool: True if blinking is enabled, false otherwise.
     */
	bool getBlinkState() {
		return this->blink;
	}

    /**
     * Retrieves the current Attr as byte.
     * @return char: Byte value of Attr.
     */
	char asByte() { return byte; }

private:
	Color fg ;
	Color bg ;
	bool blink ;
	char byte = 0;

};

#endif
