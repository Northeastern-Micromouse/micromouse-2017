#include "reflSensor.h"
#include "tableReader.h"
#include "adcPin.h"
#include "ledDriver.h"

#include <string>
#include <vector>
#include <iostream>

namespace micromouse {

ReflSensor::ReflSensor(std::string filepath, AdcPin* adcPin,
                       LedDriver* pwmChip, int pwmChannel) :
    _lookupTable(TableReader(filepath).parseTableCSV()),
    _adcPin(adcPin) {
    TableReader reader(filepath);
    _lookupTable = reader.parseTableCSV();
    _minValue = reader.getMinValue();
    pwmChip->init();
    pwmChip->setIntensity(pwmChannel, reader.getBrightness());
}

float ReflSensor::getDistance() {
    int adcValue = this->_adcPin->getValue();
    std::cout << "Refl adc read: " << adcValue << std::endl;
    std::cout << "Refl minValue: " << _minValue << std::endl;
    std::cout << "size: " << _lookupTable->size() << std::endl;
    if (adcValue < this->_minValue) {
        return this->_lookupTable->at(0);
    }
    if (adcValue >= this->_minValue + this->_lookupTable->size()) {
        return this->_lookupTable->at(this->_lookupTable->size() - 1);
    }
    return this->_lookupTable->at(adcValue - this->_minValue);
    std::cout << "refl distance read: ";
}    

} // namespace micromouse
