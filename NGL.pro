# -------------------------------------------------
# Project created by QtCreator 2009-11-05T12:31:57
# -------------------------------------------------
# qt 5 wants this may cause errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }

# We will use the built in Qt lib template
TEMPLATE = lib
QT += opengl
QT += core
QT += gui
QT -=xml

# use this to remove any marked as deprecated classes from NGL
DEFINES += REMOVEDDEPRECATED
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {DEFINES +=QT5BUILD }

# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
DEFINES+=ADDLARGEMODELS

# set the base directory of our project so Qt knows where to find them
# we can use shell vars but need to use $$
BASE_DIR = $$(HOME)/NGL
# This is the output target we want to create
TARGET = $$BASE_DIR/lib/NGL
# this is where we want to put the intermediate build files ( ../obj)
OBJECTS_DIR = $$BASE_DIR/obj
QMAKE_LFLAGS-= -headerpad_max_install_names
QMAKE_LFLAGS_SHLIB -= -single_module
QMAKE_LFLAGS_VERSION=
QMAKE_LFLAGS_COMPAT_VERSION=
QMAKE_LFLAGS_SONAME=
# use this to suppress some warning from boost
unix:QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
# define the NGL_DEBUG flag for the graphics lib
DEFINES += NGL_DEBUG
# if you install boost to /usr/local/include/ we can find it from this line
# basically all you need to do is copy the headers from the boost source to this
# location cp -R boost_1_49_0/boost /usr/local/include under linux use apt-get install
unix:INCLUDEPATH+=/usr/local/include
#set some flags for sse etc
unix:QMAKE_CXXFLAGS+=  -msse -msse2 -msse3 -fms-extensions -O3
unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-builtin-macro-redefined -isystem
macx:DEFINES +=GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

# this is where to look for includes
INCLUDEPATH += $$BASE_DIR/include/ngl
INCLUDEPATH += $$BASE_DIR/glew/

INCLUDEPATH += $$BASE_DIR/src/ngl
INCLUDEPATH +=$$BASE_DIR/src/shaders
unix:LIBS += -L/usr/local/lib

# set the SRC_DIR so we can find the project files
SRC_DIR = $$BASE_DIR/src


# and the include files
INC_DIR = $$BASE_DIR/include/ngl
DEPENDPATH= $$INC_DIR
DEPENDPATH +=$$SRC_DIR/ngl/
DEPENDPATH +=$$SRC_DIR/shaders/

macx:{
	QMAKE_CXXFLAGS+=  -fPIC
	LIBS+= -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework OpenGL
	LIBS+=  -Wl,-framework,Cocoa
	DEFINES += DARWIN

}


# in this case unix is also mac so we need to exclude mac from the unix build
win32|unix:!macx{
	# now define some linux specific flags
	unix:QMAKE_CXXFLAGS+=  -march=native
	unix:DEFINES += LINUX
	unix:LIBS+= -L/usr/lib64 -lGL -lGLU -lX11

}


# The windows configuration is very frustrating however I seem to have it working now
# you will need to install boost in the path below
# once you have done this set the PATH environment variable to look in
# c:/NGL/lib to find the DLL
win32{
				message("Using Windows check to see what needs to be installed")
				CONFIG+=staticlib
				INCLUDEPATH +=C:/boost/
				DEFINES+=_USE_MATH_DEFINES
				# Silence some boost warnings
				DEFINES+= _SCL_SECURE_NO_WARNINGS
				DESTDIR=c:/
				DEFINES += NO_DLL
}


