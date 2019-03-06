#ifndef ROBOT_H
#define ROBOT_H

#include <fstream>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include "Maze.h"
#include "Direction.h"

namespace micromouse {


class Robot {

public:
  Robot(bool enable_debugging, int maze_x, int maze_y, algorithm::Direction orientation);
	int pid_drive(float distance, float speed);
	int turn(int amt, float speed);
	int checkWallFront(bool* result);
	int checkWallRight(bool* result);
	int checkWallLeft(bool* result);
	int setxy(int x, int y);
	int setorientation(algorithm::Direction orientation);


private:
  algorithm::Direction orientation_;
  algorithm::Maze maze_;
	int cur_x_;
	int cur_y_;
};
}

#endif
