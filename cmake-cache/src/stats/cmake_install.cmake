# Install script for directory: /home/pgz/Escritorio/simulador/simulador-ns3/src/stats

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
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pgz/Escritorio/simulador/simulador-ns3/build/lib/libns3-dev-stats-debug.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so"
         OLD_RPATH "/home/pgz/Escritorio/simulador/simulador-ns3/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3-dev-stats-debug.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/helper/file-helper.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/helper/gnuplot-helper.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/average.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/basic-data-calculators.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/boolean-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/data-calculator.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/data-collection-object.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/data-collector.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/data-output-interface.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/double-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/file-aggregator.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/get-wildcard-matches.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/gnuplot-aggregator.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/gnuplot.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/histogram.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/omnet-data-output.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/stats.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/time-data-calculators.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/time-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/time-series-adaptor.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/uinteger-16-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/uinteger-32-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/src/stats/model/uinteger-8-probe.h"
    "/home/pgz/Escritorio/simulador/simulador-ns3/build/include/ns3/stats-module.h"
    )
endif()
