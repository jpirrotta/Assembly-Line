cmake_minimum_required(VERSION 3.23)
project(MS2)

set(CMAKE_CXX_STANDARD 17)

add_executable(MS2 ms2.cpp CustomerOrder.cpp Station.h Station.cpp Utilities.h Utilities.cpp Workstation.cpp Workstation.h LineManager.h LineManager.cpp)
