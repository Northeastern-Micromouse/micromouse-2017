#include "../include/AlgoRobot.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>

namespace algorithm {

using algorithm::Direction;

Robot::Robot(bool enable_debugging, int maze_x, int maze_y, Direction orientation)
    : maze_(enable_debugging, maze_x, maze_y),
      orientation_(orientation),
      enable_debugging_(enable_debugging),
      curr_x_(0),
      curr_y_(0),
      driveSpeed_(0),
      turnSpeed_(0),
      top_left_goal_x_(7),
      top_left_goal_y_(7),
      bottom_right_goal_x_(8),
      bottom_right_goal_y_(8),
      winslow_(enable_debugging, maze_x, maze_y, orientation) {
        /*
  winslow_.init();
  winslow_.enableMotors();
  std::ifstream speedStream;
  speedStream.open("/home/debian/speed.txt");
  speedStream >> driveSpeed_;
  speedStream >> turnSpeed_;
  speedStream >> top_left_goal_x_;
  speedStream >> top_left_goal_y_;
  speedStream.close();*/
}

bool inPath(std::vector<Cell*> path, Cell* c) {
  //printf("%d, %d\n",  c->x_, c->y_);
  for (int i = 0; i < path.size(); i++) {
    //printf("%d, %d\n",  path[i]->x_, path[i]->y_);
    if ((c->x_ == path[i]->x_) && (c->y_ == path[i]->y_)) {
      //printf("%d, %d\n",  path[i]->x_, path[i]->y_);
      return true;
    }
  }
  return false;
}

void Robot::Map() {
  curr_x_ = 0;
  curr_y_ = 0;
  std::stack<Cell*> cells_to_visit;
  Cell* curr = &maze_.get(0,0);
  cells_to_visit.push(curr);
  std::vector<Cell*> visited = {curr};

  while(!cells_to_visit.empty()) {
    curr = cells_to_visit.top();
    cells_to_visit.pop();
    std::vector<Cell*> tmppath = {curr};
    moveToPath(tmppath);
    if (curr->x_ == top_left_goal_x_ && curr->y_ == top_left_goal_y_) {
      Cell* hi = &maze_.get(top_left_goal_x_,top_left_goal_y_);
      while (hi->x_ != 0 || hi->y_ != 0) {
        printf("col: %d row: %d ->", hi->x_, hi->y_);
        hi = hi->actualParent_;
      }
      printf("\n");
    }
    VisitCurrentCell();
    visited.push_back(curr);
    for (auto neighbor: maze_.GetNeighbors(curr->x_, curr->y_)) {
      if (!inPath(visited, neighbor)) {
        neighbor->actualParent_ = curr;
        cells_to_visit.push(neighbor);
      }
    }
  }
}

void Robot::ComputeShortestPath() {
  printf("computing shortest path ;) \n\n");
  std::stack<std::vector<Cell*>> cells_to_visit;
  std::vector<Cell*> tmppath = {&maze_.get(0,0)};
  Cell* curr;
  cells_to_visit.push(tmppath);
  std::vector<std::vector<Cell*>> possiblePaths;
  std::vector<Cell*> shortestPath;
  curr_x_ = 0;
  curr_y_ = 0;

  while(!cells_to_visit.empty()) {
  //for (int i = 0; i < 10; i++) {
    //maze_.print();
    std::vector<Cell*> tmppath = cells_to_visit.top();
    cells_to_visit.pop();
    curr = tmppath.back();
    //printf("x: %d y: %d\n", curr->x_, curr->y_);
    //TODO: actually move
    //TODO: orientation should be set by moving

    curr_x_ = curr->x_;
    curr_y_ = curr->y_;
    //winslow_.setxy(curr_x_, curr_y_);
    //if (tmppath.size() > 1) {
    //  orientation_ = GetDirection(tmppath[tmppath.size() - 2], tmppath[tmppath.size() - 1]);
    //  winslow_.setorientation(orientation_);
    //} else {
    //  printf("one elem path\n");
    //  orientation_ = Direction::SOUTH;
    //  winslow_.setorientation(Direction::SOUTH);
    //}
    //TODO dont hardcode this
    //moveToPath(tmppath);
    if (curr->x_ == top_left_goal_x_ && curr->y_ == top_left_goal_y_) {
        possiblePaths.push_back(std::vector<Cell*>(tmppath));
    }
    //printf("visiting curr cell\n");
    //VisitCurrentCell();
    for (auto neighbor: maze_.GetNeighbors(curr->x_, curr->y_)) {
      if (!inPath(tmppath, neighbor)) {
        std::vector<Cell*> newpath = tmppath;
        newpath.push_back(neighbor);
        cells_to_visit.push(newpath);
      }
    }
}
  curr_x_ = 0;
  curr_y_ = 0;
  shortestPath = possiblePaths[0];
  int minTurns = INT_MAX;
  for (auto a : possiblePaths) {
    Direction prevDir = Direction::NONE;
    int turns = 0;
    for (int i = 0; i < a.size() - 1; i++) {
      if (prevDir != GetDirection(a[i], a[i + 1])) {
        turns+=3;
      } else {
        turns+=1;
      }
    }
    if (turns < minTurns) {
      minTurns = turns;
      shortestPath = a;
    }
  }
  for (int i = 0; i < shortestPath.size() - 1; i++) {
    Direction dir = GetDirection(shortestPath[i], shortestPath[i + 1]);
    switch(dir) {
      case Direction::NORTH:
        printf("north");
        break;
      case Direction::SOUTH:
        printf("south");
        break;
      case Direction::EAST:
        printf("east");
        break;
      case Direction::WEST:
        printf("west");
        break;
    }
    printf(" -> ");
    Move(GetDirection(shortestPath[i], shortestPath[i + 1]));
  }
  printf("\n");
  Log("Done computing the shortest path. At location: ");
}

Direction Robot::GetDirection(Cell* start, Cell* end) {
  if (start->x_ == end->x_ && start->y_ + 1 == end->y_) {
    //printf("returning south\n");
    return Direction::SOUTH;
  } else if (start->x_ == end->x_ && start->y_ == end->y_ + 1) {
    //printf("returning north\n");
    return Direction::NORTH;
  } else if (start->x_ + 1 == end->x_ && start->y_ == end->y_) {
    //printf("returning east\n");
    return Direction::EAST;
  } else if (start->x_ == end->x_ + 1 && start->y_ == end->y_) {
    //printf("returning west\n");
    return Direction::WEST;
  }
  //printf("wtf? %d %d %d %d\n", start->x_, start->y_, end->x_, end->y_);
  return Direction::NONE;
}

Direction Robot::GetDirection(Cell* cell) {

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
  Cell* aboveCell;
  Cell* belowCell;
  Cell* leftCell;
  Cell* rightCell;
  Cell fakeCell;
  Cell* fake = &fakeCell;
  if (curr_y_ - 1 >= 0) {
    aboveCell = &maze_.get(curr_x_, curr_y_ - 1);
  } else {
    aboveCell = fake;
  }
  if (curr_y_ + 1 < maze_.rows()) {
    belowCell = &maze_.get(curr_x_, curr_y_ + 1);
  } else {
    belowCell = fake;
  }
  if (curr_x_ - 1 >= 0) {
    leftCell = &maze_.get(curr_x_ - 1, curr_y_);
  } else {
    leftCell = fake;
  }
  if (curr_x_ + 1 < maze_.cols()) {
    rightCell = &maze_.get(curr_x_ + 1, curr_y_);
  } else {
    rightCell = fake;
  }
  switch(orientation_) {
    case Direction::NORTH:
      winslow_.checkWallFront(&cell.has_top_);
      winslow_.checkWallFront(&aboveCell->has_bottom_);
      winslow_.checkWallLeft(&cell.has_left_);
      winslow_.checkWallLeft(&leftCell->has_right_);
      winslow_.checkWallRight(&cell.has_right_);
      winslow_.checkWallRight(&rightCell->has_left_);
    break;
    case Direction::SOUTH:
      winslow_.checkWallFront(&cell.has_bottom_);
      winslow_.checkWallFront(&belowCell->has_top_);
      winslow_.checkWallLeft(&cell.has_right_);
      winslow_.checkWallLeft(&rightCell->has_left_);
      winslow_.checkWallRight(&cell.has_left_);
      winslow_.checkWallRight(&leftCell->has_right_);
    break;
    case Direction::WEST:
      winslow_.checkWallFront(&cell.has_left_);
      winslow_.checkWallFront(&leftCell->has_right_);
      winslow_.checkWallLeft(&cell.has_bottom_);
      winslow_.checkWallLeft(&belowCell->has_top_);
      winslow_.checkWallRight(&cell.has_top_);
      winslow_.checkWallRight(&aboveCell->has_bottom_);
    break;
    case Direction::EAST:
      winslow_.checkWallFront(&cell.has_right_);
      winslow_.checkWallFront(&rightCell->has_left_);
      winslow_.checkWallLeft(&cell.has_top_);
      winslow_.checkWallLeft(&aboveCell->has_bottom_);
      winslow_.checkWallRight(&cell.has_bottom_);
      winslow_.checkWallRight(&belowCell->has_top_);
    break;
  }
  return true;
}

void Robot::Move(Direction dir) {
  switch (dir) {
    case Direction::NORTH:
      Log("Move north");
      TurnNorth();
      curr_y_ -= 1;
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
      curr_y_ += 1;
      break;
    case Direction::NONE:
      Log("Do not need to move");
      return;
  }

  Log("Moved to cell: " + std::to_string(curr_x_) + "," + std::to_string(curr_y_));
  assert(curr_y_ >= 0 && curr_x_ >= 0 && curr_y_ < maze_.cols() && curr_x_ < maze_.rows());
  winslow_.pid_drive(180, driveSpeed_);
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
    case Direction::NONE:
      // No op.
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
      Rotate(180);
      break;
    case Direction::SOUTH:
      Rotate(-90);
      break;
    case Direction::NONE:
      // No op.
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
    case Direction::NONE:
      // No op.
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
      Rotate(90);
      break;
    case Direction::WEST:
      Rotate(-90);
      break;
    case Direction::SOUTH:
      // No op.
      break;
    case Direction::NONE:
      // No op.
      break;
  }
  orientation_ = Direction::SOUTH;
}

