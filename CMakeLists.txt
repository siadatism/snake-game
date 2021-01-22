cmake_minimum_required(VERSION 3.16)

project(snake-project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(snake-lib src/Snake.cpp src/Page.cpp)

include_directories(src)
add_executable(snake-game Main.cpp)
target_link_libraries(snake-game snake-lib pthread)
