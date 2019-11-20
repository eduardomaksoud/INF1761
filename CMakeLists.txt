cmake_minimum_required(VERSION 3.5)

project(Raytracing)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Raytracing src/Main.cpp)
target_link_libraries(Raytracing ${SDL2_LIBRARIES})
