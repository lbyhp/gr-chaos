# Install script for directory: /home/edwin/Documents/GNURadio/gr-chaos/include/chaos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/edwin/prefix")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/chaos" TYPE FILE FILES
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/api.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_seq_source_f.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_seq_source_f.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_seq_source_f.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_seq_source_f.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_seq_source_f.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/CPM_cf.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/CPM_demod_fc.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/CPM_demod_fc.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/CPM2_cf.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/DCSK_mod_cc.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/DCSK_demod_cc.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/chaotic_prefix_bc.h"
    "/home/edwin/Documents/GNURadio/gr-chaos/include/chaos/CPM2_demod_fc.h"
    )
endif()

