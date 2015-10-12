cmake_minimum_required(VERSION 2.8.11)
# Name of the project
project(NGL)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#######################################################
#######################################################
#Search for dependencies
find_package(Boost COMPONENTS system REQUIRED) #iostreams system filesystem regex thread date_time timer atomic locale graph exception
find_package(GLEW)
find_package(OpenGL REQUIRED)
#####
find_package(OpenImageIO REQUIRED)
if (OpenImageIO_FOUND)
    add_definitions(-DUSEOIIO) #linking doesn't work without this
endif ()
#####
# as NGL uses Qt we need to define this flag
# NGL also needs the OpenGL framework from Qt so add it
find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL REQUIRED)

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})

#c++11 ?
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -fPIC ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}" CACHE STRING "Flags used by the compiler during all build types.")
endif()

#######################################################
#######################################################

include_directories(${Boost_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${OpenImageIO_INCLUDE_DIRS}
)

#Bring the headers into the project (local ones)
include_directories(${PROJECT_SOURCE_DIR}/include/ngl)
include_directories(${PROJECT_SOURCE_DIR}/src/ngl)
include_directories(${PROJECT_SOURCE_DIR}/src/shaders)

# use this to remove any marked as deprecated classes from NGL
add_definitions(-DREMOVEDDEPRECATED)
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
add_definitions(-DQT5BUILD)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)

#######################################################
#######################################################

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/ngl/*.cpp
    # ${PROJECT_SOURCE_DIR}/glew/glew.c
)

list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/src/HoudiniGeo.cpp)

file(GLOB HEADERS
    ${PROJECT_SOURCE_DIR}/src/ngl/*.h
    ${PROJECT_SOURCE_DIR}/include/ngl/*.h
    ${PROJECT_SOURCE_DIR}/src/shaders/*.h
    ${PROJECT_SOURCE_DIR}/include/ngl/rapidxml/*.hpp
)

list(REMOVE_ITEM HEADERS ${PROJECT_SOURCE_DIR}/include/ngl/HoudiniGeo.h)

if(APPLE)
    file(GLOB OBJC_SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.mm
    )
    find_library(COCOA_LIBRARY Cocoa)
    find_library(FOUNDATION_LIBRARY Foundation)
endif()


#######################################################
#######################################################
# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions(-DDARWIN)
    find_library(MACGL OpenGL)
    set(EXTRALIBS  ${MACGL})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_definitions(-DLINUX)
endif()

#######################################################
#######################################################
set(PROJEECT_LIB_DIRS
    ${Boost_LIBRARY_DIRS}
)
set(PROJECT_LINK_LIBS
    ${Boost_LIBRARIES}
    ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
    ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES}
    ${OpenImageIO_LIBRARY}
)

#######################################################
#######################################################
# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(NGL SHARED ${SOURCES} ${OBJC_SOURCES} ${HEADERS})

link_directories(${PROJEECT_LIB_DIRS})
target_link_libraries(NGL ${PROJECT_LINK_LIBS} ${EXTRALIBS})

if(APPLE)
target_link_libraries(NGL
    ${FOUNDATION_LIBRARY} ${COCOA_LIBRARY}
)
endif()
