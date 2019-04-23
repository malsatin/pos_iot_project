# cmake_minimum_required(VERSION <specify CMake version here>)
project(pos_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_MESSAGE LAZY)

add_executable(pos_project test.c present/Present.c present/Present.h present/PresentECB.h)