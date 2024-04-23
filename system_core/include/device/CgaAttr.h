#ifndef CgaAttr_h
#define CgaAttr_h

class CgaAttr {
public:
    enum Color {
        BLACK,
        WHITE,
        BLUE,
        BROWN,
        CYAN,
        GRAY,
        GREEN,
        RED,
        YELLOW,
        LIGHT_BLUE,
        LIGHT_CYAN,
        LIGHT_GRAY,
        LIGHT_GREEN,
        LIGHT_MAGENTA,
        LIGHT_RED,
        MAGENTA
    };

private:
	enum AttrMaskAndShifts {
        FGPOS = 0,
        BGPOS = 4,
        BLPOS = 7,
        FGCLEAR = 0xF0, // 11110000
        BGCLEAR = 0x8F, // 10001111
        BLCLEAR = 0x7F, // 01111111
	};
    char val_;

public:

    /**
     * Constructor for CgaAttr, initializing with optional parameters.
     * @param fg Color (default WHITE): foreground color.
     * @param bg Color (default BLACK): background color.
     * @param blink bool (default false): blink state.
     */
    explicit CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false) {

    }

    /**
     * Sets the foreground color.
     * @param col Color: The new foreground color.
     */
    void setForeground(Color col) {

    }

    /**
     * Sets the background color.
     * @param col Color: The new background color.
     */
    void setBackground(Color col) {

    }

    /**
     * Sets the blink state.
     * @param blink bool: The new blink state (true enables blinking).
     */
    void setBlinkState(bool blink) {

    }

    /**
     * Sets all attributes from another CgaAttr object.
     * @param attr CgaAttr: The other CgaAttr object to copy attributes from.
     */
    void setAttr(CgaAttr attr) {

    }

    /**
     * Retrieves the current foreground color.
     * @return Color: The current foreground color.
     */
    Color getForeground() {

    }

    /**
     * Retrieves the current background color.
     * @return Color: The current background color.
     */
    Color getBackground() {

    }

    /**
     * Retrieves the current blinking state..
     * @return bool: True if blinking is enabled, false otherwise.
     */
    bool getBlinkState() {

    }
};

#endif
