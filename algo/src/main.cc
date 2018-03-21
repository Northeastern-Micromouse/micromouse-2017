// Micromouse 2018
// Written by Matthew Murphy

#include <iostream>

#include "Robot.h"
#include "Direction.h"

int main() {
  std::cout << "Running the micromouse program!" << std::endl;

  algorithm::Robot winslow = algorithm::Robot(true, 5, 5, algorithm::Direction::NORTH);
  winslow.Map();

  return 0;
}
