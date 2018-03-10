#ifndef	DIGITAL_POTENTIOMETER_H
#define DIGITAL_POTENTIOMETER_H

#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

namespace micromouse {
	
class DigitalPotentiometer {

public:
	DigitalPotentiometer(int fd);
	
	int setResistance(unsigned char channel, unsigned char resistance);

private:
	int _fd;
};
	
}

#endif