
BASE_ADC_FILEPATH = "/sys/bus/iio/devices/iio:device2/in_voltage"
BASE_CALIBRATION_FILEPATH = "/home/debian/calibration/sensor"
BASE_OUTPUT_FILEPATH = "/home/debian/sensors/sensor"
NUM_SENSORS = 6
NUM_SAMPLES = 200

data = []

for i in range(0,6):
    with open(BASE_CALIBRATION_FILEPATH + str(i) + ".csv") as f:
        data.append(f.readlines())
        data[i] = [float(x.strip()) for x in data[i]]

while True:
    for sensor in range(0,6):
        average = 0
        for sample in range(0, NUM_SAMPLES):
            value = 0
            with open(BASE_ADC_FILEPATH + str(sensor) + "_raw") as f:
                value = f.readline()
                average += data[sensor][int(value)+1]
               
        average /= NUM_SAMPLES
        with open(BASE_OUTPUT_FILEPATH + str(sensor), "w") as f:
            f.write(str(average))
            f.close()
            

