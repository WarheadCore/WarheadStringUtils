#
# This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
#

set(TEST_SOURCES
    WarheadStringUtils.cpp
    main.cpp)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests
  PRIVATE
    warhead-core-interface
    wsu
    Catch2::Catch2)

catch_discover_tests(tests)

set_target_properties(tests
  PROPERTIES
    FOLDER
      "tests")
