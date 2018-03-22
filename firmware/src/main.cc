#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "robot.h"

int main() {
    //micromouse::I2cDevice myI2C = micromouse::I2cDevice();
    //std::cout << std::hex << (int)myI2C.readByte(0x28, 0x0) << std::endl;
    //65 47 64
    //46 44 124
	/*
    micromouse::RgbLedDevice led(64, 47, 65);
    led.setRgb(1, 1, 1);
	
	micromouse::I2cDevice i2c;
	std::cout << "Opening: " << i2c.openI2C() << std::endl;
	
	micromouse::LedDriver leds(&i2c, LED_DRIVER_DEFAULT_ADDRESS);
	std::cout << "Init: " << leds.init() << std::endl;
	std::cout << "Set: " << leds.setIntensity(0, 4095) << std::endl;
	*/
	
	
	micromouse::Robot robot;
	robot.init();
	
	while(1) {
		robot.turn(1, 100);
		usleep(1000000);
		robot.pid_drive(180, 100);
		usleep(1000000);
	}
	
   
	return 0;
}
