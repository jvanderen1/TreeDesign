cmake_minimum_required(VERSION 3.6)
project(Tree_Design)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x") # Latest standard of C

set(SOURCE_FILES main.c)
add_executable(Tree_Design ${SOURCE_FILES})