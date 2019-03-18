# SeedUpperBodyRTC CMake config file
#
# This file sets the following variables:
# SeedUpperBodyRTC_FOUND - Always TRUE.
# SeedUpperBodyRTC_INCLUDE_DIRS - Directories containing the SeedUpperBodyRTC include files.
# SeedUpperBodyRTC_IDL_DIRS - Directories containing the SeedUpperBodyRTC IDL files.
# SeedUpperBodyRTC_LIBRARIES - Libraries needed to use SeedUpperBodyRTC.
# SeedUpperBodyRTC_DEFINITIONS - Compiler flags for SeedUpperBodyRTC.
# SeedUpperBodyRTC_VERSION - The version of SeedUpperBodyRTC found.
# SeedUpperBodyRTC_VERSION_MAJOR - The major version of SeedUpperBodyRTC found.
# SeedUpperBodyRTC_VERSION_MINOR - The minor version of SeedUpperBodyRTC found.
# SeedUpperBodyRTC_VERSION_REVISION - The revision version of SeedUpperBodyRTC found.
# SeedUpperBodyRTC_VERSION_CANDIDATE - The candidate version of SeedUpperBodyRTC found.

message(STATUS "Found SeedUpperBodyRTC-1.0.0")
set(SeedUpperBodyRTC_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SeedUpperBodyRTC_INCLUDE_DIRS
#    "/usr/local/include/seedupperbodyrtc-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SeedUpperBodyRTC_IDL_DIRS
#    "/usr/local/include/seedupperbodyrtc-1/idl")
set(SeedUpperBodyRTC_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SeedUpperBodyRTC_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(SeedUpperBodyRTC_LIBRARIES
        "/usr/local//libseedupperbodyrtc.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SeedUpperBodyRTC_LIBRARIES
        "/usr/local//libseedupperbodyrtc.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SeedUpperBodyRTC_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SeedUpperBodyRTC_VERSION 1.0.0)
set(SeedUpperBodyRTC_VERSION_MAJOR 1)
set(SeedUpperBodyRTC_VERSION_MINOR 0)
set(SeedUpperBodyRTC_VERSION_REVISION 0)
set(SeedUpperBodyRTC_VERSION_CANDIDATE )

