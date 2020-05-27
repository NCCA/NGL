cmake_minimum_required(VERSION 3.2)
#-------------------------------------------------------------------------------------------
# as much as possible I will use best practice as outlined in the book "Profession cmake"
#-------------------------------------------------------------------------------------------
project(AllNGL VERSION 8.0 LANGUAGES CXX C)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for VCPKG_ROOT
#-------------------------------------------------------------------------------------------
message("Testing  for vcpkg " $ENV{VCPKG_ROOT})
if( $ENV{VCPKG_ROOT} NOT "" AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable not set")
endif()


add_subdirectory(NGL)
#add_subdirectory(tests)
#if(!WIN32)
#    add_subdirectory(PyNGL)
#endif()
