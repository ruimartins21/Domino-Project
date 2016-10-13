cmake_minimum_required(VERSION 3.6)
project(Domino-Project)

file(GLOB SOURCES libs/*.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c libs/utils.c libs/utils.h)

add_executable(Domino-Project ${SOURCES} ${SOURCE_FILES})