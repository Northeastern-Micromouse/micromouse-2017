#include "motors.h"

namespace micromouse {
	
MotorSystem::MotorSystem(int pruFile,
							GpioDevice* leftDirPin,
							GpioDevice* rightDirPin,
							GpioDevice* enablePin):
							_pruFile(pruFile),
							_leftDirPin(leftDirPin),
							_rightDirPin(rightDirPin),
							_enablePin(enablePin) {}
			
void MotorSystem::enable() {
	this->_enablePin->setValue(0);
}

void MotorSystem::disable() {
	this->_enablePin->setValue(1);
}
			
int MotorSystem::drive(unsigned int stepsLeft,
						unsigned int usLeft,
						unsigned int directionLeft,
						unsigned int stepsRight,
						unsigned int usRight,
						unsigned int directionRight) {
							
	unsigned char data[] = {(unsigned char)(stepsLeft & 0xFF), 
							(unsigned char)((stepsLeft & 0x0000FF00) >> 8),
							(unsigned char)((stepsLeft & 0x00FF0000) >> 16),
							(unsigned char)((stepsLeft & 0xFF000000) >> 24),
							(unsigned char)((usLeft & 0x000000FF)),
							(unsigned char)((usLeft & 0x0000FF00) >> 8),
							(unsigned char)((usLeft & 0x00FF0000) >> 16),
							(unsigned char)((usLeft & 0xFF000000) >> 24),
							(unsigned char)(stepsRight & 0xFF), 
							(unsigned char)((stepsRight & 0x0000FF00) >> 8),
							(unsigned char)((stepsRight & 0x00FF0000) >> 16),
							(unsigned char)((stepsRight & 0xFF000000) >> 24),
							(unsigned char)((usRight & 0x000000FF)),
							(unsigned char)((usRight & 0x0000FF00) >> 8),
							(unsigned char)((usRight & 0x00FF0000) >> 16),
							(unsigned char)((usRight & 0xFF000000) >> 24) };
							
	if(directionLeft) {
		this->_leftDirPin->setValue(!MOTOR_INVERT_LEFT);
	}
	else {
		this->_leftDirPin->setValue(MOTOR_INVERT_LEFT);
	}
	
	if(directionRight) {
		this->_rightDirPin->setValue(!MOTOR_INVERT_RIGHT);
	}
	else {
		this->_rightDirPin->setValue(MOTOR_INVERT_RIGHT);
	}
	
	int error;
	if((error = write(this->_pruFile, data, 16)) != 16) {
		return error;
	}
	
	return 0;
}

}