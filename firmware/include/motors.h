#ifndef	MOTORS_H
#define MOTORS_H

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARD 0

#define MOTOR_INVERT_LEFT 0
#define MOTOR_INVERT_RIGHT 1

#include "gpioDevice.h"

namespace micromouse {
	
class MotorSystem {
	
public:
	MotorSystem(std::string pruFile,
				GpioDevice* leftDirPin,
				GpioDevice* rightDirPin,
				GpioDevice* enablePin);
				
	void enable();
	void disable();
	int drive(unsigned int stepsLeft,
				unsigned int stepsRight,
				unsigned int periodLeft,
				unsigned int periodRight,
				bool directionLeft,
				bool directionRight,
				unsigned int timeout);
	
private:
	std::string _pruFile;
	GpioDevice* _leftDirPin;
	GpioDevice* _rightDirPin;
	GpioDevice* _enablePin;
};

}

#endif