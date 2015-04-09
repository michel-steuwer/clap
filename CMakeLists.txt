cmake_minimum_required(VERSION 2.8)
project(HeliumPP)
set(PROJECT_MAJOR 0)
set(PROJECT_MINOR 0)
set(PROJECT_PATCH 0)

include_directories(include/)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

set(LIBRARY_NAME HeliumPP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fvisibility=hidden") 

set(FEATURES "")

option(DEBUG_TRACK_OVERHEAD "Measure the overheads of the profiler's hooks." OFF)
if(DEBUG_TRACK_OVERHEAD)
  set(FEATURES "${FEATURES}
  #define DEBUG_TRACK_OVERHEAD")
endif()

option(TRACK_REFCOUNT "Track retain/realease for OpenCL objects." OFF)
if(TRACK_REFCOUNT)
  set(FEATURES "${FEATURES}
  #define TRACK_REFCOUNT")
endif()

option(TRACK_EVENTS "Force timing in all queues and force events to all actions." OFF)
if(TRACK_EVENTS)
  set(FEATURES "${FEATURES}
  #define TRACK_EVENTS")
endif()

option(TRACK_API_CALLS "Time each OpenCL function call and their number of instances." OFF)
if(TRACK_API_CALLS OR DEBUG_TRACK_OVERHEAD)
  set(FEATURES "${FEATURES}
  #define TRACK_API_CALLS")
endif()

option(TRACK_KERNEL_ARGUMENTS "Record the kernel arguments for each instance." OFF)
if(TRACK_KERNEL_ARGUMENTS)
  set(FEATURES "${FEATURES}
  #define TRACK_KERNEL_ARGUMENTS")
endif()

option(TRACK_PROGRAMS "Track program sources or binaries." OFF)
if(TRACK_PROGRAMS)
  set(FEATURES "${FEATURES}
  #define TRACK_PROGRAMS")
endif()

configure_file(include/features.h.in include/feature.h)

ADD_DEFINITIONS(-D_GNU_SOURCE)
ADD_DEFINITIONS(-DVERBOSE)
FILE(GLOB_RECURSE ALL_SOURCES src/*.cpp)
add_library(${LIBRARY_NAME} SHARED 
	${ALL_SOURCES}
)

install_targets("/lib/" ${LIBRARY_NAME})

