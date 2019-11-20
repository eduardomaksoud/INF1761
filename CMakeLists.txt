cmake_minimum_required(VERSION 3.5)

project(Raytracing)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(builddir ${dir}/bin/builds)
set(EXECUTABLE_OUTPUT_PATH ${builddir} CACHE PATH "build" FORCE)
set(LIBRARY_OUTPUT_PATH ${builddir} CACHE PATH "build" FORCE)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Raytracing src/Main.cpp)
target_link_libraries(Raytracing ${SDL2_LIBRARIES})