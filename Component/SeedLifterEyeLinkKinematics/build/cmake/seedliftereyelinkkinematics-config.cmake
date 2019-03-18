# SeedLifterEyeLinkKinematics CMake config file
#
# This file sets the following variables:
# SeedLifterEyeLinkKinematics_FOUND - Always TRUE.
# SeedLifterEyeLinkKinematics_INCLUDE_DIRS - Directories containing the SeedLifterEyeLinkKinematics include files.
# SeedLifterEyeLinkKinematics_IDL_DIRS - Directories containing the SeedLifterEyeLinkKinematics IDL files.
# SeedLifterEyeLinkKinematics_LIBRARIES - Libraries needed to use SeedLifterEyeLinkKinematics.
# SeedLifterEyeLinkKinematics_DEFINITIONS - Compiler flags for SeedLifterEyeLinkKinematics.
# SeedLifterEyeLinkKinematics_VERSION - The version of SeedLifterEyeLinkKinematics found.
# SeedLifterEyeLinkKinematics_VERSION_MAJOR - The major version of SeedLifterEyeLinkKinematics found.
# SeedLifterEyeLinkKinematics_VERSION_MINOR - The minor version of SeedLifterEyeLinkKinematics found.
# SeedLifterEyeLinkKinematics_VERSION_REVISION - The revision version of SeedLifterEyeLinkKinematics found.
# SeedLifterEyeLinkKinematics_VERSION_CANDIDATE - The candidate version of SeedLifterEyeLinkKinematics found.

message(STATUS "Found SeedLifterEyeLinkKinematics-1.0.0")
set(SeedLifterEyeLinkKinematics_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SeedLifterEyeLinkKinematics_INCLUDE_DIRS
#    "/usr/local/include/seedliftereyelinkkinematics-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SeedLifterEyeLinkKinematics_IDL_DIRS
#    "/usr/local/include/seedliftereyelinkkinematics-1/idl")
set(SeedLifterEyeLinkKinematics_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SeedLifterEyeLinkKinematics_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(SeedLifterEyeLinkKinematics_LIBRARIES
        "/usr/local//libseedliftereyelinkkinematics.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SeedLifterEyeLinkKinematics_LIBRARIES
        "/usr/local//libseedliftereyelinkkinematics.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SeedLifterEyeLinkKinematics_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SeedLifterEyeLinkKinematics_VERSION 1.0.0)
set(SeedLifterEyeLinkKinematics_VERSION_MAJOR 1)
set(SeedLifterEyeLinkKinematics_VERSION_MINOR 0)
set(SeedLifterEyeLinkKinematics_VERSION_REVISION 0)
set(SeedLifterEyeLinkKinematics_VERSION_CANDIDATE )

