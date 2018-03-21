#ifndef MICROMOUSE_2018_ALGO_MAZE_H
#define MICROMOUSE_2018_ALGO_MAZE_H

#include <vector>

#include "Cell.h"

namespace algorithm {

class Maze {
 public:
  Maze(bool enable_debugging_, int rows, int cols);

  void Clear();

  Cell& get(int x, int y);

  std::vector<Cell*> GetNeighbors(int x, int y);

  // Returns the number of rows in the maze.
  int rows();

  // Returns the number of cols in the maze.
  int cols();

 private:
  bool enable_debugging_;
  int rows_;
  int cols_;
  std::vector<std::vector<Cell>> cells_;

  void Log(const std::string& log);
};

}

#endif //MICROMOUSE_2018_ALGO_MAZE_H
