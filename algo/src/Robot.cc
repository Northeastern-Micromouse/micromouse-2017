#include "Robot.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace algorithm {

using algorithm::Direction;

Robot::Robot(bool enable_debugging, int maze_x, int maze_y, Direction orientation)
    : maze_(enable_debugging, maze_x, maze_y),
      orientation_(orientation),
      enable_debugging_(enable_debugging),
      curr_x_(0),
      curr_y_(0) {
  // No op.
}

void Robot::Map() {
  Log("--------------- Start Mapping the Maze ---------------");
  assert(curr_x_ == 0 && curr_y_ == 0);

  maze_.Clear();

  VisitCurrentCell();

  while (!neighbors_.empty()) {
    CellPair cell = neighbors_.top();
    Log("Got the cell: " + std::to_string(cell.first_->x_) + "," + std::to_string(cell.first_->y_));
    neighbors_.pop();
    // Move to where you were when you put the cell on the stack.
    Direction dir = GetDirection(&cell.second_);
    Move(dir);
    // Move to the cell
    dir = GetDirection(cell.first_);
    Move(dir);
    if (!VisitCurrentCell()) {
      GoBack(dir);
    }
  }

  Log("Done mapping the maze. At location: " + std::to_string(curr_x_) + "," = std::to_string(curr_y_));
}

Direction Robot::GetDirection(Cell* cell) {
  if (curr_x_ == cell->x_ && curr_y_ == cell->y_ + 1) {
    return Direction::SOUTH;
  } else if (curr_x_ == cell->x_ && curr_y_ == cell->y_ - 1) {
    return Direction::NORTH;
  } else if (curr_x_ == cell->x_ + 1 && curr_y_ == cell->y_) {
    return Direction::WEST;
  } else if (curr_x_ == cell->x_ - 1 && curr_y_ == cell->y_) {
    return Direction::EAST;
  } else if (curr_x_ == cell->x_ && curr_y_ == cell->y_) {
    return Direction::NONE;
  }
  Log(std::to_string(curr_x_) + "," + std::to_string(curr_y_) + "     " + std::to_string(cell->x_) + "," + std::to_string((cell->y_)));
  assert(false);
}

void Robot::ComputeShortestPath() {
  Log("Computing the shortest path");

}

void Robot::Run() {
  Log("Running the robot :)");
}

void Robot::Log(const std::string& log) {
  if (enable_debugging_) {
    std::cout << log << std::endl;
  }
}

bool Robot::VisitCurrentCell() {
  Cell& cell = maze_.get(curr_x_, curr_y_);
  bool should_move_forward = false;
  // Only visit a cell if it is not visited.
  if (!cell.visited_) {
    Log("--------------- Visit Cell ---------------");
    Log("X: " + std::to_string(cell.x_));
    Log("Y: " + std::to_string(cell.y_));
    Log("--------------------------------------------");
    // TODO(matt): Read the sensors and update the values. For now just say everything is open.
    cell.has_right_ = false;
    cell.has_left_ = false;
    cell.has_top_ = false;
    cell.has_bottom_ = false;

    for (Cell* c : maze_.GetNeighbors(curr_x_, curr_y_)) {
      if (!c->visited_) {
        neighbors_.push(CellPair(c, Cell(curr_x_, curr_y_)));
        should_move_forward = true;
      }
    }

    cell.visited_ = true;
  } else {
    std::stringstream ss;
    ss << "Trying to visit cell: ";
    ss << curr_x_;
    ss << ",";
    ss << curr_y_;
    ss << " and it is already visited";
    Log(ss.str());
  }
  return should_move_forward;
}

void Robot::Move(Direction dir) {
  switch (dir) {
    case Direction::NORTH:
      Log("Move north");
      TurnNorth();
      curr_y_ += 1;
      break;
    case Direction::EAST:
      Log("Move east");
      TurnEast();
      curr_x_ += 1;
      break;
    case Direction::WEST:
      Log("Move west");
      TurnWest();
      curr_x_ -= 1;
      break;
    case Direction::SOUTH:
      Log("Move south");
      TurnSouth();
      curr_y_ -= 1;
      break;
    case Direction::NONE:
      Log("Do not need to move");
      return;
  }

  Log("Moved to cell: " + std::to_string(curr_x_) + "," + std::to_string(curr_y_));
  assert(curr_y_ >= 0 && curr_x_ >= 0 && curr_y_ < maze_.cols() && curr_x_ < maze_.rows());
  // TODO(matt): Move forward one cell.
}

void Robot::TurnNorth(){
  switch (orientation_) {
    case Direction::NORTH:
      // No op.
      break;
    case Direction::EAST:
      Rotate(-90);
      break;
    case Direction::WEST:
      Rotate(90);
      break;
    case Direction::SOUTH:
      Rotate(180);
      break;
  }
  orientation_ = Direction::NORTH;
}

void Robot::TurnEast() {
  switch (orientation_) {
    case Direction::NORTH:
      Rotate(90);
      break;
    case Direction::EAST:
      // No op.
      break;
    case Direction::WEST:
      Rotate(-90);
      break;
    case Direction::SOUTH:
      Rotate(180);
      break;
  }
  orientation_ = Direction::EAST;
}

void Robot::TurnWest() {
  switch (orientation_) {
    case Direction::NORTH:
      Rotate(-90);
      break;
    case Direction::EAST:
      Rotate(180);
      break;
    case Direction::WEST:
      // No op.
      break;
    case Direction::SOUTH:
      Rotate(90);
      break;
  }
  orientation_ = Direction::WEST;
}

void Robot::TurnSouth() {
  switch (orientation_) {
    case Direction::NORTH:
      Rotate(180);
      break;
    case Direction::EAST:
      Rotate(-90);
      break;
    case Direction::WEST:
      Rotate(90);
      break;
    case Direction::SOUTH:
      // No op.
      break;
  }
  orientation_ = Direction::SOUTH;
}

void Robot::Rotate(int degrees) {
  // TODO(matt): Implement
  Log("Rotating " + std::to_string(degrees) + " degress");
}

void Robot::GoBack(Direction dir) {
  Log("Go back");
  switch (dir) {
    case Direction::NORTH:
      Move(Direction::SOUTH);
      return;
    case Direction::SOUTH:
      Move(Direction::NORTH);
      return;
    case Direction::EAST:
      Move(Direction::WEST);
      return;
    case Direction::WEST:
      Move(Direction::EAST);
      return;
  }
}

}
