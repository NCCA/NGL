/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef TYPES_H__
#define TYPES_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Types.h
/// @brief main definition of types and namespace
//----------------------------------------------------------------------------------------------------------------------


#ifdef DARWIN
  #include <unistd.h>
  #include "glew.h"

  #include <OpenGL/gl3.h>
  #include <OpenGL/glext.h>
#else

  #include "glew.h"
  #include <GL/gl.h>
  #include <GL/glext.h>
#endif



#ifndef QT5BUILD
  #include <QtOpenGL/QGLContext>
#endif
// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include <boost/python.hpp>
  #include <boost/format.hpp>
#endif

//----------------------------------------------------------------------------------------------------------------------
// DLL Glue for windows build / apps
//----------------------------------------------------------------------------------------------------------------------
#ifdef WIN32
  #ifdef BUILDING_DLL
    #define NGL_DLLEXPORT __declspec(dllexport)
  #else
    #define NGL_DLLEXPORT __declspec(dllimport)
  #endif
  #ifdef NO_DLL
    #undef NGL_DLLEXPORT
    #define NGL_DLLEXPORT
  #endif

#else
    #define NGL_DLLEXPORT
#endif

#ifdef DARWIN
    #ifndef GL_TESS_CONTROL_SHADER
        #define GL_TESS_CONTROL_SHADER 0x00008e88
    #endif
    #ifndef GL_TESS_EVALUATION_SHADER
        #define GL_TESS_EVALUATION_SHADER 0x00008e87
    #endif
    #ifndef GL_PATCHES
        #define GL_PATCHES 0x0000000e
    #endif
#endif


  extern void* setGL32VisualMac(bool _multisample=true);
#ifndef QT5BUILD
#include <QGLContext>
  class CreateCoreGLContext : public QGLContext
  {
   public :
    CreateCoreGLContext(const QGLFormat& format, QPaintDevice* device) : QGLContext(format,device) {;}
    CreateCoreGLContext(const QGLFormat& format) : QGLContext(format) {;}
    // under mac this is called and we create the context for GL3.2
    #ifdef DARWIN
      #ifndef QT5BUILD
        virtual void* chooseMacVisual()
        {
          return setGL32VisualMac();
        }
      #endif
    #endif
  };
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file types.h
/// @brief declare a variable called Real which sets the Global Precision for the other classes (GLfloat)
/// @author Jonathan Macey
/// @version 2.0
/// @date 29/10/09 Updated to meet NCCA coding standard
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
/// @namespace ngl : bundled all the graphics lib code in this namespace to allow several
/// global namespace enums and variables
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @brief Set the PRECISION of all data types
///  Set PRECISION to be a GLfloat so we only have to change one value to set the data type
//----------------------------------------------------------------------------------------------------------------------

  typedef GLfloat PRECISION;

//----------------------------------------------------------------------------------------------------------------------
/// create a variable called Real which is the main data type we use (GLfloat for most  cases)
//----------------------------------------------------------------------------------------------------------------------

typedef PRECISION Real;
//----------------------------------------------------------------------------------------------------------------------
/// @brief define EPSILON for floating point comparison
//----------------------------------------------------------------------------------------------------------------------
#ifndef EPSILON
  const static float  EPSILON = 0.001f;
#endif

//----------------------------------------------------------------------------------------------------------------------
/// @brief FCompare macro used for floating point comparision functions
//----------------------------------------------------------------------------------------------------------------------
  #define FCompare(a,b) \
      ( ((a)-EPSILON)<(b) && ((a)+EPSILON)>(b) )

//----------------------------------------------------------------------------------------------------------------------
/// @brief define unused to quiet Warnings
//----------------------------------------------------------------------------------------------------------------------

 #define NGL_UNUSED(arg) (void)arg;

}

#endif

//----------------------------------------------------------------------------------------------------------------------
