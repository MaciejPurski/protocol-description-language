cmake_minimum_required(VERSION 3.9)
project(TKOM)

set(CMAKE_CXX_STANDARD 17)

add_executable(TKOM main.cpp Source.cpp Source.h Scanner.cpp Scanner.h tokens.h)