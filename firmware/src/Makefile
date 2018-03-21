INCLUDE_DIR=../include
CC=g++
CFLAGS=-I$(INCLUDE_DIR)

ODIR=obj
LDIR=../lib

_DEPS=i2cDevice.h \
	  gpioDevice.h \
	  rgbLedDevice.h \
	  tableReader.h \
	  digitalPotentiometer.h \
	  ledDriver.h \
	  motors.h \
	  adcPin.h \
	  reflSensor.h

DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ=i2cDevice.o \
	 main.o \
	 gpioDevice.o \
	 rgbLedDevice.o \
	 tableReader.o \
	 digitalPotentiometer.o \
	 ledDriver.o \
	 motors.o \
	 adcPin.o \
	 reflSensor.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCLUDE_DIR)/*~
	rm main -f
