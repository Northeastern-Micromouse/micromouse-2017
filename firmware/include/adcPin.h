#ifndef _MM_ADC_PIN_H
#define _MM_ADC_PIN_H

#include <string>

namespace micromouse {

static const int ADC0_IIO_DEVICE = 2;

class AdcPin {

 public:
    AdcPin(int iioDeviceNum, int channel);
    int getValue();

 private:
    int _iioDeviceNum;
    int _channel;
    std::string _filePath;
};





} // namespace micromouse
#endif
