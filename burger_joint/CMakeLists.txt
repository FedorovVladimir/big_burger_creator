cmake_minimum_required(VERSION 3.15)
project(burger_joint)

set(CMAKE_CXX_STANDARD 14)

add_executable(burger_joint main.cpp lib/BinarySemaphore.cpp lib/BinarySemaphore.h lib/IntegerChannel.cpp lib/IntegerChannel.h lib/IntegerSemaphore.cpp lib/IntegerSemaphore.h)