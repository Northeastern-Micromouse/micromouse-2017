#include "imu.h"

#include <unistd.h>

namespace micromouse {

IMU::IMU(I2cDevice* i2c, char address) {
    i2c_ = i2c;
    address_ = address;
}

int IMU::ReadThreeAxisData(
    char baseAddress, 
    float scaleFactor,
    float& x,
    float& y,
    float& z) {
        
    char data[6];
    int error = i2c_->readBytes(address_,
                                baseAddress,
                                6 * sizeof(char),
                                data);
                                                     
    if (error) {
        return error;
    }
       
    x = ((data[1] << 8) | data[0]) * scaleFactor;
    y = ((data[3] << 8) | data[2]) * scaleFactor;
    z = ((data[5] << 8) | data[4]) * scaleFactor;
        
    return 0;
}
        

int IMU::Initialize() {
    
    int error;
    
    // First, set the operating mode to configuration
    error = i2c_->sendByte(address_,
                           BNO055_OPR_MODE_ADDR,
                           BNO055_OPERATION_MODE_CONFIG);
    if (error) {
        return error;
    }
    
    // Reset the chip
    error = i2c_->sendByte(address_, BNO055_SYS_TRIGGER_ADDR, 0x20);
    
    if (error) {
        return error;
    }
    
    // Wait for it to come back online
    char response;
    
    do {
        
        usleep(1000);
		
        error = i2c_->readByte(address_, BNO055_CHIP_ID_ADDR, &response);
        
        // we don't want to return based on error here since the chip will
		// return an error if we try to read from it before it's ready
        
    } while (response != BNO055_ID);
	
    usleep(500);
    
    // Set power mode to normal
    error = i2c_->sendByte(address_,
                           BNO055_PWR_MODE_ADDR,
                           BNO055_POWER_MODE_NORMAL);
    
    if (error) {
        return error;
    }
    
    usleep(100);
    
    // Write 0 to page ID
    
    error = i2c_->sendByte(address_, BNO055_PAGE_ID_ADDR, 0x00);
    
    if (error) {
        return error;
    }
    
    // Write 0 to system trigger
    
    error = i2c_->sendByte(address_, BNO055_SYS_TRIGGER_ADDR, 0x00);
    
    if (error) {
        return error;
    }
    
    usleep(100);
    
    // Set mode to NDOF
    error = i2c_->sendByte(address_,
                           BNO055_OPR_MODE_ADDR,
                           BNO055_OPERATION_MODE_NDOF);
    
    if (error) {
        return error;
    }
    
    usleep(200);

    return 0;
}

int IMU::GetTemperature(char* temperature) {
    return i2c_->readByte(address_, BNO055_TEMP_ADDR, temperature);
}

int IMU::GetMagnetometerData(
    float& x,
    float& y,
    float& z) {
  
    return ReadThreeAxisData(BNO055_MAG_DATA_X_LSB_ADDR,
                             BNO055_MAG_SCALE_FACTOR,
                             x, y, z);
}

int IMU::GetGyroscopeData(float& x, float& y, float& z) {
    
    return ReadThreeAxisData(BNO055_GYRO_DATA_X_LSB_ADDR,
                             BNO055_GYRO_SCALE_FACTOR,
                             x, y, z);
}

int IMU::GetAccelerationData(
    float& x,
    float& y,
    float& z) {
    
    return ReadThreeAxisData(BNO055_ACCEL_DATA_X_LSB_ADDR,
                             BNO055_ACCEL_SCALE_FACTOR,
                             x, y, z);
}

int IMU::GetGravityData(float& x, float& y, float& z) {
    
    return ReadThreeAxisData(BNO055_GRAVITY_DATA_X_LSB_ADDR,
                             BNO055_GRAVITY_SCALE_FACTOR,
                             x, y, z);
}

int IMU::GetLinearAccelerationData(
    float& x,
    float& y,
    float& z) {
        
    return ReadThreeAxisData(BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR,
                             BNO055_LINEAR_ACCEL_SCALE_FACTOR,
                             x, y, z);
}

int IMU::GetRoll(float& roll) {
    
    char data[2];
    int error = i2c_->readBytes(address_, 
                                BNO055_EULER_R_LSB_ADDR, 
                                2, 
                                data);
    
    if (error) {
        return error;
    }
    
    roll = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return 0;
}

int IMU::GetPitch(float& pitch) {
    
    char data[2];
    int error = i2c_->readBytes(address_, 
                                BNO055_EULER_P_LSB_ADDR, 
                                2, 
                                data);
    
    if (error) {
        return error;
    }
    
    pitch = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return 0;
}

int IMU::GetHeading(float& heading) {
    char data[2];
    int error = i2c_->readBytes(address_, 
                                BNO055_EULER_H_LSB_ADDR, 
                                2, 
                                data);
    
    if (error) {
        return error;
    }
    
    heading = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return 0;
}

int IMU::GetQuaternion(
    float& w,
    float& x,
    float& y,
    float& z) {
        
    char data[8];
    int error = i2c_->readBytes(address_, 
                                BNO055_QUATERNION_DATA_W_LSB_ADDR, 
                                8, 
                                data);
    
    if (error) {
        return error;
    }
    
    w = ((data[1] << 8) | data[0]) * BNO055_QUATERNION_SCALE_FACTOR;
    x = ((data[3] << 8) | data[2]) * BNO055_QUATERNION_SCALE_FACTOR;
    y = ((data[5] << 8) | data[4]) * BNO055_QUATERNION_SCALE_FACTOR;
    z = ((data[7] << 8) | data[6]) * BNO055_QUATERNION_SCALE_FACTOR;
    
    return 0;
}

} // namespace miromouse
