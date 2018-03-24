#include "rgbLedDevice.h"
#include "gpioDevice.h"
#include <string>

namespace micromouse {

RgbLedDevice::RgbLedDevice(int rPin, int gPin, int bPin) : r(rPin), g(gPin), b(bPin) {
    //this->r = GpioDevice(r);
    //this->g = GpioDevice(g);
    //this->b = GpioDevice(b);
}

void RgbLedDevice::setRgb(int r, int g, int b) {
    this->r.setValue(r);
    this->g.setValue(g);
    this->b.setValue(b);
}

std::string RgbLedDevice::getRgb() {
    return "r: " + std::to_string(this->r.getValue()) + " " +
        "g: " + std::to_string(this->g.getValue()) + " " +
        "b: " + std::to_string(this->b.getValue());
}


}
