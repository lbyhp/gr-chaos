# Install script for directory: /home/edwin/Documents/GNURadio/gr-chaos/grc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_chaotic_seq_source_f.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_CPM_cf.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_CPM_demod_fc.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_CPM2_cf.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_DCSK_mod_cc.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_DCSK_demod_cc.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_chaotic_prefix_bc.xml"
    "/home/edwin/Documents/GNURadio/gr-chaos/grc/chaos_CPM2_demod_fc.xml"
    )
endif()

