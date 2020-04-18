cmake_minimum_required(VERSION 3.1)

if(DEFINED ENV{NGLDIR})
    message("found define NGLDIR as " $ENV{NGLDIR})
    set(NGLROOT $ENV{NGLDIR})
elseif(NOT DEFINED ENV{NGLDIR})
    #$ENV{HOME} gives you backslashes on windows so default to C drive root
    if(WIN32)
        file (TO_CMAKE_PATH $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL NGLROOT)
		message("setting NGLROOT to " ${NGLROOT})
		set(CMAKE_TOOLCHAIN_FILE "$ENV{HOMEDRIVE}/$ENV{HOMEPATH}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
		set(CMAKE_GENERATOR_PLATFORM x64)
	
	else()
        message("setting NGLROOT to " $ENV{HOME}/NGL/)
        set(NGLROOT $ENV{HOME}/NGL/)
    endif()
endif()

# Name of the project
set(PROJECT_NAME NGLTests)
project(${PROJECT_NAME})
find_package(GTest )
find_package(glfw )
#Bring the headers into the project (local ones)
include_directories(include ${NGLROOT}/include ${NGLROOT}/gl3w ${NGLROOT}/include/fmt )
# use C++ 17
set(CMAKE_CXX_STANDARD 14)
add_definitions(-DUSEGLM -DGLM_ENABLE_EXPERIMENTAL)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

#the file(GLOB...) allows for wildcard additions of our src dir
set(SOURCES 
			${PROJECT_SOURCE_DIR}/main.cpp  
			${PROJECT_SOURCE_DIR}/MessageQueueTests.cpp  
			${PROJECT_SOURCE_DIR}/UtilTests.cpp           
			${PROJECT_SOURCE_DIR}/Vec4Tests.cpp
			${PROJECT_SOURCE_DIR}/Mat2Tests.cpp  
			${PROJECT_SOURCE_DIR}/NGLInitTests.cpp       
			${PROJECT_SOURCE_DIR}/VAOPrimitivesTests.cpp
			${PROJECT_SOURCE_DIR}/Mat3Tests.cpp  
			${PROJECT_SOURCE_DIR}/ObjTests.cpp           
			${PROJECT_SOURCE_DIR}/Vec2Tests.cpp
			${PROJECT_SOURCE_DIR}/Mat4Tests.cpp  
			${PROJECT_SOURCE_DIR}/ShaderLibTests.cpp     
			${PROJECT_SOURCE_DIR}/Vec3Tests.cpp
			${PROJECT_SOURCE_DIR}/RandomTests.cpp
			${PROJECT_SOURCE_DIR}/QuaternionTests.cpp
)


# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Mac build")
	find_library(MACGL OpenGL)
	set ( PROJECT_LINK_LIBS -lNGL ${MACGL} -L/usr/local/lib/ -lgtest)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set ( PROJECT_LINK_LIBS -lNGL -lGL -lpthread -lgtest)
endif()


# define that if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-O2) 


# now add NGL specific values
link_directories( ${NGLROOT}/lib )

# add exe and link libs that must be after the other defines
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS}  glfw)

