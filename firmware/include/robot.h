#ifndef ROBOT_H
#define ROBOT_H

#include <math.h>
#include "gpioDevice.h"
#include "ledDriver.h"
#include "motors.h"
#include "rgbLedDevice.h"
#include "PID.h"
#include "reflSensor.h"
#include "adcPin.h"

// PID Gains for driving
#define PID_GAINS_PATH "/home/debian/pidgains.txt"

// Number of discrete motions a single drive command will be divided into
#define DRIVE_DIVISIONS 10

// Hardware constants
#define MICROSTEPPING		16
#define RADIANS_PER_STEP 	((1.8 / MICROSTEPPING) * M_PI/180.0)
#define WHEEL_RADIUS 		30.0
#define DISTANCE_PER_STEP	(RADIANS_PER_STEP*WHEEL_RADIUS)

#define ROBOT_WIDTH 		110.0
#define TURN_LENGTH			(M_PI/2.0 * ROBOT_WIDTH/2.0)
#define TURN_STEPS(n)		(int)(fabs(n) * TURN_LENGTH / DISTANCE_PER_STEP)

#define WALL_THRESHOLD		80.0


namespace micromouse {
	
class Robot {
	
public:
	int init();
	int pid_drive(float distance, float speed);
	int turn(int amt, float speed);
	int checkWallFront(bool* result);
	int checkWallRight(bool* result);
	int checkWallLeft(bool* result);
	void setLED1(int r, int g, int b);

private:

	int getLeftDistance(float* distance);
	int getRightDistance(float* distance);
	int getFrontDistance(float* distance);

	micromouse::RgbLedDevice* _led1;
	micromouse::RgbLedDevice* _led2;
	
	micromouse::MotorSystem* _motorSystem;
	float _drive_kp;
	float _drive_ki;
	float _drive_kd;
	
	micromouse::ReflSensor* _leftFrontFacing;
	micromouse::ReflSensor* _rightFrontFacing;
	micromouse::ReflSensor* _frontLeftFacing;
	micromouse::ReflSensor* _rearLeftFacing;
	micromouse::ReflSensor* _frontRightFacing;
	micromouse::ReflSensor* _rearRightFacing;
	
	//micromouse::OrientationSensor* orientation;
	
};
	
	
}

#endif