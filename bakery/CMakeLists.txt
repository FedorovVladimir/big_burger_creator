cmake_minimum_required(VERSION 3.15)
project(bakery)

set(CMAKE_CXX_STANDARD 14)

add_executable(bakery main.cpp lib/BinarySemaphore.h lib/BinarySemaphore.cpp lib/IntegerChannel.h lib/IntegerChannel.cpp lib/IntegerSemaphore.h lib/IntegerSemaphore.cpp)