#This file is included in any project that requires NGL it will be searched for 
#in the default $(HOME)/NGL/  directory if this can't be found the environment variable $NGLDIR will be searched for and this will be used.
CONFIG+=c++11

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES +=QT5BUILD
}
NGLPATH=$$(NGLDIR)

isEmpty(NGLPATH){ # note brace must be here
	NGLBASE=$$(HOME)/NGL
}
else{ # note brace must be here
	NGLBASE=$$(NGLDIR)
}

message($${NGLBASE})

# use this to suppress some warning from boost
unix*:QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
# basic compiler flags (not all appropriate for all platforms)
QMAKE_CXXFLAGS+= -msse -msse2 -msse3 -fopenmp
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/include/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native
# define the _DEBUG flag for the graphics lib
DEFINES +=NGL_DEBUG

unix:LIBS += -L/usr/local/lib
# add the ngl lib note the { } for the environment variable QMake variable's value at time qmake is run 
unix:LIBS +=  -L$${NGLBASE}/lib -l NGL

# now if we are under unix and not on a Mac (i.e. linux)
linux-*{
		linux-*:QMAKE_CXXFLAGS +=  -march=native
		LIBS+=-ltiff
		#DEFINES += LINUX
}
DEPENDPATH+=include
# if we are on a mac define DARWIN
message("Building for Mac El-Capitain using sdk 10.11 if this is not found")
message("Modify UseNGL.pri and modify QMAKE_MACK_SDK to macosx10.10")

macx:QMAKE_MAC_SDK = macosx10.11
# this is where to look for includes
INCLUDEPATH += $${NGLBASE}/include/

win32: {
        PRE_TARGETDEPS+=C:/NGL/lib/NGL.lib
        INCLUDEPATH+=-I c:/boost
        DEFINES+=GL42
        DEFINES += WIN32
        DEFINES+=_WIN32
        DEFINES+=_USE_MATH_DEFINES
        LIBS+= -lopengl32
        LIBS += -LC:/NGL/lib/ -lNGL
        DEFINES+=NO_DLL
}

ios {
        message("IOS BUILD")
        DEFINES+=USINGIOS_
        INCLUDEPATH+=/usr/local/include
        LIBS +=  -L$${NGLBASE}/lib -lNGLIOS

}

QMAKE_RPATHDIR+=/Users/v0q/clang-omp/build/lib
QMAKE_RPATHDIR+=$${NGLBASE}/lib

