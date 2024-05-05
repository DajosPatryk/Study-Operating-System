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
public:
    enum Color {
        BLACK = 0,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHT_GRAY,
        DARK_GRAY,
        LIGHT_BLUE,
        LIGHT_GREEN,
        LIGHT_CYAN,
        LIGHT_RED,
        LIGHT_MAGENTA,
        YELLOW,
        WHITE
    };

private:
    enum AttrMaskAndShifts {
        FGPOS   = 0,
        BGPOS   = 4,
        BLPOS   = 7,
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
        this->setForeground(fg);
        this->setBackground(bg);
        this->setBlinkState(blink);
    }

    /**
     * Sets the foreground color.
     * @param col Color: The new foreground color.
     */
    void setForeground(Color col) {
        this->val_ = this->val_ & FGCLEAR;
        this->val_ = this->val_ | (col << FGPOS);
    }

    /**
     * Sets the background color.
     * @param col Color: The new background color.
     */
    void setBackground(Color col) {
        this->val_ = this->val_ & BGCLEAR;
        this->val_ = this->val_ | ((col << BGPOS) & BLCLEAR);
    }

    /**
     * Sets the blink state.
     * @param blink bool: The new blink state (true enables blinking).
     */
    void setBlinkState(bool blink) {
        this->val_ = this->val_ & BLCLEAR;
        this->val_ = this->val_ | (blink << BLPOS);
    }

    /**
     * Sets all attributes from another CgaAttr object.
     * @param attr CgaAttr: The other CgaAttr object to copy attributes from.
     */
    void setAttr(CgaAttr attr) {
        this->setForeground(attr.getForeground());
        this->setBackground(attr.getBackground());
        this->setBlinkState(attr.getBlinkState());
    }

    /**
     * Retrieves the current foreground color.
     * @return Color: The current foreground color.
     */
    Color getForeground() {
        return (Color)(this->val_ & ~FGCLEAR);
    }

    /**
     * Retrieves the current background color.
     * @return Color: The current background color.
     */
    Color getBackground() {
        return (Color)((this->val_ & ~BGCLEAR) >> BGPOS);
    }

    /**
     * Retrieves the current blinking state..
     * @return bool: True if blinking is enabled, false otherwise.
     */
    bool getBlinkState() {
        return (bool)((this->val_ & ~BLCLEAR) >> BLPOS);
    }
};

#endif
