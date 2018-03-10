#ifndef	MOTORS_H
#define MOTORS_H

#define FORWARD 1
#define BACKWARD 0

#include "gpioDevice.h"

namespace micromouse {
	
class MotorSystem {
	
public:
	MotorSystem(GpioDevice* leftDirPin,
			unsigned int leftStepsMemLoc,
			unsigned int leftCyclesMemLoc,
			GpioDevice* rightDirPin,
			unsigned int rightStepsMemLoc,
			unsigned int rightCyclesMemLoc);
			
	void drive(unsigned int stepsLeft,
				unsigned int cyclesLeft,
				unsigned int directionLeft,
				unsigned int stepsRight,
				unsigned int cyclesRight,
				unsigned int directionRight);
	
	unsigned int getStepsLeft();
	unsigned int getStepsRight();
	
private:
	GpioDevice* _leftDirPin;
	GpioDevice* _rightDirPin;
	unsigned int _leftStepsMemLoc;
	unsigned int _leftCyclesMemLoc;
	unsigned int _rightStepsMemLoc;
	unsigned int _rightCyclesMemLoc;
	
};

}

#endif