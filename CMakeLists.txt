
project(Assignment3_ZHZ)

cmake_minimum_required(VERSION 2.6)

add_executable(Assignment3_ZHZ main.cpp Sonar.cpp Radar.cpp Ranger.cpp DataFusion.cpp)

find_package (Threads)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

