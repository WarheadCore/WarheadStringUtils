#
# This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
#

set(WSU_HEADERS
    ../include/Warhead/Algorithm.h
    ../include/Warhead/Convert.h
    ../include/Warhead/Tokenizer.h)

set(WSU_SOURCES
  Algorithm.cpp
  Tokenizer.cpp)

add_library(wsu ${WSU_SOURCES} ${WSU_HEADERS})

target_include_directories(wsu
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(wsu
  PRIVATE
    warhead-core-interface)
