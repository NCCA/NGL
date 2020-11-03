cmake_minimum_required(VERSION 3.1)
# Name of the project
project(PyNGLBuild)
find_package( PythonInterp 3 REQUIRED )
find_package( PythonLibs 3 REQUIRED )
find_package(pybind11 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(IlmBase CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
find_package(RapidJSON CONFIG REQUIRED)


add_library(pyngl SHARED ${SOURCES})


#Bring the header into the project (local ones)
set(PYSOURCEDIR ${CMAKE_SOURCE_DIR}/PyNGL/src)
include_directories(${CMAKE_SOURCE_DIR}/PyNGL/)
include_directories(${CMAKE_SOURCE_DIR}/src/ngl)
include_directories(${CMAKE_SOURCE_DIR}/src/shaders)
include_directories(${CMAKE_SOURCE_DIR}/include/fmt)
include_directories(${CMAKE_SOURCE_DIR}/include/ngl/)
include_directories(${CMAKE_SOURCE_DIR}/gl3w)
include_directories(/usr/local/include/)
include_directories(${PYTHON_INCLUDE_DIRS})

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)
add_definitions(-DPYTHONBUILD)
#This defines the image lib to use by default use OIIO, I need to fix this for the others
add_definitions(-DUSEOIIO)
#This defines that we are using the header only version of the fmt lib
add_definitions(-DFMT_HEADER_ONLY)
add_definitions(-DUSEGLM)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

target_sources(pyngl PRIVATE
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
    ${PYSOURCEDIR}/PyAABB.cpp            
    ${PYSOURCEDIR}/PyNGLInit.cpp         
    ${PYSOURCEDIR}/PyText.cpp
    ${PYSOURCEDIR}/PyAbstractMesh.cpp    
    ${PYSOURCEDIR}/PyObj.cpp             
    ${PYSOURCEDIR}/PyTexture.cpp
    ${PYSOURCEDIR}/PyAbstractVAO.cpp     
    ${PYSOURCEDIR}/PyPlane.cpp           
    ${PYSOURCEDIR}/PythonBindings.cpp
    ${PYSOURCEDIR}/PyBBox.cpp            
    ${PYSOURCEDIR}/PyQuaternion.cpp      
    ${PYSOURCEDIR}/PyTransformation.cpp
    ${PYSOURCEDIR}/PyBezierCurve.cpp     
    ${PYSOURCEDIR}/PyRandom.cpp          
    ${PYSOURCEDIR}/PyUtil.cpp
    ${PYSOURCEDIR}/PyImage.cpp           
    ${PYSOURCEDIR}/PyRibExport.cpp       
    ${PYSOURCEDIR}/PyVAOFactory.cpp
    ${PYSOURCEDIR}/PyMat3.cpp            
    ${PYSOURCEDIR}/PyMat2.cpp            
    ${PYSOURCEDIR}/PyShader.cpp          
    ${PYSOURCEDIR}/PyVAOPrimitives.cpp
    ${PYSOURCEDIR}/PyMat4.cpp            
    ${PYSOURCEDIR}/PyShaderLib.cpp       
    ${PYSOURCEDIR}/PyVec2.cpp
    ${PYSOURCEDIR}/PyMultiBufferVAO.cpp  
    ${PYSOURCEDIR}/PyShaderProgram.cpp   
    ${PYSOURCEDIR}/PyVec3.cpp
    ${PYSOURCEDIR}/PyNCCABinMesh.cpp     
    ${PYSOURCEDIR}/PySimpleIndexVAO.cpp  
    ${PYSOURCEDIR}/PyVec4.cpp
    ${PYSOURCEDIR}/PyNCCAPointBake.cpp   
    ${PYSOURCEDIR}/PySimpleVAO.cpp
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
    set(EXTRALIBS  ${MACGL} -lpython2.7)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()



# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${CMAKE_SOURCE_DIR}/lib)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_SOURCE_DIR}/lib/pyngl.so")


set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

#target_link_libraries(pyngl PRIVATE mylib pybind11::embed pybind11::module pybind11::pybind11)
target_link_libraries(pyngl PRIVATE glm)
target_link_libraries(pyngl PRIVATE fmt::fmt-header-only)
target_link_libraries(pyngl ${PROJECT_LINK_LIBS} ${EXTRALIBS})
target_link_libraries(pyngl PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(pyngl PRIVATE  IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
target_link_libraries(pyngl PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)
target_include_directories(pyngl PRIVATE ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(pyngl PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