SOURCES += $$SRC_DIR/Vec4.cpp \
		$$SRC_DIR/VAOPrimitives.cpp \
		$$SRC_DIR/Util.cpp \
		$$SRC_DIR/Texture.cpp \
		$$SRC_DIR/SpotLight.cpp \
		$$SRC_DIR/ShaderLib.cpp \
		$$SRC_DIR/Transformation.cpp \
		$$SRC_DIR/RibExport.cpp \
		$$SRC_DIR/Quaternion.cpp \
		$$SRC_DIR/PathCamera.cpp \
		$$SRC_DIR/Obj.cpp \
		$$SRC_DIR/Mat4.cpp \
		$$SRC_DIR/Material.cpp \
		$$SRC_DIR/Light.cpp \
		$$SRC_DIR/NGLInit.cpp \
		$$SRC_DIR/Colour.cpp \
		$$SRC_DIR/Camera.cpp \
		$$SRC_DIR/NCCABinMesh.cpp \
		$$SRC_DIR/BezierCurve.cpp \
		$$SRC_DIR/BBox.cpp \
		$$SRC_DIR/AbstractMesh.cpp \
		$$SRC_DIR/Random.cpp \
		$$SRC_DIR/NCCAPointBake.cpp \
		$$SRC_DIR/Shader.cpp \
		$$SRC_DIR/ShaderProgram.cpp \
		$$SRC_DIR/Plane.cpp \
		$$SRC_DIR/AABB.cpp \
		$$SRC_DIR/VertexArrayObject.cpp \
		$$SRC_DIR/createDefaultVAOs.cpp \
		$$SRC_DIR/Vec3.cpp \
		$$SRC_DIR/Vec2.cpp \
		$$SRC_DIR/Text.cpp \
		$$SRC_DIR/Mat3.cpp \
		$$SRC_DIR/AbstractSerializer.cpp \
		$$SRC_DIR/XMLSerializer.cpp \
		$$SRC_DIR/NGLStream.cpp \
		glew/glew.c




isEqual(QT_MAJOR_VERSION, 4) {
			OBJECTIVE_SOURCES += $$SRC_DIR/setGL32VisualMac.mm
}

HEADERS += $$INC_DIR/Vec4.h \
		$$INC_DIR/VAOPrimitives.h \
		$$INC_DIR/Singleton.h \
		$$INC_DIR/Util.h \
		$$INC_DIR/Types.h \
		$$INC_DIR/Texture.h \
		$$INC_DIR/SpotLight.h \
		$$INC_DIR/ShaderLib.h \
		$$INC_DIR/RibExport.h \
		$$INC_DIR/Transformation.h \
		$$INC_DIR/Quaternion.h \
		$$INC_DIR/PathCamera.h \
		$$INC_DIR/Obj.h \
		$$INC_DIR/NGLassert.h \
		$$INC_DIR/Mat4.h \
		$$INC_DIR/Material.h \
		$$INC_DIR/Light.h \
		$$INC_DIR/NGLInit.h \
		$$INC_DIR/Colour.h \
		$$INC_DIR/Camera.h \
		$$INC_DIR/BezierCurve.h \
		$$INC_DIR/NCCABinMesh.h \
		$$INC_DIR/BBox.h \
		$$INC_DIR/AbstractMesh.h \
		$$INC_DIR/Random.h \
		$$INC_DIR/NCCAPointBake.h \
		$$INC_DIR/Shader.h \
		$$INC_DIR/ShaderProgram.h \
		$$INC_DIR/Plane.h \
		$$INC_DIR/AABB.h \
		$$INC_DIR/VertexArrayObject.h \
		$$INC_DIR/Vec3.h \
		$$INC_DIR/Vec2.h \
		$$INC_DIR/Text.h \
		$$INC_DIR/Mat3.h \
		$$INC_DIR/AbstractSerializer.h \
		$$INC_DIR/XMLSerializer.h \
		$$INC_DIR/NGLStream.h \
		$$SRC_DIR/shaders/TextShaders.h \
		$$SRC_DIR/shaders/ColourShaders.h \
		$$SRC_DIR/shaders/DiffuseShaders.h \
		$$SRC_DIR/shaders/ToonShaders.h \
		$$INC_DIR/rapidxml/rapidxml.hpp \
		$$INC_DIR/rapidxml/rapidxml_iterators.hpp \
		$$INC_DIR/rapidxml/rapidxml_print.hpp \
		$$INC_DIR/rapidxml/rapidxml_utils.hpp



unix:PRECOMPILED_HEADER += $$SRC_DIR/ngl/Meshes.h \


PYTHON_DIR=$$BASE_DIR/python
OTHER_FILES+= Doxyfile \
							README.md



