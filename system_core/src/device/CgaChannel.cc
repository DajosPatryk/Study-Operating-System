#include "device/CgaChannel.h"
#include "CgaScreen.cc"

CgaChannel::CgaChannel() { this -> setAttr(CgaAttr()); }
CgaChannel::CgaChannel(const CgaAttr& attr) { this->attr = attr; }

int CgaChannel::write(const char* data, int size) {
    int col, row;

    for (int i = 0; i < size; i++) {
        switch (data[i]) {
            case '\n': // Newline character - Move cursor to the beginning of the next line
                this->setCursor(0, row + 1);
                break;
            case '\r': // Carriage return - Move cursor to the beginning of the current line
                getCursor(col, row);
                this->setCursor(0, row);
                break;
            default:
                this->show(data[i]);

                getCursor(col, row);
                this->setCursor(col + 1, row);
        }
    }

    return 0;
}

void CgaChannel::blueScreen(const char* error) {
    this->clear(CgaAttr(CgaAttr::WHITE, CgaAttr::BLUE));
    this->write(error, this->strlen(error));
}

int CgaChannel::strlen(const char* str){
    int size = 0; while (str[size] != '\0') { size++; } return size;
}