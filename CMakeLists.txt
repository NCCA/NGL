cmake_minimum_required(VERSION 2.8.11)
# Name of the project
project(NGL)
#Bring the headers into the project (local ones)
include_directories(include/ngl)
include_directories(src/ngl)
include_directories(src/shaders)

# use this to remove any marked as deprecated classes from NGL
add_definitions(-DREMOVEDDEPRECATED)
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
add_definitions(-DQT5BUILD)
# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
add_definitions(-DADDLARGEMODELS)

set(SOURCES
    src/Vec4.cpp
    src/VAOPrimitives.cpp
    src/Util.cpp
    src/Texture.cpp
    src/SpotLight.cpp
    src/ShaderLib.cpp
    src/Transformation.cpp
    src/RibExport.cpp
    src/Quaternion.cpp
    src/PathCamera.cpp
    src/Obj.cpp
    src/Mat4.cpp
    src/Material.cpp
    src/Light.cpp
    src/NGLInit.cpp
    src/Colour.cpp
    src/Camera.cpp
    src/NCCABinMesh.cpp
    src/BezierCurve.cpp
    src/BBox.cpp
    src/AbstractMesh.cpp
    src/Random.cpp
    src/NCCAPointBake.cpp
    src/Shader.cpp
    src/ShaderProgram.cpp
    src/Plane.cpp
    src/AABB.cpp
    src/VertexArrayObject.cpp
    src/createDefaultVAOs.cpp
    src/Vec3.cpp
    src/Vec2.cpp
    src/Text.cpp
    src/Mat3.cpp
    src/AbstractSerializer.cpp
    src/XMLSerializer.cpp
    src/NGLStream.cpp
    src/Logger.cpp
    glew/glew.c
    include/ngl/Vec4.h
    include/ngl/VAOPrimitives.h
    include/ngl/Singleton.h
    include/ngl/Util.h
    include/ngl/Types.h
    include/ngl/Texture.h
    include/ngl/SpotLight.h
    include/ngl/ShaderLib.h
    include/ngl/RibExport.h
    include/ngl/Transformation.h
    include/ngl/Quaternion.h
    include/ngl/PathCamera.h
    include/ngl/Obj.h
    include/ngl/NGLassert.h
    include/ngl/Mat4.h
    include/ngl/Material.h
    include/ngl/Light.h
    include/ngl/NGLInit.h
    include/ngl/Colour.h
    include/ngl/Camera.h
    include/ngl/BezierCurve.h
    include/ngl/NCCABinMesh.h
    include/ngl/BBox.h
    include/ngl/AbstractMesh.h
    include/ngl/Random.h
    include/ngl/NCCAPointBake.h
    include/ngl/Shader.h
    include/ngl/ShaderProgram.h
    include/ngl/Plane.h
    include/ngl/AABB.h
    include/ngl/VertexArrayObject.h
    include/ngl/Vec3.h
    include/ngl/Vec2.h
    include/ngl/Text.h
    include/ngl/Mat3.h
    include/ngl/Logger.h
    include/ngl/AbstractSerializer.h
    include/ngl/XMLSerializer.h
    include/ngl/NGLStream.h
    src/shaders/TextShaders.h
    src/shaders/ColourShaders.h
    src/shaders/DiffuseShaders.h
    src/shaders/ToonShaders.h
    include/ngl/rapidxml/rapidxml.hpp
    include/ngl/rapidxml/rapidxml_iterators.hpp
    include/ngl/rapidxml/rapidxml_print.hpp
    include/ngl/rapidxml/rapidxml_utils.hpp



)


# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions(-DDARWIN)

elif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_definitions(-DLINUX)
endif()



# as NGL uses Qt we need to define this flag
# NGL also needs the OpenGL framework from Qt so add it
find_package(Qt5OpenGL)

# add exe and link libs this must be after the other defines
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(NGL SHARED ${SOURCES})

target_link_libraries(NGL Qt5::OpenGL)
target_link_libraries(NGL ${PROJECT_LINK_LIBS} )

