#include "reflSensor.h"
#include "tableReader.h"
#include "adcPin.h"
#include "ledDriver.h"

#include <string>
#include <vector>
#include <iostream>

#define NUM_ADC_READING 200

namespace micromouse {

ReflSensor::ReflSensor(std::string filepath, AdcPin* adcPin,
                       LedDriver* pwmChip, int pwmChannel) :
    _lookupTable(TableReader(filepath).parseTableCSV()),
    _adcPin(adcPin) {
    TableReader reader(filepath);
    _lookupTable = reader.parseTableCSV();
    pwmChip->init();
    std::cout << "brightness: " << reader.getBrightness() << std::endl;
    pwmChip->setIntensity(pwmChannel, reader.getBrightness());
}

float ReflSensor::getDistance() {
    int adcValue = 0;
    for (int i = 0; i < NUM_ADC_READING; ++i) {
        adcValue += _adcPin->getValue();
    }

    adcValue /= NUM_ADC_READING;
    std::cout << "Refl adc read: " << adcValue << std::endl;
    std::cout << "size: " << _lookupTable->size() << std::endl;
    /*
    if (adcValue < this->_minValue) {
        return this->_lookupTable->at(0);
    }
    if (adcValue >= this->_minValue + this->_lookupTable->size()) {
        return this->_lookupTable->at(this->_lookupTable->size() - 1);
    }
    */
    return this->_lookupTable->at(adcValue);
}    

} // namespace micromouse
