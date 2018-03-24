#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "i2cDevice.h"

namespace micromouse {
	
#define LED_DRIVER_DEFAULT_ADDRESS	0x40

// Registers
// Note that for all registers ending in "_L" are those representing a low byte
// and the high byte is at the next address (i.e., <reg>_L+1)
#define LED_DRIVER_MODE1			0x00
#define LED_DRIVER_MODE2			0x01
#define LED_DRIVER_SUBADR1			0x02
#define LED_DRIVER_SUBADR2			0x03
#define LED_DRIVER_SUBADR3			0x04
#define LED_DRIVER_ALLCALLADR		0x05
#define LED_DRIVER_LED0_ON_L		0x06
#define LED_DRIVER_LED0_OFF_L		0x08
#define LED_DRIVER_LED1_ON_L		0x0A
#define LED_DRIVER_LED1_OFF_L		0x0C
#define LED_DRIVER_LED2_ON_L		0x0E
#define LED_DRIVER_LED2_OFF_L		0x10
#define LED_DRIVER_LED3_ON_L		0x12
#define LED_DRIVER_LED3_OFF_L		0x14
#define LED_DRIVER_LED4_ON_L		0x16
#define LED_DRIVER_LED4_OFF_L		0x18
#define LED_DRIVER_LED5_ON_L		0x1A
#define LED_DRIVER_LED5_OFF_L		0x1C
#define LED_DRIVER_LED6_ON_L		0x1E
#define LED_DRIVER_LED6_OFF_L		0x20
#define LED_DRIVER_LED7_ON_L		0x22
#define LED_DRIVER_LED7_OFF_L		0x24
#define LED_DRIVER_LED8_ON_L		0x26
#define LED_DRIVER_LED8_OFF_L		0x28
#define LED_DRIVER_LED9_ON_L		0x2A
#define LED_DRIVER_LED9_OFF_L		0x2C
#define LED_DRIVER_LED10_ON_L		0x2E
#define LED_DRIVER_LED10_OFF_L		0x30
#define LED_DRIVER_LED11_ON_L		0x32
#define LED_DRIVER_LED11_OFF_L		0x34
#define LED_DRIVER_LED12_ON_L		0x36
#define LED_DRIVER_LED12_OFF_L		0x38
#define LED_DRIVER_LED13_ON_L		0x3A
#define LED_DRIVER_LED13_OFF_L		0x3C
#define LED_DRIVER_LED14_ON_L		0x3E
#define LED_DRIVER_LED14_OFF_L		0x40
#define LED_DRIVER_LED15_ON_L		0x42
#define LED_DRIVER_LED15_OFF_L		0x44
#define LED_DRIVER_ALL_LED_ON_L		0xFA
#define LED_DRIVER_ALL_LED_OFF_L	0xFC
#define LED_DRIVER_PRE_SCALE		0xFE
#define LED_DRIVER_TESTMODE			0xFF

// Constants
#define LED_DRIVER_PRE_SCALE_1526HZ	0x03
#define LED_DRIVER_PRE_SCALE_24HZ	0xFF
const unsigned char LED_DRIVER_LED_OFF_L[] = {
	LED_DRIVER_LED0_OFF_L,
	LED_DRIVER_LED1_OFF_L,
	LED_DRIVER_LED2_OFF_L,	
	LED_DRIVER_LED3_OFF_L,
	LED_DRIVER_LED4_OFF_L,
	LED_DRIVER_LED5_OFF_L,
	LED_DRIVER_LED6_OFF_L,
	LED_DRIVER_LED7_OFF_L,
	LED_DRIVER_LED8_OFF_L,
	LED_DRIVER_LED9_OFF_L,
	LED_DRIVER_LED10_OFF_L,
	LED_DRIVER_LED11_OFF_L,
	LED_DRIVER_LED12_OFF_L,
	LED_DRIVER_LED13_OFF_L,
	LED_DRIVER_LED14_OFF_L,
	LED_DRIVER_LED15_OFF_L
};
	
class LedDriver {
	
public:
	LedDriver(I2cDevice* i2c, unsigned char address);
	int init();
	int setIntensity(unsigned char led, unsigned int intensity);
	
private:
	I2cDevice* _i2c;
	unsigned char _address;
};
	
}

#endif