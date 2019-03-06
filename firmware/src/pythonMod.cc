#include <boost/python.hpp>
#include "pythonMod.h"
#include "i2cDevice.h"
#include <iostream>

using namespace boost::python;

BOOST_PYTHON_MODULE(pythonMod) {
        class_<micromouse::I2cDevice>("I2cDevice")
            .def("openI2C", &micromouse::I2cDevice::openI2C)
            .def("closeI2C", &micromouse::I2cDevice::closeI2C)
            .def("setAddress", &micromouse::I2cDevice::setAddress)
            .def("sendByte", &micromouse::I2cDevice::sendByte)
            .def("readByte", &micromouse::I2cDevice::readByte)
            .def("readBytes", &micromouse::I2cDevice::readBytes);
}
