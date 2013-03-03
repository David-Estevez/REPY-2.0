# Verbose or not verbose
IF($ENV{VERBOSE})
	MESSAGE(STATUS "Verbose mode on")
ELSE($ENV{VERBOSE})
	MESSAGE(STATUS "Verbose mode off (type 'VERBOSE=1 cmake .' to enable it)")
ENDIF($ENV{VERBOSE})

# Needed by CMake versione 2.6 or later (Run "cmake --help-policy CMP0003" for more information.)"
# specifically, we are using full-path when possible for linking libraries
# this should be mandatory for packages found using ROOT directive
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Optional flags and configurable stuff in ccmake
# Replacement for manual.cmake
SET(COMPILATION_FLAGS "-W -Wall -O2 -ggdb" CACHE STRING "CMake compilation flags")
SET(CMAKE_BUILD_TYPE "Debug")

# Add REPY module:
ADD_SUBDIRECTORY( "${PROJECT_SOURCE_DIR}/src")
