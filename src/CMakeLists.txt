# You may have to replace /usr/include/ooml for the corresponding folder on your computer
SET(OOML_INCLUDE_DIR "/usr/include/ooml" CACHE STRING "OOML Include Dir")
SET(OOML_LINK_DIR "/usr/lib" CACHE STRING "OOML Libraries Directory")

INCLUDE_DIRECTORIES(${OOML_INCLUDE_DIR})
LINK_DIRECTORIES(${OOML_LINK_DIR})

# Main project declaration
PROJECT(REPY-2.0)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src/servos" "${PROJECT_SOURCE_DIR}/src/boards")
ADD_SUBDIRECTORY( boards)
ADD_SUBDIRECTORY( servos)

ADD_EXECUTABLE(REPY-2.0 main.cpp repy_module.cpp)
TARGET_LINK_LIBRARIES(REPY-2.0 OOMLCore OOMLParts OOMLComponents SERVOS BOARDS)

ADD_EXECUTABLE( EXPERIMENTAL experimental.cpp repy_module.cpp)
TARGET_LINK_LIBRARIES( EXPERIMENTAL OOMLCore OOMLParts OOMLComponents SERVOS BOARDS)



