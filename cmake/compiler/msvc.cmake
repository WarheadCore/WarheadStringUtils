#
# This file is part of
#

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MSVC_EXPECTED_VERSION 19.32)
set(MSVC_EXPECTED_VERSION_STRING "Microsoft Visual Studio 2022 17.2")

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS MSVC_EXPECTED_VERSION)
  message(FATAL_ERROR "MSVC: Requires version ${MSVC_EXPECTED_VERSION} (${MSVC_EXPECTED_VERSION_STRING}) to build but found ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(STATUS "MSVC: Minimum version required is ${MSVC_EXPECTED_VERSION}, found ${CMAKE_CXX_COMPILER_VERSION} - ok!")
endif()

# CMake sets warning flags by default, however we manage it manually
# for different core and dependency targets
string(REGEX REPLACE "/W[0-4] " "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Search twice, once for space after /W argument,
# once for end of line as CMake regex has no \b
string(REGEX REPLACE "/W[0-4]$" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "/W[0-4] " "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string(REGEX REPLACE "/W[0-4]$" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

# https://tinyurl.com/jxnc4s83
target_compile_options(warhead-compile-option-interface
  INTERFACE
    /utf-8)

# disable permissive mode to make msvc more eager to reject code that other compilers don't already accept
target_compile_options(warhead-compile-option-interface
  INTERFACE
    /permissive-)

if(PLATFORM EQUAL 64)
  # This definition is necessary to work around a bug with Intellisense described
  # here: http://tinyurl.com/2cb428.  Syntax highlighting is important for proper
  # debugger functionality.
  target_compile_definitions(warhead-compile-option-interface
    INTERFACE
      -D_WIN64)
  message(STATUS "MSVC: 64-bit platform, enforced -D_WIN64 parameter")
else()
  # mark 32 bit executables large address aware so they can use > 2GB address space
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
  message(STATUS "MSVC: Enabled large address awareness")

  target_compile_options(warhead-compile-option-interface
    INTERFACE
      /arch:SSE2)
  message(STATUS "MSVC: Enabled SSE2 support")
endif()

# Set build-directive (used in core to tell which buildtype we used)
# msbuild/devenv don't set CMAKE_MAKE_PROGRAM, you can choose build type from a dropdown after generating projects
if("${CMAKE_MAKE_PROGRAM}" MATCHES "MSBuild")
  target_compile_definitions(warhead-compile-option-interface
    INTERFACE
      -D_BUILD_DIRECTIVE="$(ConfigurationName)")
else()
  # while all make-like generators do (nmake, ninja)
  target_compile_definitions(warhead-compile-option-interface
    INTERFACE
      -D_BUILD_DIRECTIVE="${CMAKE_BUILD_TYPE}")
endif()

# multithreaded compiling on VS
target_compile_options(warhead-compile-option-interface
  INTERFACE
    /MP)

if((PLATFORM EQUAL 64) OR BUILD_SHARED_LIBS)
  # Enable extended object support
  target_compile_options(warhead-compile-option-interface
    INTERFACE
      /bigobj)

  message(STATUS "MSVC: Enabled increased number of sections in object files")
endif()

# /Zc:throwingNew.
# When you specify Zc:throwingNew on the command line, it instructs the compiler to assume
# that the program will eventually be linked with a conforming operator new implementation,
# and can omit all of these extra null checks from your program.
# makes this flag a requirement to build WH at all
target_compile_options(warhead-compile-option-interface
  INTERFACE
    /Zc:throwingNew)

# Define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES - eliminates the warning by changing the strcpy call to strcpy_s, which prevents buffer overruns
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
message(STATUS "MSVC: Overloaded standard names")

# Ignore warnings about older, less secure functions
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D_CRT_SECURE_NO_WARNINGS)
message(STATUS "MSVC: Disabled NON-SECURE warnings")

# Ignore warnings about POSIX deprecation
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D_CRT_NONSTDC_NO_WARNINGS)
message(STATUS "MSVC: Disabled POSIX warnings")

# Ignore warnings about INTMAX_MAX
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -D__STDC_LIMIT_MACROS)
message(STATUS "MSVC: Disabled INTMAX_MAX warnings")

# Ignore specific warnings
target_compile_options(warhead-compile-option-interface
  INTERFACE
    /wd4351  # C4351: new behavior: elements of array 'x' will be default initialized
    /wd4091) # C4091: 'typedef ': ignored on left of '' when no variable is declared

# Define NOMINMAX
target_compile_definitions(warhead-compile-option-interface
  INTERFACE
    -DNOMINMAX)
message(STATUS "MSVC: Enable NOMINMAX")
