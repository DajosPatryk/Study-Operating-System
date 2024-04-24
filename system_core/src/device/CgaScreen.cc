#include "device/CgaScreen.h"
#include "lib/tools.h"

CgaScreen::CgaScreen(){ this->clear(); }

CgaScreen::CgaScreen(CgaAttr attr){
    this->clear();
    this->setAttr(attr);
}

void CgaScreen::fillScreen(){
    this->screen = (CgaChar*)VIDEO_ADDRESS;

    for (int pos = 0; pos < ROWS * COLUMNS; pos++) {
        this->screen[pos].setChar(' ');
        this->screen[pos].setAttr(this->attr);
    }
}

void CgaScreen::clear(){
    this->setAttr(CgaAttr());
    this->fillScreen();
    this->setCursor(0, 0);
}

void CgaScreen::clear(const CgaAttr& attr){
    this->setAttr(attr);
    this->fillScreen();
    this->setCursor(0, 0);
}

void CgaScreen::scroll(){
    this->screen = (CgaChar*)VIDEO_ADDRESS;

    // Shifting screen one line up using memory copy
    memcpy(
            screen,
            screen + COLUMNS,
            (ROWS - 1) * COLUMNS * sizeof(CgaChar)
    );

    // Clearing last line
    int lastIndex = (ROWS - 1) * COLUMNS;
    for (int col = 0; col < COLUMNS; col++){
        this->screen[lastIndex + col].setChar(' ');
        this->screen[lastIndex + col].setAttr(CgaAttr());
    }
}

void CgaScreen::setCursor(int column, int row){
    while (column >= COLUMNS) { column = column - COLUMNS; row++; } // Column overflow
    while (row    >= ROWS)    { row--; this->scroll();            } // Row overflow
    while (column <  0)       { column = column + COLUMNS; row--; } // Column underflow
    row = (row    <  0)?      0 : row;                              // Row underflow

    // Setting data
    unsigned pos = row * COLUMNS + column;
    char posLow  = pos;
    char posHigh = pos >> 8;

    // Writing data
    this->index.write(LOW);
    this->index.write(HIGH);
    this->data.write(posLow);
    this->data.write(posHigh);
}

void CgaScreen::getCursor(int& column, int& row){
    // Reading data
    unsigned posLow  = this->data.read();
    unsigned posHigh = this->data.read();
    unsigned pos;

    // Setting offset
    this->index.write(LOW);
    this->index.write(HIGH);

    // Retrieving data
    pos    = posHigh;
    pos    = pos << 8;
    pos    = pos | posLow;
    row    = (int)(pos / COLUMNS);
    column = (int)(pos % COLUMNS);
}

void CgaScreen::show(char ch){
    int col, row;
    this->getCursor(col, row);
    this->screen = (CgaChar*)VIDEO_ADDRESS;

    // Setting char
    this->screen[row * COLUMNS + col].setAttr(attr);
    this->screen[row * COLUMNS + col].setChar(ch);
    this->setCursor(col + 1, row);
}