#include "reflSensor.h"
#include "ledDriver.h"
#include <fstream>

namespace micromouse {

ReflSensor::ReflSensor(std::string filePath,
                       LedDriver* pwmChip, int pwmChannel) :
					   _filePath(filePath) {
    pwmChip->setIntensity(pwmChannel, 4095);
}

float ReflSensor::getDistance() {
	float data;
	std::ifstream adcStream;
	adcStream.open(this->_filePath);
	adcStream >> data;
	adcStream.close();
	return data;
}    

} // namespace micromouse
