cmake_minimum_required(VERSION 3.25)
project(federalist_papers C)

set(CMAKE_C_STANDARD 11)

add_executable(federalist_papers main.c util/array.c util/array.h)
