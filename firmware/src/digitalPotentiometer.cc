#include "digitalPotentiometer.h"

namespace micromouse {
	
DigitalPotentiometer::DigitalPotentiometer(int fd) : _fd(fd) {}

/**
 * Sets the resistance for the given channel.
 * Channel is 1-6 for the AD5206 and resistance is 0-255.
 * Each LSB is a 39.0625ohm increase, with R = 45ohms for value = 0x00.
 */
int DigitalPotentiometer::setResistance(unsigned int channel, 
											unsigned int resistance) {
	
	// Create the 11-bit word
	unsigned int data[] = {channel, resistance};
	
	// Send the data over the SPI interface
	struct spi_ioc_transfer tr = {
		tx_buf        : (unsigned long)data,
		rx_buf        : (unsigned long)NULL,
		len           : 2,
		speed_hz      : 10000,
		delay_usecs   : 0,
		bits_per_word : 0
	};
	
	int retval = ioctl(this->_fd, SPI_IOC_MESSAGE(1), &tr);
	
	// Expected wiper settling time is 2us for the 10K variant, wait some extra
	usleep(5);
	
	return retval;
}

}