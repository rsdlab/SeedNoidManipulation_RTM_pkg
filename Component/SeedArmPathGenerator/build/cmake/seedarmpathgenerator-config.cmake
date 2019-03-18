# SeedArmPathGenerator CMake config file
#
# This file sets the following variables:
# SeedArmPathGenerator_FOUND - Always TRUE.
# SeedArmPathGenerator_INCLUDE_DIRS - Directories containing the SeedArmPathGenerator include files.
# SeedArmPathGenerator_IDL_DIRS - Directories containing the SeedArmPathGenerator IDL files.
# SeedArmPathGenerator_LIBRARIES - Libraries needed to use SeedArmPathGenerator.
# SeedArmPathGenerator_DEFINITIONS - Compiler flags for SeedArmPathGenerator.
# SeedArmPathGenerator_VERSION - The version of SeedArmPathGenerator found.
# SeedArmPathGenerator_VERSION_MAJOR - The major version of SeedArmPathGenerator found.
# SeedArmPathGenerator_VERSION_MINOR - The minor version of SeedArmPathGenerator found.
# SeedArmPathGenerator_VERSION_REVISION - The revision version of SeedArmPathGenerator found.
# SeedArmPathGenerator_VERSION_CANDIDATE - The candidate version of SeedArmPathGenerator found.

message(STATUS "Found SeedArmPathGenerator-1.0.0")
set(SeedArmPathGenerator_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SeedArmPathGenerator_INCLUDE_DIRS
#    "/usr/local/include/seedarmpathgenerator-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SeedArmPathGenerator_IDL_DIRS
#    "/usr/local/include/seedarmpathgenerator-1/idl")
set(SeedArmPathGenerator_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SeedArmPathGenerator_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(SeedArmPathGenerator_LIBRARIES
        "/usr/local//libseedarmpathgenerator.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SeedArmPathGenerator_LIBRARIES
        "/usr/local//libseedarmpathgenerator.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SeedArmPathGenerator_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SeedArmPathGenerator_VERSION 1.0.0)
set(SeedArmPathGenerator_VERSION_MAJOR 1)
set(SeedArmPathGenerator_VERSION_MINOR 0)
set(SeedArmPathGenerator_VERSION_REVISION 0)
set(SeedArmPathGenerator_VERSION_CANDIDATE )

