cmake_minimum_required(VERSION 3.1)
project(AllNGL)

add_subdirectory(NGL)
add_subdirectory(tests)
if(!WIN32)
    add_subdirectory(PyNGL)
endif()
