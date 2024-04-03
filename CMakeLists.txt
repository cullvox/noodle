cmake_minimum_required(VERSION 3.12)
project(noodle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_library(noodle "source/noodle.cpp")
target_include_directories(noodle PUBLIC "include")
