cmake_minimum_required(VERSION 3.2)
# Name of the project

project(NGLLibBuild)


find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(IlmBase CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
find_package(RapidJSON CONFIG REQUIRED)


if(WIN32)
    #Not defined in msvc compiler for cmaths so must set definition manually here
    add_definitions(-D_USE_MATH_DEFINES)

    #Need to define this when building shared library or suffer dllimport errors
    add_definitions(-DBUILDING_DLL)
else()
    #Not a defined option for msvc - fine for gcc and clang
    set(CMAKE_CXX_FLAGS "-Wno-register")
endif()


#Bring the headers into the project (local ones)
include_directories(${CMAKE_SOURCE_DIR}/include/ngl)
include_directories(${CMAKE_SOURCE_DIR}/src/ngl)
include_directories(${CMAKE_SOURCE_DIR}/src/shaders)
include_directories(${CMAKE_SOURCE_DIR}/gl3w)
include_directories(/usr/local/include/)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)
#This defines the image lib to use by default use QIMAGE, I need to fix this for the others
add_definitions(-DUSEOIIO)
add_definitions(-DUSEGLM)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

add_library(NGL SHARED)

target_sources(NGL PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Vec4.cpp
    ${CMAKE_SOURCE_DIR}/src/VAOPrimitives.cpp
    ${CMAKE_SOURCE_DIR}/src/VAOFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/SimpleIndexVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/SimpleVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/AbstractVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/MultiBufferVAO.cpp
    ${CMAKE_SOURCE_DIR}/src/Util.cpp
    ${CMAKE_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_SOURCE_DIR}/src/ShaderLib.cpp
    ${CMAKE_SOURCE_DIR}/src/Transformation.cpp
    ${CMAKE_SOURCE_DIR}/src/RibExport.cpp
    ${CMAKE_SOURCE_DIR}/src/Quaternion.cpp
    ${CMAKE_SOURCE_DIR}/src/Obj.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat4.cpp
    ${CMAKE_SOURCE_DIR}/src/NGLInit.cpp
    ${CMAKE_SOURCE_DIR}/src/NCCABinMesh.cpp
    ${CMAKE_SOURCE_DIR}/src/BezierCurve.cpp
    ${CMAKE_SOURCE_DIR}/src/BBox.cpp
    ${CMAKE_SOURCE_DIR}/src/AbstractMesh.cpp
    ${CMAKE_SOURCE_DIR}/src/Random.cpp
    ${CMAKE_SOURCE_DIR}/src/NCCAPointBake.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/ShaderProgram.cpp
    ${CMAKE_SOURCE_DIR}/src/Plane.cpp
    ${CMAKE_SOURCE_DIR}/src/AABB.cpp
    ${CMAKE_SOURCE_DIR}/src/createDefaultVAOs.cpp
    ${CMAKE_SOURCE_DIR}/src/Vec3.cpp
    ${CMAKE_SOURCE_DIR}/src/Vec2.cpp
    ${CMAKE_SOURCE_DIR}/src/Text.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat3.cpp
    ${CMAKE_SOURCE_DIR}/src/Mat2.cpp
    ${CMAKE_SOURCE_DIR}/src/NGLStream.cpp
    ${CMAKE_SOURCE_DIR}/src/Image.cpp
    ${CMAKE_SOURCE_DIR}/src/Types.cpp
    ${CMAKE_SOURCE_DIR}/src/pystring.cpp
    ${CMAKE_SOURCE_DIR}/src/MessageQueue/AbstractMessageConsumer.cpp 
    ${CMAKE_SOURCE_DIR}/src/MessageQueue/NGLMessage.cpp 
    ${CMAKE_SOURCE_DIR}/src/MessageQueue/FileConsumer.cpp 
    ${CMAKE_SOURCE_DIR}/gl3w/gl3w.c
    ${CMAKE_SOURCE_DIR}/gl3w/gl3w.h
    ${CMAKE_SOURCE_DIR}/gl3w/glcorearb.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec4.h
    ${CMAKE_SOURCE_DIR}/include/ngl/VAOPrimitives.h
    ${CMAKE_SOURCE_DIR}/include/ngl/VAOFactory.h
    ${CMAKE_SOURCE_DIR}/include/ngl/SimpleIndexVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/SimpleVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AbstractVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/MultiBufferVAO.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Util.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Types.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Texture.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderLib.h
    ${CMAKE_SOURCE_DIR}/include/ngl/RibExport.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Transformation.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Quaternion.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Obj.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLassert.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat4.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLInit.h
    ${CMAKE_SOURCE_DIR}/include/ngl/BezierCurve.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NCCABinMesh.h
    ${CMAKE_SOURCE_DIR}/include/ngl/BBox.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AbstractMesh.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Random.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NCCAPointBake.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Shader.h
    ${CMAKE_SOURCE_DIR}/include/ngl/ShaderProgram.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Plane.h
    ${CMAKE_SOURCE_DIR}/include/ngl/AABB.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec3.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Vec2.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Text.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat3.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Mat2.h
    ${CMAKE_SOURCE_DIR}/include/ngl/pystring.h
    ${CMAKE_SOURCE_DIR}/include/ngl/Image.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLStream.h
    ${CMAKE_SOURCE_DIR}/include/ngl/NGLStream.h
    ${CMAKE_SOURCE_DIR}/include/ngl/MessageQueue/AbstractMessageConsumer.h 
    ${CMAKE_SOURCE_DIR}/include/ngl/MessageQueue/FileConsumer.h 
    ${CMAKE_SOURCE_DIR}/include/ngl/MessageQueue/STDERRConsumer.h 
    ${CMAKE_SOURCE_DIR}/include/ngl/MessageQueue/STDOutConsumer.h    
    ${CMAKE_SOURCE_DIR}/src/shaders/TextShaders.h
    ${CMAKE_SOURCE_DIR}/src/shaders/ColourShaders.h
    ${CMAKE_SOURCE_DIR}/src/shaders/DiffuseShaders.h
)


# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(MACGL OpenGL)
    set(EXTRALIBS  ${MACGL})


elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()


# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_SOURCE_DIR}/lib/libNGL*")


target_link_libraries(NGL PRIVATE glm)
target_link_libraries(NGL PRIVATE fmt::fmt-header-only)
target_link_libraries(NGL ${PROJECT_LINK_LIBS} ${EXTRALIBS})
target_link_libraries(NGL PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(NGL PRIVATE  IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
target_link_libraries(NGL PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)
target_include_directories(NGL PRIVATE ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(NGL PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
