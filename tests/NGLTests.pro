###############################################################################
# This specifies the exe name
###############################################################################
TARGET=NGLTests
###############################################################################
# where to put the .o files
###############################################################################
OBJECTS_DIR=obj
###############################################################################
# core Qt Libs to use add more here if needed.
###############################################################################
QT+=gui opengl core



###############################################################################
# include the UseNGL project 
###############################################################################
NGLPATH=$$(NGLDIR)

isEmpty(NGLPATH){ # note brace must be here
  unix{
          message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
  }
  win32{
    BASE_DIR=$$system(powershell -ExecutionPolicy Bypass -Command "echo $home'\NGL\'" )
    include($${BASE_DIR}\UseNGL.pri)

  }
}
else{ # note brace must be here
  message("Using custom NGL location")
  include($(NGLDIR)/UseNGL.pri)
}

DEFINES+=GLM_ENABLE_EXPERIMENTAL


###############################################################################
# we are going to use GLFW for Offscreen OpenGL context creation so we can test GL elements
###############################################################################

unix{
QMAKE_CXXFLAGS+= $$system(pkg-config --cflags glfw3)
LIBS+=$$system(pkg-config --libs glfw3)
CONFIG += console
LIBS += -L/public/devel/lib
LIBS+=-lgtest

}

macx{
      LIBS+= -framework OpenGL -framework IOKit -Cocoa -framework CoreVideo
      DEFINES+=GLFW_USE_MENUBAR
      DEFINES+=GLFW_USE_RETINA
      CONFIG-=app_bundle
}

linux-*{
  LIBS+= -lX11 -lXxf86vm -L/usr/lib64 -lXrandr -lXi -lXinerama -lXcursor -ldl
}
win32:{
# using vcpkg to install gtest under windows
BASE=$$(HOMEDRIVE)\\$$(HOMEPATH)

  contains(QT_ARCH, i386) {
      message("32-bit build")
    INCLUDEPATH += $$BASE\vcpkg\installed\x86-windows\include
    PRE_TARGETDEPS+=$$BASE\vcpkg\installed\x86-windows\lib\gtest.lib
    LIBS+= -L$$BASE\vcpkg\installed\x86-windows\lib\ -lgtest
    PRE_TARGETDEPS+=$$BASE\vcpkg\installed\x86-windows\lib\glfw3dll.lib
    LIBS+= -L$$BASE\vcpkg\installed\x86-windows\lib\ -lglfw3dll

  } 
  else {
      message("64-bit build")
    INCLUDEPATH += $$BASE\vcpkg\installed\x64-windows\include
    PRE_TARGETDEPS+=$$BASE\vcpkg\installed\x64-windows\lib\gtest.lib
    LIBS+= -L$$BASE\vcpkg\installed\x64-windows\lib\ -lgtest
    PRE_TARGETDEPS+=$$BASE\vcpkg\installed\x64-windows\lib\glfw3dll.lib
    LIBS+= -L$$BASE\vcpkg\installed\x64-windows\lib\ -lglfw3dll

  }



}

DEFINES+=ADDLARGEMODELS
cache()
# where to put moc auto generated files
MOC_DIR=moc

SOURCES+= $$PWD/Vec4Tests.cpp \
          $$PWD/Mat4Tests.cpp  \
          $$PWD/Vec3Tests.cpp  \
          $$PWD/Mat2Tests.cpp \
          $$PWD/Mat3Tests.cpp \
          $$PWD/Vec2Tests.cpp \
          $$PWD/ObjTests.cpp \
          $$PWD/UtilTests.cpp \
          $$PWD/NGLInitTests.cpp \
          $$PWD/VAOPrimitivesTests.cpp \
          $$PWD/ShaderLibTests.cpp \
          $$PWD/MessageQueueTests.cpp \
          $$PWD/RandomTests.cpp \
          $$PWD/QuaternionTests.cpp \
          $$PWD/main.cpp

OTHER_FILES+=$$PWD/files/*

# same for the .h files

DEPENDPATH+=$$PWD/include
# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./
OTHER_FILES+= README.md
