cmake_minimum_required(VERSION 3.25)
project(federalist_papers C)

set(CMAKE_C_STANDARD 11)

add_executable(federalist_papers main.c util/IntArray.c util/IntArray.h main.h util/strutils.c util/strutils.h util/LinkedList.c util/LinkedList.h util/LinkedList.c util/BinaryTree.c util/BinaryTree.h util/BinaryTree.h)
