cmake_minimum_required(VERSION 3.10)

project(jake)
set(CMAKE_CXX_STANDARD 20)

file(GLOB jakecpps "src/*.cpp")
add_executable(jake ${jakecpps})
add_executable(jake_tests ./tests/fileutils_tests.cpp ./src/fileutils.cpp ./src/util.cpp)

target_include_directories(jake PUBLIC include/)
target_include_directories(jake_tests PUBLIC include/)

add_custom_target(jake_tests_cmd
        COMMAND jake_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running tests before launching game."
        SOURCES ${jake}
        )

add_dependencies(jake jake_tests_cmd)