INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src/servos" "${PROJECT_SOURCE_DIR}/src/boards")
ADD_SUBDIRECTORY( boards)
ADD_SUBDIRECTORY( servos)

# Functions to save scad files
ADD_LIBRARY( UTILS utils.cpp)

# Main program
ADD_EXECUTABLE(REPY-2.0 main.cpp repy_module.cpp)
TARGET_LINK_LIBRARIES(REPY-2.0 OOMLCore OOMLParts OOMLComponents SERVOS BOARDS UTILS)

# Program to generate data for openrave
ADD_EXECUTABLE( openrave openrave.cpp repy_module.cpp)

TARGET_LINK_LIBRARIES( openrave OOMLCore OOMLParts OOMLComponents SERVOS BOARDS UTILS)

INSTALL( TARGETS REPY-2.0 DESTINATION bin)




