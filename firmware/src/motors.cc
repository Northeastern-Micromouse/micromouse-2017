#include "motors.h"

namespace micromouse {
	
MotorSystem::MotorSystem(GpioDevice* leftDirPin,
							unsigned int leftStepsMemLoc,
							unsigned int leftCyclesMemLoc,
							GpioDevice* rightDirPin,
							unsigned int rightStepsMemLoc,
							unsigned int rightCyclesMemLoc) :
							_leftStepsMemLoc(leftStepsMemLoc), 
							_leftCyclesMemLoc(leftCyclesMemLoc),
							_rightStepsMemLoc(rightStepsMemLoc),
							_rightCyclesMemLoc(rightCyclesMemLoc),
							_leftDirPin(leftDirPin), 
							_rightDirPin(rightDirPin) {
}
			
void MotorSystem::drive(unsigned int stepsLeft,
						unsigned int cyclesLeft,
						unsigned int directionLeft,
						unsigned int stepsRight,
						unsigned int cyclesRight,
						unsigned int directionRight) {
				
	// TODO
}
		
unsigned int MotorSystem::getStepsLeft() {
	// TODO
	return 1;
}

unsigned int MotorSystem::getStepsRight() {
	// TODO
	return 1;
}

}