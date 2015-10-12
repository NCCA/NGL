# Copyright (c) 2015, Christoph Russ.

find_path( NGL_INCLUDE_DIR ngl/NGLInit.h
  $ENV{HOME}/NGL/include
  $ENV{HOME}/ngl/include
  $ENV{NGL_INCLUDE_PATH}
  ${NGL_INSTALL_PATH}/include
  /usr/local/include
  /usr/include
  /opt/local/include
  /opt/include
  )

# Support preference of static libs by adjusting CMAKE_FIND_LIBRARY_SUFFIXES
if( NGL_USE_STATIC_LIBS )
  set( NGL_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
  if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
  else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a )
  endif()
endif()

# try to find libs
find_library( NGL_LIBRARY NGL
  $ENV{HOME}/NGL/lib
  $ENV{HOME}/ngl/lib
  $ENV{NGL_LIBRARY_PATH}
  ${NGL_INSTALL_PATH}/lib
  /usr/local/lib
  /usr/lib
  /opt/local/lib
  /opt/lib
  )

# Restore the original find library ordering
if( NGL_USE_STATIC_LIBS )
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${NGL_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

# did we find everything?
include( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "NGL" DEFAULT_MSG
  NGL_INCLUDE_DIR
  NGL_LIBRARY
  )
