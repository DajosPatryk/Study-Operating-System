#include "device/CgaAttr.h"
#include "iostream"

extern "C" int main()
{
    CgaAttr pixel = CgaAttr(CgaAttr::WHITE, CgaAttr::LIGHT_MAGENTA, true);
    CgaAttr::Color bg = pixel.getBackground();

    std::cout << bg << std::endl;

    return 0;
}
