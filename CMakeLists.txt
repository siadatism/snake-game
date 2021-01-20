cmake_minimum_required(VERSION 3.16)

project(snake-game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(game Main.cpp Snake.cpp Page.cpp)
target_link_libraries(game pthread)
