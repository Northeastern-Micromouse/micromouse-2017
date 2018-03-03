#include "i2cDevice.h"
#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace micromouse {

I2cDevice::I2cDevice() {
    this->openI2C();
}

I2cDevice::~I2cDevice() {
    this->closeI2C();
}

int I2cDevice::openI2C() {
    std::cout << "opening i2c-2" << std::endl;
    this->i2cFile = open("/dev/i2c-2", O_RDWR);
    if (this->i2cFile < 0) {
        return 0;
	}
	
	return 1;
}

void I2cDevice::closeI2C() {
    std::cout << "closing i2c-2" << std::endl;
    close(this->i2cFile);
}

int I2cDevice::setAddress(unsigned char address) {
    std::cout << "setting slave address " << std::hex;
    std::cout << int(address) << std::endl;
    if (ioctl(this->i2cFile, I2C_SLAVE, address) < 0) {
        return 0;
    }
	
	return 1;
}

int I2cDevice::sendByte(char addr, char reg, char data) {
    this->setAddress(addr);
    this->write_buf[0] = reg;
    this->write_buf[1] = data;

    std::cout << "writing " << std::hex << int(data) << std::endl;
    if (write(this->i2cFile, this->write_buf, 2) != 2) {
        return 0;
    }
	
	return 1;
}

int I2cDevice::readByte(char addr, char reg, char* data) {
    this->write_buf[0] = reg;
    this->setAddress(addr);
    std::cout << "write reg value " << std::hex << (int)reg << std::endl;
    if (write(this->i2cFile, this->write_buf, 1) != 1) {
        return 0;
    }

    std::cout << "read byte" << std::endl;
    this->setAddress(addr);
    if (read(this->i2cFile, this->read_buf, 1) != 1) {
        return 0;
    }

    *data = this->read_buf[0];
	return 1;
}

int I2cDevice::readBytes(char addr, char reg, size_t size, char** data) {
    this->write_buf[0] = reg;
    this->setAddress(addr);
    std::cout << "write reg value " << std::hex << (int)reg << std::endl;
    if (write(this->i2cFile, this->write_buf, 1) != 1) {
        return 0;
    }

    std::cout << "read bytes" << std::endl;
    this->setAddress(addr);
    if (read(this->i2cFile, this->read_buf, size) != (int)size) {
        return 0;
    }

    *data = this->read_buf;
	return 1;
} 

}

