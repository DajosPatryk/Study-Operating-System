#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
		BACKGROUND_COLOR_SHIFTED_BITS = 4,
		ENABLE_BLINKING = 0b10000000,
		DISABLE_BLINKING = 0b01111111
	};


public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		BLACK = 0xb0000,
		BLUE = 0b0001,
		GREEN = 0b0010,
		CYAN = 0b0011,
		RED = 0b0100,
		MAGENTA = 0b0101,
		BROWN = 0b0110,
		LIGHT_GRAY = 0b0111,
		GRAY = 0b1000,
		LIGHT_BLUE = 0b1001,
		LIGHT_GREEN = 0b1010,
		LIGHT_CYAN = 0b1011,
		LIGHT_RED = 0b1100,
		LIGHT_MAGENTA = 0b1101,
		YELLOW = 0b1110,
		WHITE = 0b1111
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{	this->setForeground(fg);
		this->setBackground(bg);
		this->setBlinkState(blink);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		this->fg = col;

		// clear last 4 bits
		byte &= 0b11110000;

		// write foreground color to byte
		byte |= col;
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		this->bg = col;

		// clear background bits
		byte &= 0b10001111;

		char backgroundByte =
		    col << AttrMaskAndShifts::BACKGROUND_COLOR_SHIFTED_BITS;

		// clear first bit (reserved for blinking)
		backgroundByte &= 0b01111111;

		// write background byte to byte
		byte |= backgroundByte;
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		this->blink = blink;

		byte = blink ? byte | AttrMaskAndShifts::ENABLE_BLINKING
			     : byte & AttrMaskAndShifts::DISABLE_BLINKING;
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		Color fg = attr.getForeground();
		Color bg = attr.getBackground();
		bool blink = attr.getBlinkState();

		setForeground(fg);
		setBackground(bg);
		setBlinkState(blink);
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		return this->fg;
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		return this->bg;
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		return this->blink;
	}
	char asByte() { return byte; }

private:
	Color fg ;
	Color bg ;
	bool blink ;
	char byte = 0;

};

#endif
