#include "ledDriver.h"

namespace micromouse {

LedDriver::LedDriver(I2cDevice* i2c, unsigned char address) :
						_i2c(i2c), _address(address) {}

/**
 *	Initializes the device by taking it out of sleep mode and setting the 
 *	oscillator prescale value to its maximum.
 *	Returns 0 if an error occurred, otherwise returns 1.
 */
int LedDriver::init() {
	if(!this->_i2c->sendByte(this->_address, LED_DRIVER_MODE1, 0x01)) {
		return 0;
	}
	
	if(!this->_i2c->sendByte(this->_address, 
							LED_DRIVER_PRE_SCALE,
							LED_DRIVER_PRE_SCALE_1526HZ)) {
		return 0;
	}
	
	return 1;
}

/**
 *	Sets the intensity of the given LED to the given intensity.
 *	Intensity can be between 0 and 4096.
 *	Returns 0 if an error occurred, otherwise returns 1.
 */
int LedDriver::setIntensity(unsigned char led, unsigned int intensity) {
	return this->_i2c->sendByte(this->_address,
								LED_DRIVER_LED_OFF_L[led],
								intensity);
}

}