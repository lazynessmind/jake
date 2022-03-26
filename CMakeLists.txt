cmake_minimum_required(VERSION 3.10)

project(jake)

add_executable(jake
    ./src/util.cpp 
    ./src/main.cpp
    ./src/include/util.h
    ./src/include/json.hpp
)