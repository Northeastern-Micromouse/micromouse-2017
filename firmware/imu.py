import time
import smbus

SAMPLES = 30

# Open I2C bus
bus = smbus.SMBus(2)

# Initialization
bus.write_byte_data(0x28, 0x3D, 0x00)
bus.write_byte_data(0x28, 0x3F, 0x20)
time.sleep(1)
bus.write_byte_data(0x28, 0x3E, 0x00)
time.sleep(1)
bus.write_byte_data(0x28, 0x07, 0x00)
time.sleep(1)
bus.write_byte_data(0x28, 0x3F, 0x00)
time.sleep(1)
bus.write_byte_data(0x28, 0x3D, 0x0C)
time.sleep(1)

while True:
    average = 0;
    for x in range(0, SAMPLES):
        headingBytes = bus.read_i2c_block_data(0x28, 0x1A, 2)
        average += float((headingBytes[1] << 8) | headingBytes[0]) / 16.0
        time.sleep(0.005)
    
    with open("/home/debian/sensors/imu", "w") as f:
        f.write(str(average / float(SAMPLES)))
        f.close()