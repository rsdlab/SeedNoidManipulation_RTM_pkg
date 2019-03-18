# Install script for directory: /home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedUpperBodyTestController/src

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController" TYPE SHARED_LIBRARY FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedUpperBodyTestController/build/src/SeedUpperBodyTestController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestController.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController" TYPE EXECUTABLE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedUpperBodyTestController/build/src/SeedUpperBodyTestControllerComp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController/SeedUpperBodyTestControllerComp")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/Category/SeedUpperBodyTestController" TYPE FILE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedUpperBodyTestController/RTC.xml")
endif()

