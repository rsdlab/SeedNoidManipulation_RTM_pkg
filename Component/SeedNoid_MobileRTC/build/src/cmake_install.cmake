# Install script for directory: /home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedNoid_MobileRTC/src

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC" TYPE SHARED_LIBRARY FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedNoid_MobileRTC/build/src/SeedNoid_MobileRTC.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTC.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC" TYPE EXECUTABLE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedNoid_MobileRTC/build/src/SeedNoid_MobileRTCComp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC/SeedNoid_MobileRTCComp")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-1.1/components/c++/SeedNoid/SeedNoid_MobileRTC" TYPE FILE FILES "/home/rsdlab/SeedNoidManipulation_RTM_pkg/Component/SeedNoid_MobileRTC/RTC.xml")
endif()

