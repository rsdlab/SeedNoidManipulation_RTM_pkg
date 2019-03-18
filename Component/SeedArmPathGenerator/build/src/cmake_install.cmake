# Install script for directory: /home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedArmPathGenerator/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator" TYPE SHARED_LIBRARY FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedArmPathGenerator/build/src/SeedArmPathGenerator.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGenerator.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator" TYPE EXECUTABLE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedArmPathGenerator/build/src/SeedArmPathGeneratorComp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator/SeedArmPathGeneratorComp")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedArmPathGenerator" TYPE FILE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedArmPathGenerator/RTC.xml")
endif()

