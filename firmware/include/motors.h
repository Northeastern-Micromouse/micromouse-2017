#ifndef	MOTORS_H
#define MOTORS_H

#include <fcntl.h>
#include <unistd.h>

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARD 0

#define MOTOR_INVERT_LEFT 0
#define MOTOR_INVERT_RIGHT 1

#include "gpioDevice.h"

namespace micromouse {
	
class MotorSystem {
	
public:
	MotorSystem(int pruFile,
				GpioDevice* leftDirPin,
				GpioDevice* rightDirPin,
				GpioDevice* enablePin);
				
	void enable();
	void disable();
	int drive(unsigned int stepsLeft,
				unsigned int usLeft,
				unsigned int directionLeft,
				unsigned int stepsRight,
				unsigned int usRight,
				unsigned int directionRight);
	
private:
	int _pruFile;
	GpioDevice* _leftDirPin;
	GpioDevice* _rightDirPin;
	GpioDevice* _enablePin;
};

}

#endif