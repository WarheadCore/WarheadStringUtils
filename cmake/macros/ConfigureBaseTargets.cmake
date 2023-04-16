#
# This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
#

set(CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Enabled С++17 standard")

add_library(warhead-compile-option-interface INTERFACE)
add_library(warhead-warning-interface INTERFACE)
add_library(warhead-default-interface INTERFACE)

target_link_libraries(warhead-default-interface
  INTERFACE
    warhead-compile-option-interface)

add_library(warhead-core-interface INTERFACE)
target_link_libraries(warhead-core-interface
  INTERFACE
    warhead-default-interface
    warhead-warning-interface)
