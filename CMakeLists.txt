cmake_minimum_required(VERSION 3.10)

project(jake)
set(CMAKE_CXX_STANDARD 20)

file(GLOB jakecpps "src/*.cpp")

add_executable(jake ${jakecpps})
target_include_directories(jake PUBLIC include/)

find_package(Catch2 2 QUIET)

if(Catch2_FOUND)
        add_executable(jaketest ./tests/test.cpp ./src/fileutils.cpp ./src/util.cpp)
        target_include_directories(jaketest PUBLIC include/)
        target_link_libraries(jaketest PRIVATE Catch2::Catch2WithMain)
else()
        message(WARNING "Catch2 wasn't found on your system. Not building tests.")
endif()