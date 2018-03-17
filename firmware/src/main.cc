#include <fcntl.h>
#include <iostream>

#include "i2cDevice.h"
#include "gpioDevice.h"
#include "rgbLedDevice.h"
#include "digitalPotentiometer.h"
#include "tableReader.h"
#include "adcPin.h"
#include "reflSensor.h"
#include "ledDriver.h"

int main() {
    micromouse::I2cDevice myI2C = micromouse::I2cDevice();
    //std::cout << std::hex << (int)myI2C.readByte(0x28, 0x0) << std::endl;
    //65 47 64
    //46 44 124

    //micromouse::RgbLedDevice led(64, 47, 65);
    //led.setRgb(1, 1, 1);

    //micromouse::TableReader reader("test.csv");
    //auto table = reader.parseTableCSV();

    //for (int i = 0; i < table->size(); ++i) {
    //    float val = table->at(i);
    //    std::cout << val << std::endl;
    //}

    // iioDevice 2, channel 0
    micromouse::AdcPin refl0Pin(micromouse::ADC0_IIO_DEVICE, 0);

    micromouse::LedDriver pwmChip(&myI2C, 0x40);
    pwmChip.init();

    micromouse::ReflSensor refl0("test.csv", &refl0Pin, &pwmChip, 0);
    std::cout << refl0.getDistance() << " is DISTANCE" << std::endl;
	//int pot0fd = open("/dev/spidev1.2", O_RDWR);
	//std::cout << pot0fd << std::endl;
	
	//micromouse::DigitalPotentiometer pot0(pot0fd);
	
	//std::cout << pot0.setResistance(1, 128) << std::endl;
	//std::cout << pot0.setResistance(2, 64) << std::endl;
	
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
