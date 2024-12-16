# Atto Cmake configuration file
# Copyright © 2019-2021, Matjaž Guštin <dev@matjaz.it> <https://matjaz.it>
# All rights reserved.
# This file is part of the Atto project which is released under
# the BSD 3-clause license.
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.9)  # For FindDoxygen
project(Atto
        VERSION 1.4.0
        LANGUAGES C
        DESCRIPTION
        "The microscopic C test framework")

# -----------------------------------------------------------------------------
# Build targets
# -----------------------------------------------------------------------------
add_executable(atto_selftest
               src/atto.h
               src/atto.c
               tst/selftest.c)
target_include_directories(atto_selftest PRIVATE src/)
if (NOT MSVC)
target_link_libraries(atto_selftest PRIVATE m)
endif()

enable_testing()
add_test(NAME atto_selftest COMMAND atto_selftest)

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
    doxygen_add_docs(atto_doxygen
                     src/atto.h LICENSE.md CHANGELOG.md README.md
                     # List of input files for Doxygen
                     )
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Cannot generate documentation.")
endif (DOXYGEN_FOUND)
