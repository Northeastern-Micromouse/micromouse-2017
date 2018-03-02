#ifndef _MMI2C_H_
#define _MMI2C_H_

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define BUF_SIZE 64

namespace micromouse {

class I2cDevice {

public:
    I2cDevice();
    ~I2cDevice();

    void openI2C();
    void closeI2C();
    void setAddress(unsigned char address);
    void sendByte(char addr, char reg, char data);
    char readByte(char addr, char reg);
    char* readBytes(char addr, char reg, size_t size);

private:
    int i2cFile;
    char read_buf[BUF_SIZE];
    char write_buf[BUF_SIZE];
};

}
#endif
