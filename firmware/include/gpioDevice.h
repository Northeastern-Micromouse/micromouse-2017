#ifndef _MMGPIO_H_
#define _MMGPIO_H_

#include <iostream>
#include <fstream>
#include <string>

#define OUT 1
#define IN	0

namespace micromouse {

class GpioDevice {

public:
    GpioDevice(int pin);
    ~GpioDevice();

    void setDirection(int direction);
    void setValue(int value);

    int getDirection();
    int getValue();

private:
    int pin;
    int direction;
    int value;

};

}
#endif
