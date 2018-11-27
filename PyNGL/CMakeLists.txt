cmake_minimum_required(VERSION 3.1)
# Name of the project
project(PyNGL)
find_package( PythonInterp 2.7 REQUIRED )
find_package( PythonLibs 2.7 REQUIRED )
if(DEFINED ENV{NGLDIR})
    message("found NGLDIR")
    set(NGLROOT $ENV{NGLDIR})
elseif(NOT DEFINED ENV{NGLDIR})
    set(NGLROOT $ENV{HOME}/NGL/)
endif()

#Bring the header into the project (local ones)
set(PYSOURCEDIR ${NGLROOT}/PyNGL/src)
include_directories(${NGLROOT}/PyNGL/)
include_directories(${NGLROOT}/src/ngl)
include_directories(${NGLROOT}/src/shaders)
include_directories(${NGLROOT}/include/fmt)
include_directories(${NGLROOT}/include/ngl/)
include_directories(${NGLROOT}/gl3w)
include_directories(/usr/local/include/)
include_directories(${PYTHON_INCLUDE_DIRS})

# Set to C++ 14
set(CMAKE_CXX_STANDARD 14)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)
#This defines the image lib to use by default use QIMAGE, I need to fix this for the others
add_definitions(-DUSEQIMAGE)
#This defines that we are using the header only version of the fmt lib
add_definitions(-DFMT_HEADER_ONLY)
add_definitions(-DUSEGLM)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set(SOURCES
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
    ${NGLROOT}/src/Vec4.cpp
    ${NGLROOT}/src/VAOPrimitives.cpp
    ${NGLROOT}/src/VAOFactory.cpp
    ${NGLROOT}/src/SimpleIndexVAO.cpp
    ${NGLROOT}/src/SimpleVAO.cpp
    ${NGLROOT}/src/AbstractVAO.cpp
    ${NGLROOT}/src/MultiBufferVAO.cpp
    ${NGLROOT}/src/Util.cpp
    ${NGLROOT}/src/Texture.cpp
    ${NGLROOT}/src/ShaderLib.cpp
    ${NGLROOT}/src/Transformation.cpp
    ${NGLROOT}/src/RibExport.cpp
    ${NGLROOT}/src/Quaternion.cpp
    ${NGLROOT}/src/Obj.cpp
    ${NGLROOT}/src/Mat4.cpp
    ${NGLROOT}/src/NGLInit.cpp
    ${NGLROOT}/src/NCCABinMesh.cpp
    ${NGLROOT}/src/BezierCurve.cpp
    ${NGLROOT}/src/BBox.cpp
    ${NGLROOT}/src/AbstractMesh.cpp
    ${NGLROOT}/src/Random.cpp
    ${NGLROOT}/src/NCCAPointBake.cpp
    ${NGLROOT}/src/Shader.cpp
    ${NGLROOT}/src/ShaderProgram.cpp
    ${NGLROOT}/src/Plane.cpp
    ${NGLROOT}/src/AABB.cpp
    ${NGLROOT}/src/createDefaultVAOs.cpp
    ${NGLROOT}/src/Vec3.cpp
    ${NGLROOT}/src/Vec2.cpp
    ${NGLROOT}/src/Text.cpp
    ${NGLROOT}/src/Mat3.cpp
    ${NGLROOT}/src/Mat2.cpp
    ${NGLROOT}/src/NGLStream.cpp
    ${NGLROOT}/src/Image.cpp
    ${NGLROOT}/src/Types.cpp
    ${NGLROOT}/src/pystring.cpp
    ${NGLROOT}/src/MessageQueue/AbstractMessageConsumer.cpp 
    ${NGLROOT}/src/MessageQueue/NGLMessage.cpp 
    ${NGLROOT}/src/MessageQueue/FileConsumer.cpp 
    ${NGLROOT}/gl3w/gl3w.c
    ${NGLROOT}/gl3w/gl3w.h
    ${NGLROOT}/gl3w/glcorearb.h
    ${NGLROOT}/include/ngl/Vec4.h
    ${NGLROOT}/include/ngl/VAOPrimitives.h
    ${NGLROOT}/include/ngl/VAOFactory.h
    ${NGLROOT}/include/ngl/SimpleIndexVAO.h
    ${NGLROOT}/include/ngl/SimpleVAO.h
    ${NGLROOT}/include/ngl/AbstractVAO.h
    ${NGLROOT}/include/ngl/MultiBufferVAO.h
    ${NGLROOT}/include/ngl/Singleton.h
    ${NGLROOT}/include/ngl/Util.h
    ${NGLROOT}/include/ngl/Types.h
    ${NGLROOT}/include/ngl/Texture.h
    ${NGLROOT}/include/ngl/ShaderLib.h
    ${NGLROOT}/include/ngl/RibExport.h
    ${NGLROOT}/include/ngl/Transformation.h
    ${NGLROOT}/include/ngl/Quaternion.h
    ${NGLROOT}/include/ngl/Obj.h
    ${NGLROOT}/include/ngl/NGLassert.h
    ${NGLROOT}/include/ngl/Mat4.h
    ${NGLROOT}/include/ngl/NGLInit.h
    ${NGLROOT}/include/ngl/BezierCurve.h
    ${NGLROOT}/include/ngl/NCCABinMesh.h
    ${NGLROOT}/include/ngl/BBox.h
    ${NGLROOT}/include/ngl/AbstractMesh.h
    ${NGLROOT}/include/ngl/Random.h
    ${NGLROOT}/include/ngl/NCCAPointBake.h
    ${NGLROOT}/include/ngl/Shader.h
    ${NGLROOT}/include/ngl/ShaderProgram.h
    ${NGLROOT}/include/ngl/Plane.h
    ${NGLROOT}/include/ngl/AABB.h
    ${NGLROOT}/include/ngl/Vec3.h
    ${NGLROOT}/include/ngl/Vec2.h
    ${NGLROOT}/include/ngl/Text.h
    ${NGLROOT}/include/ngl/Mat3.h
    ${NGLROOT}/include/ngl/Mat2.h
    ${NGLROOT}/include/ngl/pystring.h
    ${NGLROOT}/include/ngl/Image.h
    ${NGLROOT}/include/ngl/NGLStream.h
    ${NGLROOT}/include/ngl/NGLStream.h
    ${NGLROOT}/include/ngl/MessageQueue/AbstractMessageConsumer.h 
    ${NGLROOT}/include/ngl/MessageQueue/FileConsumer.h 
    ${NGLROOT}/include/ngl/MessageQueue/STDERRConsumer.h 
    ${NGLROOT}/include/ngl/MessageQueue/STDOutConsumer.h    
    ${NGLROOT}/src/shaders/TextShaders.h
    ${NGLROOT}/src/shaders/ColourShaders.h
    ${NGLROOT}/src/shaders/DiffuseShaders.h
    ${NGLROOT}/include/ngl/rapidxml/rapidxml.hpp
    ${NGLROOT}/include/ngl/rapidxml/rapidxml_iterators.hpp
    ${NGLROOT}/include/ngl/rapidxml/rapidxml_print.hpp
    ${NGLROOT}/include/ngl/rapidxml/rapidxml_utils.hpp
)


# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(MACGL OpenGL)
    set(EXTRALIBS  ${MACGL} -lpython2.7)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()


# as NGL uses Qt we need to define this flag
# NGL also needs the OpenGL framework from Qt so add it
find_package(Qt5OpenGL)

# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NGLROOT}/lib)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${NGLROOT}/lib/pyngl.so")


set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
add_library(pyngl SHARED ${SOURCES})

target_link_libraries(pyngl Qt5::OpenGL)
target_link_libraries(pyngl ${PROJECT_LINK_LIBS} ${EXTRALIBS})

