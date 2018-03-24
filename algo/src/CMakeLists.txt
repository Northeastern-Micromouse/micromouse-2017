cmake_minimum_required(VERSION 3.6)
project(MicroMouse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB_RECURSE SRCFILES *.cc *.h)

set(SOURCE_FILES ${SRCFILES} main.cc)

add_executable(MicroMouse ${SOURCE_FILES})