#-------------------------------------------------------------------------------------------
# as much as possible I will use best practice as outlined in the book "Profession cmake"
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.12)
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

find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(IlmBase CONFIG )
find_package(OpenEXR CONFIG )
find_package(freetype CONFIG REQUIRED)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
find_package(RapidJSON CONFIG REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
option(ENABLE_FAST_MATH ON)
add_compile_definitions(NGL_DEBUG)
if(WIN32)
    # Not defined in msvc compiler for cmaths so must set definition manually here
    add_compile_definitions(_USE_MATH_DEFINES)
    add_compile_definitions(NOMINMAX)
    # Need to define this when building shared library or suffer dllimport errors
    add_compile_definitions(BUILDING_DLL)
    
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

add_compile_definitions(ADDLARGEMODELS)
#This defines the image lib to use by default use QIMAGE, I need to fix this for the others
add_compile_definitions(USEOIIO)
add_compile_definitions(USEGLM)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
if(WIN32)
  add_library(NGL STATIC)
else()
  add_library(NGL SHARED)
endif()

install(TARGETS NGL DESTINATION lib CONFIGURATIONS Release)
install(TARGETS NGL DESTINATION lib)

install(DIRECTORY   ${CMAKE_SOURCE_DIR}/include/ngl/ DESTINATION include/ngl)
install(FILES   ${CMAKE_SOURCE_DIR}/gl3w/gl3w.h DESTINATION include/ngl)
install(FILES   ${CMAKE_SOURCE_DIR}/gl3w/glcorearb.h DESTINATION include/ngl)
install(FILES   ${CMAKE_SOURCE_DIR}/NGLConfig.cmake DESTINATION ./)



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
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_DIR})


target_link_libraries(NGL PRIVATE glm::glm)
target_link_libraries(NGL PRIVATE fmt::fmt-header-only)
target_link_libraries(NGL PRIVATE ${EXTRALIBS})
target_link_libraries(NGL PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(NGL PRIVATE  IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
target_link_libraries(NGL PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)


target_link_libraries(NGL PRIVATE freetype)
target_include_directories(NGL PRIVATE ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(NGL PRIVATE ${RAPIDJSON_INCLUDE_DIRS})


#################################################################
# Tests
#################################################################

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(NGLTests)
target_sources(NGLTests PRIVATE
${CMAKE_SOURCE_DIR}/tests/main.cpp  
${CMAKE_SOURCE_DIR}/tests/MessageQueueTests.cpp  
${CMAKE_SOURCE_DIR}/tests/UtilTests.cpp           
${CMAKE_SOURCE_DIR}/tests/Vec4Tests.cpp
${CMAKE_SOURCE_DIR}/tests/Mat2Tests.cpp  
${CMAKE_SOURCE_DIR}/tests/NGLInitTests.cpp       
${CMAKE_SOURCE_DIR}/tests/VAOPrimitivesTests.cpp
${CMAKE_SOURCE_DIR}/tests/Mat3Tests.cpp  
${CMAKE_SOURCE_DIR}/tests/ObjTests.cpp           
${CMAKE_SOURCE_DIR}/tests/Vec2Tests.cpp
${CMAKE_SOURCE_DIR}/tests/Mat4Tests.cpp  
${CMAKE_SOURCE_DIR}/tests/ShaderLibTests.cpp     
${CMAKE_SOURCE_DIR}/tests/Vec3Tests.cpp
${CMAKE_SOURCE_DIR}/tests/RandomTests.cpp
${CMAKE_SOURCE_DIR}/tests/QuaternionTests.cpp
)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
target_link_libraries(NGLTests PRIVATE glfw PRIVATE GTest::gtest  )

target_link_libraries(NGLTests PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(NGLTests PRIVATE  IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
target_link_libraries(NGLTests PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)
target_include_directories(NGLTests PRIVATE ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(NGLTests PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_link_libraries(NGLTests PRIVATE freetype)



# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     message("Doing mac OpenGL")
		 find_library(MACGL OpenGL)
		 add_definitions(-DGL_SILENCE_DEPRECATION)
    set(EXTRALIBS  ${MACGL})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()
if(WIN32)
    add_definitions( -D_USE_MATH_DEFINES)
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	link_directories(  )
	target_link_libraries( NGLTests PRIVATE $(ConfigurationName)/NGL.lib )
else()
target_link_libraries(NGLTests PRIVATE  NGL PRIVATE ${EXTRALIBS} )

endif()

gtest_discover_tests(NGLTests)


add_custom_target(CopyTestfiles ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/tests/files
		${CMAKE_BINARY_DIR}/$(ConfigurationName)/files
		COMMENT "Copy Test files to build directory"
		)
      
      
# PyNGL
#############################################################

if(DEFINED BUILD_PYNGL)

add_library(pyngl SHARED)

add_compile_definitions(PYTHONBUILD)
find_package( PythonInterp 2 REQUIRED )
find_package( PythonLibs 2 REQUIRED )
find_package(pybind11 CONFIG REQUIRED)
set(PYSOURCEDIR ${CMAKE_SOURCE_DIR}/PyNGL/src)
include_directories(${CMAKE_SOURCE_DIR}/PyNGL/)
include_directories(${PYTHON_INCLUDE_DIRS})


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

if(WIN32)
    add_definitions( -D_USE_MATH_DEFINES)
endif()



# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${CMAKE_SOURCE_DIR}/lib)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_SOURCE_DIR}/lib/pyngl.so")


set_target_properties(pyngl PROPERTIES PREFIX "")

target_link_libraries(pyngl PRIVATE  pybind11::embed pybind11::module pybind11::pybind11)
target_link_libraries(pyngl PRIVATE glm::glm)
target_link_libraries(pyngl PRIVATE fmt::fmt-header-only)
target_link_libraries(pyngl PRIVATE ${PROJECT_LINK_LIBS} ${EXTRALIBS})
target_link_libraries(pyngl PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(pyngl PRIVATE  IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
target_link_libraries(pyngl PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)



target_link_libraries(pyngl PRIVATE freetype)
target_include_directories(pyngl PRIVATE ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(pyngl PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

install(TARGETS pyngl DESTINATION lib CONFIGURATIONS Release)
install(TARGETS pyngl DESTINATION lib)


endif()


