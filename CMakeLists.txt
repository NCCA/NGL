cmake_minimum_required(VERSION 3.1)
# Name of the project
project(NGL)
#Bring the headers into the project (local ones)
include_directories(${PROJECT_SOURCE_DIR}/include/ngl)
include_directories(${PROJECT_SOURCE_DIR}/src/ngl)
include_directories(${PROJECT_SOURCE_DIR}/src/shaders)
include_directories(${PROJECT_SOURCE_DIR}/include/fmt)

include_directories(/usr/local/include/)
# Set to C++ 11
set(CMAKE_CXX_STANDARD 11)
# use this to remove any marked as deprecated classes from NGL
add_definitions(-DREMOVEDDEPRECATED)
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
add_definitions(-DQT5BUILD)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)
#This defines the image lib to use by default use QIMAGE, I need to fix this for the others
add_definitions(-DUSEQIMAGE)
#This defines that we are using the header only version of the fmt lib
add_definitions(-DFMT_HEADER_ONLY)




set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/Vec4.cpp
    ${PROJECT_SOURCE_DIR}/src/VAOPrimitives.cpp
    ${PROJECT_SOURCE_DIR}/src/VAOFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/SimpleIndexVAO.cpp
    ${PROJECT_SOURCE_DIR}/src/SimpleVAO.cpp
    ${PROJECT_SOURCE_DIR}/src/AbstractVAO.cpp
    ${PROJECT_SOURCE_DIR}/src/MultiBufferVAO.cpp
    ${PROJECT_SOURCE_DIR}/src/Util.cpp
    ${PROJECT_SOURCE_DIR}/src/Texture.cpp
    ${PROJECT_SOURCE_DIR}/src/SpotLight.cpp
    ${PROJECT_SOURCE_DIR}/src/ShaderLib.cpp
    ${PROJECT_SOURCE_DIR}/src/Transformation.cpp
    ${PROJECT_SOURCE_DIR}/src/RibExport.cpp
    ${PROJECT_SOURCE_DIR}/src/Quaternion.cpp
    ${PROJECT_SOURCE_DIR}/src/PathCamera.cpp
    ${PROJECT_SOURCE_DIR}/src/Obj.cpp
    ${PROJECT_SOURCE_DIR}/src/Mat4.cpp
    ${PROJECT_SOURCE_DIR}/src/Material.cpp
    ${PROJECT_SOURCE_DIR}/src/Light.cpp
    ${PROJECT_SOURCE_DIR}/src/NGLInit.cpp
    ${PROJECT_SOURCE_DIR}/src/Colour.cpp
    ${PROJECT_SOURCE_DIR}/src/Camera.cpp
    ${PROJECT_SOURCE_DIR}/src/NCCABinMesh.cpp
    ${PROJECT_SOURCE_DIR}/src/BezierCurve.cpp
    ${PROJECT_SOURCE_DIR}/src/BBox.cpp
    ${PROJECT_SOURCE_DIR}/src/AbstractMesh.cpp
    ${PROJECT_SOURCE_DIR}/src/Random.cpp
    ${PROJECT_SOURCE_DIR}/src/NCCAPointBake.cpp
    ${PROJECT_SOURCE_DIR}/src/Shader.cpp
    ${PROJECT_SOURCE_DIR}/src/ShaderProgram.cpp
    ${PROJECT_SOURCE_DIR}/src/Plane.cpp
    ${PROJECT_SOURCE_DIR}/src/AABB.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexArrayObject.cpp
    ${PROJECT_SOURCE_DIR}/src/createDefaultVAOs.cpp
    ${PROJECT_SOURCE_DIR}/src/Vec3.cpp
    ${PROJECT_SOURCE_DIR}/src/Vec2.cpp
    ${PROJECT_SOURCE_DIR}/src/Text.cpp
    ${PROJECT_SOURCE_DIR}/src/Mat3.cpp
    ${PROJECT_SOURCE_DIR}/src/AbstractSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/XMLSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/NGLStream.cpp
    ${PROJECT_SOURCE_DIR}/src/Logger.cpp
    ${PROJECT_SOURCE_DIR}/src/Image.cpp
    ${PROJECT_SOURCE_DIR}/glew/glew.c
    ${PROJECT_SOURCE_DIR}/include/ngl/Vec4.h
    ${PROJECT_SOURCE_DIR}/include/ngl/VAOPrimitives.h
    ${PROJECT_SOURCE_DIR}/include/ngl/VAOFactory.h
    ${PROJECT_SOURCE_DIR}/include/ngl/SimpleIndexVAO.h
    ${PROJECT_SOURCE_DIR}/include/ngl/SimpleVAO.h
    ${PROJECT_SOURCE_DIR}/include/ngl/AbstractVAO.h
    ${PROJECT_SOURCE_DIR}/include/ngl/MultiBufferVAO.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Singleton.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Util.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Types.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Texture.h
    ${PROJECT_SOURCE_DIR}/include/ngl/SpotLight.h
    ${PROJECT_SOURCE_DIR}/include/ngl/ShaderLib.h
    ${PROJECT_SOURCE_DIR}/include/ngl/RibExport.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Transformation.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Quaternion.h
    ${PROJECT_SOURCE_DIR}/include/ngl/PathCamera.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Obj.h
    ${PROJECT_SOURCE_DIR}/include/ngl/NGLassert.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Mat4.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Material.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Light.h
    ${PROJECT_SOURCE_DIR}/include/ngl/NGLInit.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Colour.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Camera.h
    ${PROJECT_SOURCE_DIR}/include/ngl/BezierCurve.h
    ${PROJECT_SOURCE_DIR}/include/ngl/NCCABinMesh.h
    ${PROJECT_SOURCE_DIR}/include/ngl/BBox.h
    ${PROJECT_SOURCE_DIR}/include/ngl/AbstractMesh.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Random.h
    ${PROJECT_SOURCE_DIR}/include/ngl/NCCAPointBake.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Shader.h
    ${PROJECT_SOURCE_DIR}/include/ngl/ShaderProgram.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Plane.h
    ${PROJECT_SOURCE_DIR}/include/ngl/AABB.h
    ${PROJECT_SOURCE_DIR}/include/ngl/VertexArrayObject.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Vec3.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Vec2.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Text.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Mat3.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Logger.h
    ${PROJECT_SOURCE_DIR}/include/ngl/Image.h 
    ${PROJECT_SOURCE_DIR}/include/ngl/AbstractSerializer.h
    ${PROJECT_SOURCE_DIR}/include/ngl/XMLSerializer.h
    ${PROJECT_SOURCE_DIR}/include/ngl/NGLStream.h
    ${PROJECT_SOURCE_DIR}/src/shaders/TextShaders.h
    ${PROJECT_SOURCE_DIR}/src/shaders/ColourShaders.h
    ${PROJECT_SOURCE_DIR}/src/shaders/DiffuseShaders.h
    ${PROJECT_SOURCE_DIR}/src/shaders/ToonShaders.h
    ${PROJECT_SOURCE_DIR}/include/ngl/rapidxml/rapidxml.hpp
    ${PROJECT_SOURCE_DIR}/include/ngl/rapidxml/rapidxml_iterators.hpp
    ${PROJECT_SOURCE_DIR}/include/ngl/rapidxml/rapidxml_print.hpp
    ${PROJECT_SOURCE_DIR}/include/ngl/rapidxml/rapidxml_utils.hpp



)


# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions(-DDARWIN)
    find_library(MACGL OpenGL)
    set(PROJECT_LINK_LIBS -lboost_system)
    link_directories(/usr/local/lib/)

    set(EXTRALIBS  ${MACGL})


elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_definitions(-DLINUX)
endif()



# as NGL uses Qt we need to define this flag
# NGL also needs the OpenGL framework from Qt so add it
find_package(Qt5OpenGL)

# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


add_library(NGL SHARED ${SOURCES})

target_link_libraries(NGL Qt5::OpenGL)
target_link_libraries(NGL ${PROJECT_LINK_LIBS} ${EXTRALIBS})

