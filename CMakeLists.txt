# Atto Cmake configuration file
# Copyright © 2019, Matjaž Guštin <dev@matjaz.it> <https://matjaz.it>
# All rights reserved.
# This file is part of the Atto project which is released under
# the BSD 3-clause license.
# -----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.13)
project(Atto C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")  # Warnings as errors!
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wdouble-promotion ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-default -Wswitch-enum ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wuninitialized -Wno-unused-variable")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpacked -Wpadded -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat-security")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wlogical-not-parentheses")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Waggregate-return")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations -fPIC")

add_executable(atto_selftest tst/selftest.c src/atto.c src/atto.h)
