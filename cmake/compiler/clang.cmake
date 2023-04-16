#
# This file is part of
#

# Set build-directive (used in core to tell which buildtype we used)
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D_BUILD_DIRECTIVE="${CMAKE_BUILD_TYPE}")

set(CLANG_EXPECTED_VERSION 11.0.0)

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS CLANG_EXPECTED_VERSION)
  message(FATAL_ERROR "Clang: requires version ${CLANG_EXPECTED_VERSION} to build but found ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(STATUS "Clang: Minimum version required is ${CLANG_EXPECTED_VERSION}. Found ${CMAKE_CXX_COMPILER_VERSION} - OK!")
endif()

target_compile_options(warhead-warning-interface
  INTERFACE
    -W
    -Wall
    -Wextra
    -Winit-self
    -Wfatal-errors
    -Wno-mismatched-tags
    -Woverloaded-virtual)
