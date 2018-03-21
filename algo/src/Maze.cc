#include "Maze.h"

#include <cassert>
#include <iostream>

namespace algorithm {

using algorithm::Cell;

Maze::Maze(bool enable_debugging_, int rows, int cols)
  : enable_debugging_(enable_debugging_),
    rows_(rows),
    cols_(cols) {
  for (int ii = 0; ii < rows; ii++) {
    cells_.push_back(std::vector<Cell>(cols));
    for (int jj = 0; jj < cols; jj++) {
      cells_[ii][jj].Configure(ii, jj);
    }
  }

  assert(cells_.size() == rows_ && cells_[0].size() == cols_);
}

void Maze::Clear() {
  // No op.
}

int Maze::rows() {
  return rows_;
}

int Maze::cols() {
  return cols_;
}

std::vector<Cell*> Maze::GetNeighbors(int x, int y) {
  std::vector<Cell*> neighbors;
  assert(x < rows_ && y < cols_ && y >= 0 && x >= 0);
  // See if there is a cell above it.
  if (y + 1 < cols_ && !cells_[x][y].has_top_) {
    neighbors.push_back(&cells_[x][y + 1]);
  }
  // Check if there is a cell below it.
  if (y - 1 >= 0 && !cells_[x][y].has_bottom_) {
    neighbors.push_back(&cells_[x][y - 1]);
  }
  // Check if there is a cell left of it.
  if (x - 1 >= 0 && !cells_[x][y].has_left_) {
    neighbors.push_back(&cells_[x - 1][y]);
  }
  // Check if there is a cell right of it.
  if (x + 1 < rows_ && !cells_[x][y].has_right_) {
    neighbors.push_back(&cells_[x + 1][y]);
  }

  Log("There are " + std::to_string(neighbors.size()) + " neighbors to cell " + std::to_string(x) + "," + std::to_string(y));
  return neighbors;
}

Cell& Maze::get(int x, int y) {
  return cells_[x][y];
}

void Maze::Log(const std::string& log) {
  if (enable_debugging_) {
    std::cout << log << std::endl;
  }
}

}
