// Micromouse 2018
// Written by Matthew Murphy

#include <iostream>

#include "../../firmware/include/AlgoRobot.h"
#include "../../firmware/include/Direction.h"

int main() {
  std::cout << "Running the micromouse program!" << std::endl;

  algorithm::Robot winslow = algorithm::Robot(true, 5, 5, algorithm::Direction::NORTH);
  winslow.Map();

  return 0;
}
