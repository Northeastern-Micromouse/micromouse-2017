#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "robot.h"
#include "AlgoRobot.h"
#include "Direction.h"

int main() {
    //micromouse::I2cDevice myI2C = micromouse::I2cDevice();
    //std::cout << std::hex << (int)myI2C.readByte(0x28, 0x0) << std::endl;
    //65 47 64
    //46 44 124
	/*
    micromouse::RgbLedDevice led(64, 47, 65);
    led.setRgb(1, 1, 1);
	
	micromouse::I2cDevice i2c;
	std::cout << "Opening: " << i2c.openI2C() << std::endl;
	
	micromouse::LedDriver leds(&i2c, LED_DRIVER_DEFAULT_ADDRESS);
	std::cout << "Init: " << leds.init() << std::endl;
	std::cout << "Set: " << leds.setIntensity(0, 4095) << std::endl;
	*/
	
	//usleep(6000000);
	
//	std::ifstream speedStream;
//	speedStream.open("/home/debian/speed.txt");
//	float driveSpeed, turnSpeed;
//	speedStream >> driveSpeed;
//	speedStream >> turnSpeed;
//	speedStream.close();
//
//	micromouse::Robot robot;
//	robot.init();
//	robot.enableMotors();
//
//	while(1) {
//
//		bool frontWall = false;
//		bool leftWall = false;
//		bool rightWall = false;
//		robot.checkWallFront(&frontWall);
//		robot.checkWallLeft(&leftWall);
//		robot.checkWallRight(&rightWall);
//
//		if(frontWall) {
//			robot.turn(-1, turnSpeed);
//		}
//		else {
//			robot.pid_drive(180, driveSpeed);
//		}

  algorithm::Robot winslow = algorithm::Robot(true, 5, 5, algorithm::Direction::NORTH);
  winslow.Map();
		
		/*
		std::cout << frontWall << leftWall << rightWall << std::endl;
		
		if(frontWall && leftWall && rightWall) {
			robot.turn(2, turnSpeed);
		}
		else {
			int i;
			bool wallPicked = false;
			while(!wallPicked) {
				i = rand() % 3;
				switch(i) {
					case 0: wallPicked = !frontWall;
					case 1: wallPicked = !leftWall;
					case 2: wallPicked = !rightWall;
				}
			}
			switch(i) {
				case 0:
					robot.pid_drive(180, driveSpeed);
				case 1:
					robot.turn(-1, turnSpeed);
					robot.pid_drive(180, driveSpeed);
				case 2:
					robot.turn(1, turnSpeed);
					robot.pid_drive(180, driveSpeed);
			}
		}
		*/
	}
	
   
	return 0;
}
