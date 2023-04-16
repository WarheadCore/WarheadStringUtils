#
# This file is part of
#

# Set build-directive (used in core to tell which buildtype we used)
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D_BUILD_DIRECTIVE="${CMAKE_BUILD_TYPE}")

set(GCC_EXPECTED_VERSION 10.0.0)

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GCC_EXPECTED_VERSION)
  message(FATAL_ERROR "GCC: requires version ${GCC_EXPECTED_VERSION} to build but found ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(STATUS "GCC: Minimum version required is ${GCC_EXPECTED_VERSION}, found ${CMAKE_CXX_COMPILER_VERSION} - ok!")
endif()

if (PLATFORM EQUAL 32)
  # Required on 32-bit systems to enable SSE2 (standard on x64)
  target_compile_options(warhead-compile-option-interface
    INTERFACE
      -msse2
      -mfpmath=sse)
endif()

target_compile_options(warhead-warning-interface
  INTERFACE
    -W
    -Wall
    -Wextra
    -Winit-self
    -Winvalid-pch
    -Wfatal-errors
    -Woverloaded-virtual)
