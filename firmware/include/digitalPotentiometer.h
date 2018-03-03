#ifndef	DIGITAL_POTENTIOMETER_H
#define DIGITAL_POTENTIOMETER_H

#include <unistd.h>
#include "gpioDevice.h"

namespace micromouse {
	
class DigitalPotentiometer {

public:
	DigitalPotentiometer(unsigned char sdiPin, 
							unsigned char clkPin, 
							unsigned char csPin);
	~DigitalPotentiometer();
	
	void init();
	void setResistance(unsigned char channel, unsigned char resistance);

private:
	GpioDevice* _sdi;
	GpioDevice* _clk;
	GpioDevice* _cs;
};
	
}

#endif