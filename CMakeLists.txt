#
# This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
#

# Require version Cmake
cmake_minimum_required(VERSION 3.16)
message(STATUS "CMake version: ${CMAKE_VERSION}")

project(WarheadStringUtils)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set RPATH-handing (CMake parameters)
set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)

# set macro-directory
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/macros")

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

include(ConfigureBaseTargets)
include(CheckPlatform)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.9
        GIT_SHALLOW    1)
FetchContent_MakeAvailable(Catch2)

include(CTest)
list(APPEND CMAKE_MODULE_PATH
      "${Catch2_SOURCE_DIR}/contrib")

include(Catch)
add_subdirectory(tests)
