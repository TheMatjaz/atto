# Atto Cmake configuration file
# Copyright © 2019, Matjaž Guštin <dev@matjaz.it> <https://matjaz.it>
# All rights reserved.
# This file is part of the Atto project which is released under
# the BSD 3-clause license.
# -----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.13)
project(Atto C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wswitch-default")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-enum -Wuninitialized -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion -Wpacked")

add_executable(atto_example example.c)
add_executable(atto_selftest selftest.c)