void Robot::Rotate(int degrees) {
  winslow_.turn(degrees / 90, turnSpeed_);
}

void Robot::GoBack(Direction dir) {
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
    case Direction::NONE:
      // No op.
      return;
  }
}

void Robot::moveToPath(std::vector<Cell*> tmppath) {
  Cell* curr = &maze_.get(curr_x_, curr_y_);
  Cell* start = curr;
  Cell* end = tmppath[tmppath.size() - 1];
  std::stack<Cell*> cells_to_visit;
  std::vector<Direction> path;

  while (curr->x_ != end->x_ || curr->y_ != end->y_) {
  //for (int i = 0; i < 1; i++) {
    std::vector<Cell*> neighbors = maze_.GetNeighbors(curr->x_, curr->y_);
    if (!curr->visited_) {
      for (Cell* neighbor : neighbors) {
        if (!neighbor->visited_) {
          neighbor->parent_ = curr;
          cells_to_visit.push(neighbor);
        }
      }
    }
    curr->visited_ = true;
    curr = cells_to_visit.top();
    cells_to_visit.pop();
    //printf("setting curr to %d, %d\n", curr->x_, curr->y_);
  }

  while (curr->x_ != start->x_ || curr->y_ != start->y_) {
    path.insert(path.begin(), GetDirection(curr->parent_, curr));
    curr = curr->parent_;
  }

  for (auto d : path) {
    //std::cout << "dir " << d << ", ";
    Move(d);
  }

  maze_.ClearVisitedAndParent();
}

bool Robot::IsInsideGoal(int x, int y) {
  return (x >= top_left_goal_x_ && x <= bottom_right_goal_x_)
         && (y <= top_left_goal_y_ && y >= bottom_right_goal_y_);
}

bool Robot::IsInsideGoal() {
  return IsInsideGoal(curr_x_, curr_y_);
}

void Robot::PrintPath(const std::vector<Direction>& path) {
  for (auto dir : path) {
    std::cout << dir << std::endl;
  }
}

}
