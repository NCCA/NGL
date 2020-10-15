cmake_minimum_required(VERSION 3.2)

# Name of the project
project(NGLTestBuild VERSION 8.0 LANGUAGES CXX)
# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(IlmBase CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

#Bring the headers into the project (local ones)
include_directories(include ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/gl3w  )
add_definitions(-DUSEGLM -DGLM_ENABLE_EXPERIMENTAL)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)
#This defines the image lib to use by default use QIMAGE, I need to fix this for the others
add_definitions(-DUSEOIIO)
#This defines that we are using the header only version of the fmt lib
add_definitions(-DFMT_HEADER_ONLY)
add_definitions(-DUSEGLM)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

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
	set ( PROJECT_LINK_LIBS -lNGL ${MACGL})

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set ( PROJECT_LINK_LIBS -L/home/jmacey/NGL/lib -lNGL -lGL -lpthread )
endif()


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(WIN32)
    #Not defined in msvc compiler for cmaths so must set definition manually here
    add_definitions(-D_USE_MATH_DEFINES)

    add_definitions(-DNOMINMAX)
    add_definitions(-DNO_DLL)
else()
    #Not a defined option for msvc - fine for gcc and clang
    set(CMAKE_CXX_FLAGS "-Wno-register")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
endif()


# now add NGL specific values
# add exe and link libs that must be after the other defines
add_executable(NGLTests ${SOURCES})

link_directories( ${NGLROOT}/lib )
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)

target_link_libraries(NGLTests PRIVATE glfw PRIVATE GTest::gtest  )
#target_link_libraries(NGLTests PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(NGLTests PRIVATE OpenImageIO::OpenImageIO)

# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     message("Doing mac OpenGL")
		 find_library(MACGL OpenGL)
		 add_definitions(-DGL_SILENCE_DEPRECATION)
    set(EXTRALIBS  ${MACGL})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	target_link_libraries( NGLTests PRIVATE  $(HOMEDRIVE)\\$(HOMEPATH)\\NGL\\lib\\NGL.lib )
else()
target_link_libraries(NGLTests PRIVATE  NGL PRIVATE ${EXTRALIBS} )

endif()

#target_link_libraries(${NGLTests} ${PROJECT_LINK_LIBS} )
gtest_discover_tests(NGLTests)


add_custom_target(CopyTestfiles ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/files
		${CMAKE_BINARY_DIR}/tests/files
		COMMENT "Copy Test files to build directory"
		)
		
#gtest_add_tests(TARGET NGLTests TEST_PREFIX Vec3.)
#add_test(NAME monolithic COMMAND NGLTests)