#include "adcPin.h"
#include <iostream>
#include <fstream>
#include <string>

namespace micromouse {

AdcPin::AdcPin (int iioDeviceNum, int channel) :
    _iioDeviceNum(iioDeviceNum),
    _channel(channel) {
    this->_filePath = "/sys/bus/iio/devices/iio:device2/in_voltage" +
        std::to_string(this->_channel) + "_raw";
}

int AdcPin::getValue() {
    std::ifstream adcFile(this->_filePath);
    int value;
    adcFile >> value;
    adcFile.close();
    return value;
}


} // namespace micromouse
