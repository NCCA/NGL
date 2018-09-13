# -------------------------------------------------
# Project created by QtCreator 2009-11-05T12:31:57
# -------------------------------------------------
# qt 5 wants this may caus errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }

# We will use the built in Qt lib template
TEMPLATE = lib
QT += opengl
QT += core
QT += gui
QT -=xml

CONFIG+=c++1z

# Use this to add GLM to the ShaderLib (assumes glm in include path)
DEFINES+=USEGLM
# What image library to use change to 1 of these depending on what platform
# QImage USEQIMAGE
# ImageMagick USEIMAGEMAGIC
# OpenImageIO USEOIIO
IMAGELIB=USEQIMAGE
# add this to the global defines
DEFINES +=$$IMAGELIB
equals(IMAGELIB,"USEIMAGEMAGIC"){
	QMAKE_CXXFLAGS+=$$system(Magick++-config --cppflags )
	LIBS+=$$system(Magick++-config --ldflags --libs )
	message("Using Image Magick config is")
	message($$system(Magick++-config --cppflags ) )
	message($$system(Magick++-config --ldflags --libs ))
}
equals(IMAGELIB,"USEOIIO"){
	LIBS+=-L/usr/local/lib/ -lOpenImageIO
}

# to ensure we don't get any ABI issues use c++ and correct libs on mac

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {DEFINES +=QT5BUILD }

# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
DEFINES+=ADDLARGEMODELS
# set the base directory of our project so Qt knows where to find them
# we can use shell vars but need to use $$

NGLPATH=$$(NGLDIR)

isEmpty(NGLPATH){ # note brace must be here
	BASE_DIR=$$(HOME)/NGL
}
else{ # note brace must be here
	BASE_DIR=$$(NGLDIR)
}

message($${BASE_DIR})

# This is the output target we want to create
TARGET = $$BASE_DIR/lib/NGL
# this is where we want to put the intermediate build files ( ../obj)
OBJECTS_DIR = $$BASE_DIR/obj
QMAKE_LFLAGS-= -headerpad_max_install_names
QMAKE_LFLAGS_SHLIB -= -single_module
QMAKE_LFLAGS_VERSION=
QMAKE_LFLAGS_COMPAT_VERSION=
QMAKE_LFLAGS_SONAME=
# use this to suppress some warning
unix:QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
# define the NGL_DEBUG flag for the graphics lib
DEFINES += NGL_DEBUG
unix:INCLUDEPATH+=/usr/local/include
#set some flags for sse etc
unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-builtin-macro-redefined -isystem
macx:DEFINES +=GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
macx {
QMAKE_POST_LINK = install_name_tool -id @rpath/$$BASE_DIR/lib/libNGL.1.0.0.dylib $$BASE_DIR/lib/libNGL.1.0.0.dylib
}

# this is where to look for includes
INCLUDEPATH +=$$BASE_DIR/include/ngl
INCLUDEPATH +=$$BASE_DIR/src/ngl
INCLUDEPATH +=$$BASE_DIR/src/shaders
INCLUDEPATH +=$$BASE_DIR/include/rapidjson
INCLUDEPATH +=$$BASE_DIR/gl3w/
# for the University build
INCLUDEPATH +=/public/devel/include
# using the fmt library https://github.com/fmtlib/fmt but header only.
DEFINES+=FMT_HEADER_ONLY
INCLUDEPATH +=$$BASE_DIR/include/fmt

unix:LIBS += -L/usr/local/lib
# set the SRC_DIR so we can find the project files
SRC_DIR = $$BASE_DIR/src


# and the include files
INC_DIR = $$BASE_DIR/include/ngl
DEPENDPATH= $$INC_DIR
DEPENDPATH +=$$SRC_DIR/ngl/
DEPENDPATH +=$$SRC_DIR/shaders/
QMAKE_CXXFLAGS+=-Wall
macx:{
  QMAKE_CXXFLAGS+=  -fPIC
	LIBS+= -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework OpenGL
	LIBS+=  -Wl,-framework,Cocoa
	#DEFINES += DARWIN
  #QMAKE_MAC_SDK=macosx10.13

}

# in this case unix is also mac so we need to exclude mac from the unix build
win32|unix:!macx{
	# now define some linux specific flags
	unix:QMAKE_CXXFLAGS+=  -march=native
	#unix:DEFINES += LINUX
	unix:LIBS+= -L/usr/lib64 -lGL -lGLU -lX11

}


# The windows configuration is very frustrating however I seem to have it working now
# once you have done this set the PATH environment variable to look in
# c:/NGL/lib to find the DLL
win32{
				message("Using Windows check to see what needs to be installed")
				CONFIG+=staticlib
        INCLUDEPATH += C:/SDKs/ #for university STEM build
				DEFINES+=_USE_MATH_DEFINES
				DESTDIR=c:/
				DEFINES += NO_DLL
}


