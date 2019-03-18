# SeedUpperBodyTestController CMake config file
#
# This file sets the following variables:
# SeedUpperBodyTestController_FOUND - Always TRUE.
# SeedUpperBodyTestController_INCLUDE_DIRS - Directories containing the SeedUpperBodyTestController include files.
# SeedUpperBodyTestController_IDL_DIRS - Directories containing the SeedUpperBodyTestController IDL files.
# SeedUpperBodyTestController_LIBRARIES - Libraries needed to use SeedUpperBodyTestController.
# SeedUpperBodyTestController_DEFINITIONS - Compiler flags for SeedUpperBodyTestController.
# SeedUpperBodyTestController_VERSION - The version of SeedUpperBodyTestController found.
# SeedUpperBodyTestController_VERSION_MAJOR - The major version of SeedUpperBodyTestController found.
# SeedUpperBodyTestController_VERSION_MINOR - The minor version of SeedUpperBodyTestController found.
# SeedUpperBodyTestController_VERSION_REVISION - The revision version of SeedUpperBodyTestController found.
# SeedUpperBodyTestController_VERSION_CANDIDATE - The candidate version of SeedUpperBodyTestController found.

message(STATUS "Found SeedUpperBodyTestController-1.0.0")
set(SeedUpperBodyTestController_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SeedUpperBodyTestController_INCLUDE_DIRS
#    "/usr/local/include/seedupperbodytestcontroller-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SeedUpperBodyTestController_IDL_DIRS
#    "/usr/local/include/seedupperbodytestcontroller-1/idl")
set(SeedUpperBodyTestController_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SeedUpperBodyTestController_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(SeedUpperBodyTestController_LIBRARIES
        "/usr/local//libseedupperbodytestcontroller.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SeedUpperBodyTestController_LIBRARIES
        "/usr/local//libseedupperbodytestcontroller.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SeedUpperBodyTestController_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SeedUpperBodyTestController_VERSION 1.0.0)
set(SeedUpperBodyTestController_VERSION_MAJOR 1)
set(SeedUpperBodyTestController_VERSION_MINOR 0)
set(SeedUpperBodyTestController_VERSION_REVISION 0)
set(SeedUpperBodyTestController_VERSION_CANDIDATE )

