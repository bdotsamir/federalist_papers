cmake_minimum_required(VERSION 3.25)
project(federalist_papers C)

set(CMAKE_C_STANDARD 11)

add_executable(federalist_papers main.c util/IntArray.c util/IntArray.h main.h util/strutils.c util/strutils.h util/BinaryTree.c util/BinaryTree.h util/BinaryTree.h)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wconversion -Wunused-parameter -fsanitize=address,undefined)