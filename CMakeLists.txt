# Atto Cmake configuration file
# Copyright © 2019-2020, Matjaž Guštin <dev@matjaz.it> <https://matjaz.it>
# All rights reserved.
# This file is part of the Atto project which is released under
# the BSD 3-clause license.
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.9)  # For FindDoxygen
project(Atto
        VERSION 1.3.1
        LANGUAGES C
        DESCRIPTION
        "The microscopic C test framework")


# -----------------------------------------------------------------------------
# Compiler flags
# -----------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Activate a million warnings to have the cleanest possible code
set(FLAGS_WARNINGS -Wall -Wextra -pedantic -Wconversion -Wdouble-promotion
    -Wswitch-default -Wswitch-enum -Wuninitialized -Wno-unused-variable
    -Wpacked -Wpadded -Wshadow -Wformat-security -Wlogical-not-parentheses
    -Waggregate-return -Wmissing-declarations -Wsign-conversion
    -Wjump-misses-init -Werror)
# Debug build: compile with no optimisation, debug info and printing
set(CMAKE_C_FLAGS_DEBUG "${WARNING_FLAGS} -g -O0 -DDEBUG")

# Performance-oriented release build: compile with optimisation for speed
# convert warnings into errors and some other optimisations
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DRELEASE \
        ${WARNING_FLAGS} -O3 -flto")


# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------
set(ATTO_LIB_SRC src/atto.h src/atto.c)
set(ATTO_DOXYGEN_SRC src/atto.h LICENSE.md CHANGELOG.md README.md)
set(ATTO_TEST_SRC tst/selftest.c)
include_directories(AFTER SYSTEM src/)


# -----------------------------------------------------------------------------
# Build targets
# -----------------------------------------------------------------------------
add_executable(atto_selftest ${ATTO_LIB_SRC} ${ATTO_TEST_SRC})


# Doxygen documentation builder
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)
    # Cmake's wrapper of Doxygen, constructing a doxyfile from the
    # DOXYGEN_* variables, which are mapped to the Doxygen variables.

    # Output format
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_SORT_MEMBER_DOCS NO)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_OUTPUT_LANGUAGE English)
    set(DOXYGEN_OUTPUT_DIRECTORY docs/)

    # Input format
    set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
    set(DOXYGEN_ALIASES license="**License:**")
    set(DOXYGEN_EXTRACT_ALL NO)
    set(DOXYGEN_INPUT_ENCODING UTF-8)

    # Input files
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_EXCLUDE src/atto.c tst/)

    # Turn on all warnings, as errors
    set(DOXYGEN_WARNINGS YES)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
    set(DOXYGEN_WARN_IF_DOC_ERROR YES)
    set(DOXYGEN_WARN_IF_NO_PARAMDOC YES)
    set(DOXYGEN_WARN_AS_ERROR YES)

    # Parallelise
    set(DOXYGEN_NUM_PROC_THREADS 0)  # Auto set based on CPU

    # Graphviz's dot
    set(DOXYGEN_DOT_NUM_THREADS 0)  # Auto set based on CPU
    set(DOXYGEN_DOT_PATH )  # Empty path = search in $PATH

    # Generate command
    doxygen_add_docs(doxygen
                     ALL # Build doxygen on make-all
                     ${ATTO_DOXYGEN_SRC} # List of input files for Doxygen
                     )
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Cannot generate documentation.")
endif (DOXYGEN_FOUND)
