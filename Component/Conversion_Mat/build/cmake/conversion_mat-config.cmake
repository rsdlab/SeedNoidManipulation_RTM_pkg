# Conversion_Mat CMake config file
#
# This file sets the following variables:
# Conversion_Mat_FOUND - Always TRUE.
# Conversion_Mat_INCLUDE_DIRS - Directories containing the Conversion_Mat include files.
# Conversion_Mat_IDL_DIRS - Directories containing the Conversion_Mat IDL files.
# Conversion_Mat_LIBRARIES - Libraries needed to use Conversion_Mat.
# Conversion_Mat_DEFINITIONS - Compiler flags for Conversion_Mat.
# Conversion_Mat_VERSION - The version of Conversion_Mat found.
# Conversion_Mat_VERSION_MAJOR - The major version of Conversion_Mat found.
# Conversion_Mat_VERSION_MINOR - The minor version of Conversion_Mat found.
# Conversion_Mat_VERSION_REVISION - The revision version of Conversion_Mat found.
# Conversion_Mat_VERSION_CANDIDATE - The candidate version of Conversion_Mat found.

message(STATUS "Found Conversion_Mat-1.0.0")
set(Conversion_Mat_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Conversion_Mat_INCLUDE_DIRS
#    "/usr/local/include/conversion_mat-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Conversion_Mat_IDL_DIRS
#    "/usr/local/include/conversion_mat-1/idl")
set(Conversion_Mat_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Conversion_Mat_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Conversion_Mat_LIBRARIES
        "/usr/local//libconversion_mat.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Conversion_Mat_LIBRARIES
        "/usr/local//libconversion_mat.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Conversion_Mat_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Conversion_Mat_VERSION 1.0.0)
set(Conversion_Mat_VERSION_MAJOR 1)
set(Conversion_Mat_VERSION_MINOR 0)
set(Conversion_Mat_VERSION_REVISION 0)
set(Conversion_Mat_VERSION_CANDIDATE )

