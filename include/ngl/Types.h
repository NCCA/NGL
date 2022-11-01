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
#ifndef TYPES_H_
#define TYPES_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Types.h
/// @brief main definition of types and namespace
//----------------------------------------------------------------------------------------------------------------------
/*
#ifdef __APPLE__
  #include <unistd.h>
  #ifndef USINGIOS_
   // #include <OpenGL/gl.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
  #else
    #include <OpenGLES/ES3/gl.h>
    #include <OpenGLES/ES3/glext.h>
  #endif

  #include <TargetConditionals.h>
  #ifndef TARGET_OS_IPHONE
//    #include <OpenGL/glext.h>
#endif

#else
  #include <GL/gl3w.h>
#endif
*/

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else

#include <GL/gl3w.h>
#endif
#include "fmt/format.h"

//----------------------------------------------------------------------------------------------------------------------
// DLL Glue for windows build / apps
//----------------------------------------------------------------------------------------------------------------------
#ifdef _WIN32
#pragma warning(disable : 5045)
#pragma warning(disable : 4251) // dll interface warning for STL
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
#include "NGLMessage.h"
#include <memory>

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

using PRECISION = GLfloat;

//----------------------------------------------------------------------------------------------------------------------
/// create a variable called Real which is the main data type we use (GLfloat for most  cases)
//----------------------------------------------------------------------------------------------------------------------

using Real = PRECISION;
//----------------------------------------------------------------------------------------------------------------------
/// @brief define EPSILON for floating point comparison
//----------------------------------------------------------------------------------------------------------------------
constexpr float EPSILON = 0.001f;

//----------------------------------------------------------------------------------------------------------------------
/// @brief FCompare macro used for floating point comparision functions
//----------------------------------------------------------------------------------------------------------------------
#define FCompare(a, b) \
  (((a)-ngl::EPSILON) < (b) && ((a) + ngl::EPSILON) > (b))

//----------------------------------------------------------------------------------------------------------------------
/// @brief define unused to quiet Warnings
//----------------------------------------------------------------------------------------------------------------------

#define NGL_UNUSED(arg) (void)arg;

constexpr auto simpleVAO = "simpleVAO";
constexpr auto multiBufferVAO = "multiBufferVAO";
constexpr auto simpleIndexVAO = "simpleIndexVAO";
constexpr auto nglColourShader = "nglColourShader";
constexpr auto nglDiffuseShader = "nglDiffuseShader";
constexpr auto nglCheckerShader = "nglCheckerShader";
constexpr auto nglTextShader = "nglTextShader";
enum class ErrorExit : bool
{
  ON,
  OFF
};

} // namespace ngl

#endif

//----------------------------------------------------------------------------------------------------------------------
