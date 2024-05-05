#include "../include/device/CgaScreen.h"

CgaScreen::CgaScreen() { setCursor(0, 0); }
CgaScreen::CgaScreen(CgaAttr attr) : attr(attr) { CgaScreen(); }

void CgaScreen::clear(CgaAttr attr) {
	setCursor(0, 0);
	int startColumn = 0;

	for (int i = startColumn; i < Screen::COLUMNS * Screen::ROWS; i++) {
		int column = i % Screen::COLUMNS;
		int row    = i / Screen::COLUMNS;
		if (row    >= Screen::ROWS) return;

		setCursor(column, row);
		show(0, attr);
	}

	setCursor(0, 0);
}

void CgaScreen::clear() { clear(defaultCgaAttr); }

void CgaScreen::scroll() {
    // Caches content from line 1 to "Screen::ROWS - 1" in buffer "content", doesn't copy last line "Screen::COLUMNS * 2"
	memcpy(
            (void *)content,
	       (void *)(Video::CGA_START + Screen::COLUMNS * 2),
	       sizeof(content) - Screen::COLUMNS * 2
    );

	// Writes buffer "content" to address Video::CGA_START
	memcpy((void *)Video::CGA_START, (void *)content, sizeof(content));

	int column, row;
	getCursor(column, row);
	if (row != 0) setCursor(0, row - 1);
}

void CgaScreen::setCursor(int column, int row) {
	// Source: wiki.osdev.org/Text_Mode_Cursor
	unsigned short position = row * Screen::COLUMNS + column;

	index.write(LOW);
	data.write((unsigned char)(position & 0xff));   // Writes last 8 bits of 16-bit short "position" in register 15 as an 8-bit char
	index.write(HIGH);
	data.write((unsigned char)(position >> 8) & 0xff);  // Writes first 8 bits of 16-bit short "position" in register 14 as an 8-bit char
}

void CgaScreen::getCursor(int &column, int &row) {
	// Source: wiki.osdev.org/Text_Mode_Cursor
	unsigned short position;

	index.write(LOW);
	position = data.read(); // Assigns read data to position first
	index.write(HIGH);
	position |= (unsigned short)(data.read() << 8); // Writes last 8 bits of read data as first 8 bits of 16-bit short pos

	column = position % Screen::COLUMNS;
	row    = position / Screen::COLUMNS;
}

void CgaScreen::show(char ch, const CgaAttr &attr) {
	int column = 0, row = 0;
	getCursor(column, row);

	char *base = (char *)(Video::CGA_START + (row * Screen::COLUMNS + column) * 2);
	*base++    = int(ch);
	*base      = ((CgaAttr)attr).asByte(); // Writes attribute byte to VRAM
}