SOURCES += $$SRC_DIR/Vec4.cpp \
		$$SRC_DIR/VAOPrimitives.cpp \
		$$SRC_DIR/Util.cpp \
		$$SRC_DIR/Texture.cpp \
		$$SRC_DIR/ShaderLib.cpp \
		$$SRC_DIR/Transformation.cpp \
		$$SRC_DIR/RibExport.cpp \
		$$SRC_DIR/Quaternion.cpp \
		$$SRC_DIR/Obj.cpp \
		$$SRC_DIR/Mat4.cpp \
		$$SRC_DIR/NGLInit.cpp \
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
		$$SRC_DIR/createDefaultVAOs.cpp \
		$$SRC_DIR/Vec3.cpp \
		$$SRC_DIR/Vec2.cpp \
		$$SRC_DIR/Text.cpp \
		$$SRC_DIR/Mat3.cpp \
		$$SRC_DIR/NGLStream.cpp \
    $$SRC_DIR/Image.cpp \
    $$SRC_DIR/VAOFactory.cpp \
    $$SRC_DIR/AbstractVAO.cpp \
    $$SRC_DIR/MultiBufferVAO.cpp \
    $$SRC_DIR/SimpleVAO.cpp \
    $$SRC_DIR/SimpleIndexVAO.cpp \
    $$SRC_DIR/Types.cpp \
    $$SRC_DIR/pystring.cpp \
    $$SRC_DIR/MessageQueue/AbstractMessageConsumer.cpp \
    $$SRC_DIR/MessageQueue/NGLMessage.cpp \
    $$SRC_DIR/MessageQueue/FileConsumer.cpp \
    $$SRC_DIR/MessageQueue/PipeConsumer.cpp \
    $$SRC_DIR/MessageQueue/MMapConsumer.cpp
    !macx:{
      SOURCES+=$$BASE_DIR/gl3w/gl3w.c
    }

ios {
	message("IOS BUILD")
	DEFINES+=USINGIOS_
}





HEADERS += $$INC_DIR/Vec4.h \
		$$INC_DIR/VAOPrimitives.h \
		$$INC_DIR/Singleton.h \
		$$INC_DIR/Util.h \
		$$INC_DIR/Types.h \
		$$INC_DIR/Texture.h \
		$$INC_DIR/ShaderLib.h \
		$$INC_DIR/RibExport.h \
		$$INC_DIR/Transformation.h \
		$$INC_DIR/Quaternion.h \
		$$INC_DIR/Obj.h \
		$$INC_DIR/NGLassert.h \
		$$INC_DIR/Mat4.h \
		$$INC_DIR/NGLInit.h \
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
		$$INC_DIR/Vec3.h \
		$$INC_DIR/Vec2.h \
		$$INC_DIR/Text.h \
		$$INC_DIR/Mat3.h \
		$$INC_DIR/Image.h \
    $$INC_DIR/VAOFactory.h \
    $$INC_DIR/AbstractVAO.h \
    $$INC_DIR/SimpleVAO.h \
    $$INC_DIR/SimpleIndexVAO.h \
    $$INC_DIR/MultiBufferVAO.h \
		$$INC_DIR/NGLStream.h \
    $$INC_DIR/NGLMessage.h \
    $$INC_DIR/MessageQueue/AbstractMessageConsumer.h \
    $$INC_DIR/MessageQueue/FileConsumer.h \
    $$INC_DIR/MessageQueue/PipeConsumer.h \
    $$INC_DIR/MessageQueue/MMapConsumer.h \
    $$INC_DIR/MessageQueue/STDERRConsumer.h \
    $$INC_DIR/MessageQueue/STDOUTConsumer.h \
    $$SRC_DIR/shaders/TextShaders.h \
		$$SRC_DIR/shaders/ColourShaders.h \
		$$SRC_DIR/shaders/DiffuseShaders.h \
    $$SRC_DIR/shaders/CheckerShaders.h \
		$$INC_DIR/rapidxml/rapidxml.hpp \
		$$INC_DIR/rapidxml/rapidxml_iterators.hpp \
		$$INC_DIR/rapidxml/rapidxml_print.hpp \
    $$INC_DIR/rapidxml/rapidxml_utils.hpp \
    $$INC_DIR/pystring.h
    !macx:{
            HEADERS+=$$PWD/gl3w/gl3w.h
    }

unix:PRECOMPILED_HEADER += $$SRC_DIR/ngl/Meshes.h \


OTHER_FILES+= Doxyfile \
              README.md \
              CMakeLists.txt

DISTFILES += \
    NGLUML.qmodel



