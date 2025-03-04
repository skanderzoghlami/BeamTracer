cmake_minimum_required(VERSION 3.10.0)
project(raytrace VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")
add_executable(raytrace main.cpp ${SOURCES})
target_include_directories(raytrace PRIVATE include)
