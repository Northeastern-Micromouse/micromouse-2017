#include "robot.h"

namespace micromouse {
	
int Robot::init() {
	/** Initialize drive system **/
	micromouse::GpioDevice* leftMotorDirPin = new GpioDevice(112);
	micromouse::GpioDevice* rightMotorDirPin = new GpioDevice(113);
	micromouse::GpioDevice* enableMotorPin = new GpioDevice(114);
	
	leftMotorDirPin->setDirection(GPIO_OUT);
	rightMotorDirPin->setDirection(GPIO_OUT);
	enableMotorPin->setDirection(GPIO_OUT);
	
	this->_motorSystem = new micromouse::MotorSystem("/dev/rpmsg_pru30",  
													leftMotorDirPin, 
													rightMotorDirPin, 
													enableMotorPin);
	std::cout << "Initialized drive system." << std::endl;
	
	/** Initialize sensors **/
	micromouse::I2cDevice* i2c1 = new I2cDevice(1);
	micromouse::LedDriver* ledDriver = 
		new LedDriver(i2c1, LED_DRIVER_DEFAULT_ADDRESS);
		
	ledDriver->init();
	
	std::cout << "Initialized LED driver." << std::endl;
	
	this->_leftFrontFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor3",
								ledDriver,
								3);
	
	this->_rightFrontFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor5",
								ledDriver,
								5);
								
	this->_frontLeftFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor2",
								ledDriver,
								2);
								
	this->_rearLeftFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor0",
								ledDriver,
								0);
								
	this->_frontRightFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor1",
								ledDriver,
								1);
								
	this->_rearRightFacing = new
		micromouse::ReflSensor("/home/debian/sensors/sensor4",
								ledDriver,
								4);
	
	std::cout << "Initialized reflectance sensors." << std::endl;
	
	std::ifstream pidFile;
	pidFile.open(PID_GAINS_PATH);
	pidFile >> this->_drive_kp;
	pidFile >> this->_drive_ki;
	pidFile >> this->_drive_kd;
	pidFile.close();
	
	std::cout << "Loaded PID gains: ";
	std::cout << this->_drive_kp << " ";
	std::cout << this->_drive_ki << " ";
	std::cout << this->_drive_kd << std::endl;
	
	this->_led1 = new micromouse::RgbLedDevice(64, 47, 65);
	this->_led1->setRgb(0, 0, 1);
}

int Robot::getLeftDistance(float* distance) {
	*distance = (this->_frontLeftFacing->getDistance() +
				this->_rearLeftFacing->getDistance())/2.0;
	
	return 0;
}

int Robot::getRightDistance(float* distance) {
	*distance = (this->_frontRightFacing->getDistance() +
				this->_rearRightFacing->getDistance())/2.0;
	
	return 0;
}

int Robot::getFrontDistance(float* distance) {
	*distance = (this->_leftFrontFacing->getDistance() +
				this->_rightFrontFacing->getDistance())/2.0;
	
	return 0;
}

int Robot::pid_drive(float distance, float speed) {
	
	PID pid(this->_drive_kp, this->_drive_ki, this->_drive_kd);
	pid.reset();
	pid.setSetpoint(0);
	
	this->_motorSystem->enable();
	
	for(int i = 0; i < DRIVE_DIVISIONS; i++) {
		
		float error = 0;
		
		// Determine if we have enough walls to calculate error
		bool leftWall = 0, rightWall = 0;
		if(this->checkWallLeft(&leftWall) || 
			this->checkWallRight(&rightWall)) {
			std::cout << "Error checking wall." << std::endl; 
			return -1;
		}
		
		if(leftWall && rightWall) {
			float leftSensorDistance, rightSensorDistance;
			if(this->getLeftDistance(&leftSensorDistance) || 
				this->getRightDistance(&rightSensorDistance)) {
				std::cout << "Error getting distance." << std::endl;
				return -1;
			}
			
			error = leftSensorDistance - rightSensorDistance;
		}
		
		else if(leftWall) {
			std::cout << "Warning: only left wall detected" << std::endl;
			error = this->_frontLeftFacing->getDistance() - 
					this->_rearLeftFacing->getDistance();
		}
		
		else if(rightWall) {
			std::cout << "Warning: only right wall detected" << std::endl;
			error = this->_frontRightFacing->getDistance() - 
					this->_rearRightFacing->getDistance();
		}
		
		else {
			std::cout << "WARNING: NO WALLS DETECTED." << std::endl;
		}
		
		
		float offset = pid.update(error, (distance / DRIVE_DIVISIONS) / speed);
		
		float leftDistance = (distance / DRIVE_DIVISIONS) + offset;
		float rightDistance = (distance / DRIVE_DIVISIONS) - offset;
		
		// First, figure out how much time the entire operation will take using the
		// given velocity
		float time = ((leftDistance + rightDistance) / 2) / speed;
		
		// Now compute the left and right velocities, and accordingly the time per
		// step of the left and right wheels
		float leftVelocity = leftDistance / time;
		float rightVelocity = rightDistance / time;
			
		// (rad/step) / (rad/s) = (s/step)
		// Also calculate required angular velocity
		// v = rw -> w = r/v
		int periodLeft = (int)((DISTANCE_PER_STEP * 1000000)/ 
								leftVelocity);
		int periodRight = (int)((DISTANCE_PER_STEP * 1000000) / 
								rightVelocity);
								
		std::cout << periodRight << std::endl;
			
		int stepsLeft = leftDistance / DISTANCE_PER_STEP;
		int stepsRight = rightDistance / DISTANCE_PER_STEP;
		
		this->_motorSystem->drive(stepsLeft,
									stepsRight,
									periodLeft,
									periodRight,
									MOTOR_FORWARD,
									MOTOR_FORWARD,
									5000);
	}
	
	this->_motorSystem->disable();

	return 0;
}

int Robot::turn(int amt, float speed) {
	int stepSpeed = (int)((DISTANCE_PER_STEP * 1000000)/ 
								speed);
								
	std::cout << TURN_STEPS(amt) << " " << stepSpeed << std::endl;
	return this->_motorSystem->drive(TURN_STEPS(amt),
									TURN_STEPS(amt),
									stepSpeed,
									stepSpeed,
									((amt > 0) ? MOTOR_FORWARD : MOTOR_BACKWARD),
									((amt > 0) ? MOTOR_BACKWARD : MOTOR_FORWARD),
									5000);
}

int Robot::checkWallFront(bool* result) {
	*result = this->_leftFrontFacing->getDistance() <= WALL_THRESHOLD && 
				this->_rightFrontFacing->getDistance() <= WALL_THRESHOLD;
	return 0;
}

int Robot::checkWallRight(bool* result) {
	*result = this->_frontRightFacing->getDistance() <= WALL_THRESHOLD && 
				this->_rearRightFacing->getDistance() <= WALL_THRESHOLD;
	return 0;
}

int Robot::checkWallLeft(bool* result) {
	*result = this->_frontLeftFacing->getDistance() <= WALL_THRESHOLD && 
				this->_rearLeftFacing->getDistance() <= WALL_THRESHOLD;
	return 0;
}

void Robot::setLED1(int r, int g, int b) {
	this->_led1->setRgb(r, g, b);
}

}