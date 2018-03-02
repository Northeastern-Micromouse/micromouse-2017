#ifndef _MM_RGB_LED_H_
#define _MM_RGB_LED_H_

#include "gpioDevice.h"
#include <string>

namespace micromouse {

class RgbLedDevice {

public:
    RgbLedDevice(int r, int g, int b);
    void setRgb(int r, int g, int b);
    std::string getRgb();

private:
    GpioDevice r;
    GpioDevice g;
    GpioDevice b;
};

}
#endif
