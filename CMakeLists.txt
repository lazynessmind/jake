cmake_minimum_required(VERSION 3.10)

project(jake)
set(CMAKE_CXX_STANDARD 20)

add_executable(jake
    ./src/util.cpp 
    ./src/main.cpp
    ./src/java.cpp
    ./src/jake.cpp
)

target_include_directories(jake PUBLIC include/)