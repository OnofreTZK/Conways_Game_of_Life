cmake_minimum_required(VERSION 2.8.9)
project(CanvasLifeGame)

#Bring the headers, such as Student.h into the project
include_directories(include)

#SET C++ VERSION
set (CMAKE_CXX_STANDARD 14)

#However, the file (Glob...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(canvas ${SOURCES})

#To create cmake inside the build folder when its not working in tradicional methods
#cmake -S . -Bbuild

