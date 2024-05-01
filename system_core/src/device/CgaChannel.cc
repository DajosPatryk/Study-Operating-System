#include "include/device/CgaChannel.h"

CgaChannel::CgaChannel() {}

CgaChannel::CgaChannel(const CgaAttr &attr) { this->attr = attr; }

int CgaChannel::write(const char *data, int size) {
	int column, row;
	getCursor(column, row);

	int writtenCharacters = 0;

	for (int i = 0; i < size; i++) {
		char c = data[i];

		switch (c) {
		case '\n':
			lastLineLength = column;
			row++;

		case '\r':
			column = 0;
			break;

		default:
			setCursor(column, row);
			show(c);

			// check if line is full
			if (++column == Screen::COLUMNS) {
				lastLineLength = 0;
				column = 0;
				row++;
			}
		}

		// check if screen is full
		if (row >= Screen::ROWS) {
			column = 0;
			row = Screen::ROWS - 1;
			scroll();
		}

		writtenCharacters++;
	}

	// set cursor after written content
	setCursor(column, row);

	return writtenCharacters;
}

void CgaChannel::blueScreen(const char *error) {
	attr.setBackground(CgaAttr::Color::BLUE);
	attr.setForeground(CgaAttr::Color::WHITE);
	attr.setBlinkState(false);

	setCursor(0, 0);
	clear(attr);
	setCursor(0, 0);

	int i = 0;

	// find first NULL char
	while (error[i++] != 0)
		;
	// now write error message
	write(error, i - 1);
}