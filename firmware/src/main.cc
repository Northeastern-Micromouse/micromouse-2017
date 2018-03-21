#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "i2cDevice.h"
#include "gpioDevice.h"
#include "rgbLedDevice.h"
#include "digitalPotentiometer.h"
#include "tableReader.h"
#include "adcPin.h"
#include "reflSensor.h"
#include "ledDriver.h"
#include "motors.h"

int main() {
    micromouse::I2cDevice myI2C = micromouse::I2cDevice();
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
	
	int pru0_file = open("/dev/rpmsg_pru30", O_RDWR);
    if (pru0_file < 0) {
		printf("Error opening PRU0 RPMSG file.\n");
        return pru0_file;
	}
	
	micromouse::GpioDevice leftMotorDirPin(112);
	micromouse::GpioDevice rightMotorDirPin(113);
	micromouse::GpioDevice enableMotorPin(114);
	
	leftMotorDirPin.setDirection(GPIO_OUT);
	rightMotorDirPin.setDirection(GPIO_OUT);
	enableMotorPin.setDirection(GPIO_OUT);
	
	micromouse::MotorSystem motorSystem(pru0_file,  
										&leftMotorDirPin, 
										&rightMotorDirPin, 
										&enableMotorPin);
	
	motorSystem.enable();
	
	motorSystem.drive(16000, 200, MOTOR_FORWARD, 16000, 200, MOTOR_FORWARD);
	
	motorSystem.disable();
	
	while(read(pru0_file, NULL, 2) != 2) {
		
	}
    /*
    micromouse::GpioDevice r(64);
    micromouse::GpioDevice g(47);
    micromouse::GpioDevice b(65);
    r.setValue(1);
    std::cout << "r " << r.getValue() << std::endl;
    g.setValue(1);
    std::cout << "g " << g.getValue() << std::endl;
    b.setValue(0);
    std::cout << "b " << b.getValue() << std::endl;
    */
	
	return 0;
}
