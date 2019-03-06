#include "../include/Maze.h"
#include "../include/Direction.h"
#include <queue>
#include <algorithm>


namespace algorithm {
using algorithm::Direction;

algorithm::Maze maze_ = algorithm::Maze(true, 16, 16);

void GetShortestPath(Cell* start, Cell* end) {
  std::queue<std::vector<Cell*>> cells_to_visit;
  std::vector<Cell*> tmppath = {start};
  Cell* curr;
  cells_to_visit.push(tmppath);

  while(cells_to_visit.empty() != false) {
    std::vector<Cell*> tmppath = cells_to_visit.front();
    cells_to_visit.pop();
    curr = tmppath.back();
    if (curr->x_ == end->x_ && curr->y_ == end->y_) {
      printf("valid path found");
    }

    for (auto neighbor: maze_.GetNeighbors(curr->x_, curr->y_)) {
      if (std::find(tmppath.begin(), tmppath.end(), curr) == tmppath.end()) {
        std::vector<Cell*> newpath = tmppath;
        newpath.push_back(neighbor);
        cells_to_visit.push(newpath);
      }
    }
  }
}

}

int main() {
}
