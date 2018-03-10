#include <fcntl.h>
#include <iostream>

#include "i2cDevice.h"
#include "gpioDevice.h"
#include "rgbLedDevice.h"
#include "digitalPotentiometer.h"

int main() {
    //micromouse::I2cDevice myI2C = micromouse::I2cDevice();
    //std::cout << std::hex << (int)myI2C.readByte(0x28, 0x0) << std::endl;
    //65 47 64
    //46 44 124

    micromouse::RgbLedDevice led(64, 47, 65);
    led.setRgb(1, 1, 1);
	
	int pot0fd = open("/dev/spidev1.2", O_RDWR);
	std::cout << pot0fd << std::endl;
	
	micromouse::DigitalPotentiometer pot0(pot0fd);
	
	std::cout << pot0.setResistance(1, 128) << std::endl;
	std::cout << pot0.setResistance(2, 64) << std::endl;
	
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
}
