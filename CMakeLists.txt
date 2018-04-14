cmake_minimum_required(VERSION 3.9)
project(T2_SimuladorMIPS)

set(CMAKE_CXX_STANDARD 17)

add_executable(T2_SimuladorMIPS src/main.cpp include/memory.hpp src/memory.cpp include/registers.hpp src/registers.cpp include/processor.hpp src/processor.cpp include/constants.hpp)