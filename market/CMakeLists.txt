cmake_minimum_required(VERSION 3.15)
project(market)

set(CMAKE_CXX_STANDARD 14)

add_executable(market main.cpp lib/BinarySemaphore.cpp lib/BinarySemaphore.h lib/IntegerChannel.cpp lib/IntegerChannel.h lib/IntegerSemaphore.cpp lib/IntegerSemaphore.h)