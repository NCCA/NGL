###############################################################################
# This file is included in any project that requires NGL it will be searched for
# in the default $(HOME)/NGL/  directory if this can't be found the environment 
# variable $NGLDIR will be searched for and this will be used.
###############################################################################

CONFIG+=c++14

###############################################################################
# find where NGL is installed
###############################################################################
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here

        NGLBASE=$$(HOME)/NGL
        win32:{
            NGLBASE=$(HOMEDRIVE)\$(HOMEPATH)\NGL
        }
}
else{ # note brace must be here
	NGLBASE=$$(NGLDIR)
}
###############################################################################
# this is where to look for includes
###############################################################################
INCLUDEPATH += $${NGLBASE}/include/ 
INCLUDEPATH += $${NGLBASE}/gl3w/

DEFINES+=FMT_HEADER_ONLY
DEFINES += USEGLM
DEFINES+=GLM_ENABLE_EXPERIMENTAL
DEFINES +=NGL_DEBUG
DEPENDPATH+=include


###############################################################################
# Unix (mac / linux) specific build rules
###############################################################################
unix{
  QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
  QMAKE_CXXFLAGS +=  -march=native -Wno-unused-variable
  QMAKE_RPATHDIR+=L$${NGLBASE}/lib
  # For University build 
  INCLUDEPATH+=/public/devel/include
  LIBS += -L/usr/local/lib
  LIBS +=  -L$${NGLBASE}/lib -l NGL
  QMAKE_RPATHDIR+=$${NGLBASE}/lib

}


###############################################################################
# Mac specific build rules
###############################################################################

macx{
  CONFIG-=app_bundle
  DEFINES+=GL_SILENCE_DEPRECATION
  QMAKE_CXXFLAGS+= -arch x86_64
  INCLUDEPATH+=/usr/local/include/
}


###############################################################################
# Windows specific build rules
###############################################################################


win32: {
        PRE_TARGETDEPS+=$$(HOMEDRIVE)\\$$(HOMEPATH)\NGL\lib\NGL.lib
        DEFINES+=GL42
        DEFINES += WIN32
        DEFINES+=_WIN32
        DEFINES+=_USE_MATH_DEFINES
        LIBS+= -lopengl32
        LIBS += -L$$(HOMEDRIVE)\\$$(HOMEPATH)\NGL\lib -lNGL
        DEFINES+=NO_DLL
        contains(QT_ARCH, i386) {
            message("32-bit build")
          INCLUDEPATH += $$(HOMEDRIVE)\\$$(HOMEPATH)\vcpkg\installed\x86-windows\include

        } 
        else {
            message("64-bit build")
          INCLUDEPATH += $$(HOMEDRIVE)\\$$(HOMEPATH)\vcpkg\installed\x64-windows\include

        }
}


