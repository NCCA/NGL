#-------------------------------------------------------------------------------------------
# as much as possible I will use best practice as outlined in the book "Profession cmake"
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for VCPKG_ROOT and must be done before starting
# the project as the variables will be used and chached.
#-------------------------------------------------------------------------------------------

# message("Testing  for vcpkg current =" $ENV{VCPKG_ROOT})
# if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
#   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# else()
#     message(FATAL_ERROR "VCPKG_ROOT environment variable not set")
# endif()

#-------------------------------------------------------------------------------------------
# Setup the project and languages required. Note version number is NGL version
#-------------------------------------------------------------------------------------------

project(AllNGL VERSION 8.0 LANGUAGES CXX C)

add_subdirectory(NGL)
#add_subdirectory(tests)
#if(!WIN32)
#    add_subdirectory(PyNGL)
#endif()
