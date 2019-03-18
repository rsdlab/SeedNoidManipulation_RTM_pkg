# SeedNoid_MobileRTC CMake config file
#
# This file sets the following variables:
# SeedNoid_MobileRTC_FOUND - Always TRUE.
# SeedNoid_MobileRTC_INCLUDE_DIRS - Directories containing the SeedNoid_MobileRTC include files.
# SeedNoid_MobileRTC_IDL_DIRS - Directories containing the SeedNoid_MobileRTC IDL files.
# SeedNoid_MobileRTC_LIBRARIES - Libraries needed to use SeedNoid_MobileRTC.
# SeedNoid_MobileRTC_DEFINITIONS - Compiler flags for SeedNoid_MobileRTC.
# SeedNoid_MobileRTC_VERSION - The version of SeedNoid_MobileRTC found.
# SeedNoid_MobileRTC_VERSION_MAJOR - The major version of SeedNoid_MobileRTC found.
# SeedNoid_MobileRTC_VERSION_MINOR - The minor version of SeedNoid_MobileRTC found.
# SeedNoid_MobileRTC_VERSION_REVISION - The revision version of SeedNoid_MobileRTC found.
# SeedNoid_MobileRTC_VERSION_CANDIDATE - The candidate version of SeedNoid_MobileRTC found.

message(STATUS "Found SeedNoid_MobileRTC-1.2.0")
set(SeedNoid_MobileRTC_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SeedNoid_MobileRTC_INCLUDE_DIRS
#    "/usr/local/include/seednoid_mobilertc-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SeedNoid_MobileRTC_IDL_DIRS
#    "/usr/local/include/seednoid_mobilertc-1/idl")
set(SeedNoid_MobileRTC_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SeedNoid_MobileRTC_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(SeedNoid_MobileRTC_LIBRARIES
        "/usr/local//libseednoid_mobilertc.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SeedNoid_MobileRTC_LIBRARIES
        "/usr/local//libseednoid_mobilertc.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SeedNoid_MobileRTC_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SeedNoid_MobileRTC_VERSION 1.2.0)
set(SeedNoid_MobileRTC_VERSION_MAJOR 1)
set(SeedNoid_MobileRTC_VERSION_MINOR 2)
set(SeedNoid_MobileRTC_VERSION_REVISION 0)
set(SeedNoid_MobileRTC_VERSION_CANDIDATE )

