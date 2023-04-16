#
# This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
#

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(PLATFORM 64)
  message(STATUS "Detected 64-bit platform")
else()
  set(PLATFORM 32)
  message(STATUS "Detected 32-bit platform")
endif()

if (UNIX)
# configure uninstaller
configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.in.cmake"
  "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
  @ONLY)

message(STATUS "UNIX: Configuring uninstall target")

# create uninstaller target (allows for using "make uninstall")
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake" )
endif()

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0601)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-DNOMINMAX)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/msvc.cmake)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/clang.cmake)
  endif()
elseif(UNIX)
  if(CMAKE_C_COMPILER MATCHES "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/gcc.cmake)
  elseif(CMAKE_C_COMPILER MATCHES "clang" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/clang.cmake)
  endif()
endif()
