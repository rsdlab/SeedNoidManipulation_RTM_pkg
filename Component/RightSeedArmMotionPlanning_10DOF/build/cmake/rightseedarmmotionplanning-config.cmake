# RightSeedArmMotionPlanning CMake config file
#
# This file sets the following variables:
# RightSeedArmMotionPlanning_FOUND - Always TRUE.
# RightSeedArmMotionPlanning_INCLUDE_DIRS - Directories containing the RightSeedArmMotionPlanning include files.
# RightSeedArmMotionPlanning_IDL_DIRS - Directories containing the RightSeedArmMotionPlanning IDL files.
# RightSeedArmMotionPlanning_LIBRARIES - Libraries needed to use RightSeedArmMotionPlanning.
# RightSeedArmMotionPlanning_DEFINITIONS - Compiler flags for RightSeedArmMotionPlanning.
# RightSeedArmMotionPlanning_VERSION - The version of RightSeedArmMotionPlanning found.
# RightSeedArmMotionPlanning_VERSION_MAJOR - The major version of RightSeedArmMotionPlanning found.
# RightSeedArmMotionPlanning_VERSION_MINOR - The minor version of RightSeedArmMotionPlanning found.
# RightSeedArmMotionPlanning_VERSION_REVISION - The revision version of RightSeedArmMotionPlanning found.
# RightSeedArmMotionPlanning_VERSION_CANDIDATE - The candidate version of RightSeedArmMotionPlanning found.

message(STATUS "Found RightSeedArmMotionPlanning-1.0.0")
set(RightSeedArmMotionPlanning_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(RightSeedArmMotionPlanning_INCLUDE_DIRS
#    "/usr/local/include/rightseedarmmotionplanning-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(RightSeedArmMotionPlanning_IDL_DIRS
#    "/usr/local/include/rightseedarmmotionplanning-1/idl")
set(RightSeedArmMotionPlanning_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(RightSeedArmMotionPlanning_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(RightSeedArmMotionPlanning_LIBRARIES
        "/usr/local//librightseedarmmotionplanning.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(RightSeedArmMotionPlanning_LIBRARIES
        "/usr/local//librightseedarmmotionplanning.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(RightSeedArmMotionPlanning_DEFINITIONS ${<dependency>_DEFINITIONS})

set(RightSeedArmMotionPlanning_VERSION 1.0.0)
set(RightSeedArmMotionPlanning_VERSION_MAJOR 1)
set(RightSeedArmMotionPlanning_VERSION_MINOR 0)
set(RightSeedArmMotionPlanning_VERSION_REVISION 0)
set(RightSeedArmMotionPlanning_VERSION_CANDIDATE )

