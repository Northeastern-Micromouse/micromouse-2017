#include "../include/RobotStub.h"

namespace micromouse {

using algorithm::Direction;

Robot::Robot(bool enable_debugging, int maze_x, int maze_y, Direction orientation)
    : maze_(false, maze_x, maze_y),
      orientation_(algorithm::Direction::SOUTH),
      cur_x_(0),
      cur_y_(0)
      {

  maze_.ReadFromFile();
  maze_.print();
}

int Robot::pid_drive(float distance, float speed) {
  switch(orientation_) {
    case Direction::NORTH: cur_y_ = cur_y_ - 1;
    case Direction::SOUTH: cur_y_ = cur_y_ + 1;
    case Direction::EAST: cur_x_ = cur_x_ + 1;
    case Direction::WEST: cur_x_ = cur_x_ - 1;
  }

  return 0;
}

int Robot::setxy(int x, int y) {
  cur_x_ = x;
  cur_y_ = y;
}

int Robot::setorientation(algorithm::Direction orientation) {
  printf("new orientatino: ");
  switch(orientation) {
    case Direction::NORTH:
      printf("north\n");
      break;
    case Direction::SOUTH:
      printf("south\n");
      break;
    case Direction::EAST:
      printf("east\n");
      break;
    case Direction::WEST:
      printf("west\n");
      break;
  }
  orientation_ = orientation;
}

int Robot::turn(int amt, float speed) {
  switch(orientation_) {
    case Direction::NORTH:
      switch(amt) {
        case 1:
          orientation_ = Direction::EAST;
          break;
        case 2:
          orientation_ = Direction::SOUTH;
          break;
        case -1: orientation_ = Direction::WEST;
          break;
      }
      break;
    case Direction::SOUTH:
      switch(amt) {
        case 1:
          orientation_ = Direction::WEST;
          break;
        case 2:
          orientation_ = Direction::NORTH;
          break;
        case -1:
          orientation_ = Direction::EAST;
          break;
      }
      break;
    case Direction::EAST:
      switch(amt) {
        case 1:
          orientation_ = Direction::SOUTH;
          break;
        case 2:
          orientation_ = Direction::WEST;
          break;
        case -1:
          orientation_ = Direction::NORTH;
          break;
      }
      break;
    case Direction::WEST:
      switch(amt) {
        case 1:
          orientation_ = Direction::NORTH;
          break;
        case 2:
          orientation_ = Direction::EAST;
          break;
        case -1:
          orientation_ = Direction::SOUTH;
          break;
      }
      break;
  }
  return 0;
}

int Robot::checkWallFront(bool* result) {
  printf("row: %d, col: %d\n", cur_y_, cur_x_);
  auto cell = maze_.get(cur_x_, cur_y_);
  printf("robot code - top: %d bot: %d left: %d right: %d\n", !cell.has_top_, !cell.has_bottom_, !cell.has_left_, !cell.has_right_);

  switch(orientation_) {
    case Direction::NORTH:
      *result= cell.has_top_;
      break;
    case Direction::SOUTH:
      *result= cell.has_bottom_;
      break;
    case Direction::EAST:
      printf("checking front wall: %d\n", cell.has_right_);
      *result= cell.has_right_;
      break;
    case Direction::WEST:
      *result= cell.has_left_;
      break;
  }
  return 0;
}

int Robot::checkWallRight(bool* result) {
  switch(orientation_) {
    case Direction::NORTH:
      *result= maze_.get(cur_x_, cur_y_).has_right_;
      break;
    case Direction::SOUTH:
      *result= maze_.get(cur_x_, cur_y_).has_left_;
      break;
    case Direction::EAST:
      printf("checking right wall: %d\n", maze_.get(cur_x_, cur_y_).has_bottom_);
      *result= maze_.get(cur_x_, cur_y_).has_bottom_;
      break;
    case Direction::WEST:
      *result= maze_.get(cur_x_, cur_y_).has_top_;
      break;
  }
  return 0;
}

int Robot::checkWallLeft(bool* result) {
  switch(orientation_) {
    case Direction::NORTH:
      *result = maze_.get(cur_x_, cur_y_).has_left_;
      break;
    case Direction::SOUTH:
      *result= maze_.get(cur_x_, cur_y_).has_right_;
      break;
    case Direction::EAST:
      printf("checking left wall: %d\n", maze_.get(cur_x_, cur_y_).has_top_);
      *result= maze_.get(cur_x_, cur_y_).has_top_;
      break;
    case Direction::WEST:
      *result= maze_.get(cur_x_, cur_y_).has_bottom_;
      break;
  }
  return 0;
}
}
