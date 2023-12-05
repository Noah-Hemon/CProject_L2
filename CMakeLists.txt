cmake_minimum_required(VERSION 3.24)
project(projL2 C)

set(CMAKE_C_STANDARD 11)

add_executable(projL2 main.c cell.c cell.h list.c list.h timer.c timer.h calendar.h calendar.c)
