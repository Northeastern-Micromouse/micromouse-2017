#ifndef _MM_REFL_SENSOR
#define _MM_REFL_SENSOR

#include <vector>
#include <string>

#include "adcPin.h"
#include "ledDriver.h"


namespace micromouse {

class ReflSensor {

 public:
    ReflSensor(std::string filePath,
               LedDriver* pwmChip, int pwmChannel);
    float getDistance();

 private:
	std::string _filePath;
};

} // namespace micromouse
#endif
