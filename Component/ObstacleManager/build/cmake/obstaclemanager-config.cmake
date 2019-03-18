# ObstacleManager CMake config file
#
# This file sets the following variables:
# ObstacleManager_FOUND - Always TRUE.
# ObstacleManager_INCLUDE_DIRS - Directories containing the ObstacleManager include files.
# ObstacleManager_IDL_DIRS - Directories containing the ObstacleManager IDL files.
# ObstacleManager_LIBRARIES - Libraries needed to use ObstacleManager.
# ObstacleManager_DEFINITIONS - Compiler flags for ObstacleManager.
# ObstacleManager_VERSION - The version of ObstacleManager found.
# ObstacleManager_VERSION_MAJOR - The major version of ObstacleManager found.
# ObstacleManager_VERSION_MINOR - The minor version of ObstacleManager found.
# ObstacleManager_VERSION_REVISION - The revision version of ObstacleManager found.
# ObstacleManager_VERSION_CANDIDATE - The candidate version of ObstacleManager found.

message(STATUS "Found ObstacleManager-1.0.0")
set(ObstacleManager_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ObstacleManager_INCLUDE_DIRS
#    "/usr/local/include/obstaclemanager-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ObstacleManager_IDL_DIRS
#    "/usr/local/include/obstaclemanager-1/idl")
set(ObstacleManager_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ObstacleManager_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ObstacleManager_LIBRARIES
        "/usr/local//libobstaclemanager.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ObstacleManager_LIBRARIES
        "/usr/local//libobstaclemanager.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ObstacleManager_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ObstacleManager_VERSION 1.0.0)
set(ObstacleManager_VERSION_MAJOR 1)
set(ObstacleManager_VERSION_MINOR 0)
set(ObstacleManager_VERSION_REVISION 0)
set(ObstacleManager_VERSION_CANDIDATE )

