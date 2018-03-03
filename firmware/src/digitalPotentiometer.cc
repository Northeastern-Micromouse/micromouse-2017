#include "digitalPotentiometer.h"

namespace micromouse {
	
DigitalPotentiometer::DigitalPotentiometer(unsigned char sdiPin, 
											unsigned char clkPin, 
											unsigned char csPin) {
	this->_sdi = new GpioDevice(sdiPin);
	this->_clk = new GpioDevice(clkPin);
	this->_cs = new GpioDevice(csPin);	
}

DigitalPotentiometer::~DigitalPotentiometer() {
	delete _sdi;
	delete _clk;
	delete _cs;
}

/**
 * Initializes the digital potentiometer interface hardware.
 */
void DigitalPotentiometer::init() {
	this->_sdi->setDirection(OUT);
	this->_sdi->setValue(0);
	
	this->_clk->setDirection(OUT);
	this->_clk->setValue(0);
	
	this->_cs->setDirection(OUT);
	this->_cs->setValue(1);
}

/**
 * Sets the resistance for the given channel.
 * Channel is 1-6 for the AD5206 and resistance is 0-255.
 * Each LSB is a 39.0625ohm increase, with R = 45ohms for value = 0x00.
 */
void DigitalPotentiometer::setResistance(unsigned char channel, 
											unsigned char resistance) {
	// First, drive CS low
	this->_cs->setValue(0);
	usleep(1);
	
	unsigned int data = (((unsigned int)channel - 1) << 8) | resistance;
	
	// Shift the bits into the device on the rising edge
	for(int i = 10; i>=0; i--) {
		this->_sdi->setValue((data & (1 << i)) >> i);

		this->_clk->setValue(1);
		usleep(1);
		this->_clk->setValue(0);
		usleep(1);
	}
	
	this->_cs->setValue(1);
	
	// Expected wiper settling time is 2us for the 10K variant, wait some extra
	usleep(5);
}

}