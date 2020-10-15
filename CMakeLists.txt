#-------------------------------------------------------------------------------------------
# as much as possible I will use best practice as outlined in the book "Profession cmake"
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

#-------------------------------------------------------------------------------------------
# Setup the project and languages required. Note version number is NGL version
#-------------------------------------------------------------------------------------------

project(AllNGL VERSION 8.0 LANGUAGES CXX C)
add_subdirectory(NGL)
#add_subdirectory(tests)
#if(!WIN32)
#    add_subdirectory(PyNGL)
#endif()
