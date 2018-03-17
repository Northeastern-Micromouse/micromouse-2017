#ifndef _MM_REFL_SENSOR
#define _MM_REFL_SENSOR

#include <vector>
#include <string>

#include "adcPin.h"
#include "ledDriver.h"


namespace micromouse {

class ReflSensor {

 public:
    ReflSensor(std::string filePath, AdcPin* adcPin,
               LedDriver* pwmChip, int pwmChannel, int brightness);
    float getDistance();

 private:
    std::vector<float>* _lookupTable;
    int _minValue;
    AdcPin* _adcPin;
};

} // namespace micromouse
#endif