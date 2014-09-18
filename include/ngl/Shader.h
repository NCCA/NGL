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
#ifndef SHADER_H__
#define SHADER_H__

#include "Types.h"

#include <iostream>
#include <cstdlib>
namespace ngl
{


/// @enum Type of shader this object is
// for c++ 11 use enum class
enum  SHADERTYPE{VERTEX,FRAGMENT,GEOMETRY,TESSCONTROL,TESSEVAL};
/// @class Shader
/// @brief and encapsulation of an OpenGL Shader object with
/// associations for source code, etc.
/// Used in conjunction with the ShaderProgram class
/// @author Jonathan Macey
/// @version 1.0
/// @date 24/11/10
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Shader
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor
  /// @param _name the name of the program object
  /// @param[in] _type the type of shader we are building
  //----------------------------------------------------------------------------------------------------------------------
  Shader( std::string _name,  SHADERTYPE _type );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor, will clean up shader source and remove shader from GL
  //----------------------------------------------------------------------------------------------------------------------
  ~Shader();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compile the current shader will check to see if source
  /// is attached and issue warning if not
  //----------------------------------------------------------------------------------------------------------------------
  void compile();
  /// @brief load in shader source and attach it to the shader object
  /// if source is already loaded it will re-load and re-attached
  /// @param _name the file name for the source we are loading
  //----------------------------------------------------------------------------------------------------------------------
  void load( std::string _name );
   //----------------------------------------------------------------------------------------------------------------------
  void loadFromString(const char **_string  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle the debug state
  //----------------------------------------------------------------------------------------------------------------------
  void toggleDebug(){m_debugState ^=true;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the shader handle for this shader
  /// @return the hand for this shader
  //----------------------------------------------------------------------------------------------------------------------
  inline GLuint getShaderHandle()const {return m_shaderHandle;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief increment the shader ref count so we can see how many
  /// program objects are using this shader
  //----------------------------------------------------------------------------------------------------------------------
  inline void incrementRefCount(){ ++m_refCount;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief decrement the reference counteer
  //----------------------------------------------------------------------------------------------------------------------
  inline void decrementRefCount(){ --m_refCount;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the number of ProgramObjects referencing this shader
  /// @returns the number of references
  //----------------------------------------------------------------------------------------------------------------------
  inline int getRefCount()const { return m_refCount; }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the shader source
  /// @returns the shader source
  //----------------------------------------------------------------------------------------------------------------------
  inline const std::string * getShaderSource() const  {return m_source;}

private :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the text name of this Shader used in the search for shader
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_name;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the actual source code for this shader (used for debug and initial loading)
  //----------------------------------------------------------------------------------------------------------------------
  std::string *m_source;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the shader has been compiled
  /// this will get channged on re-load of source to false
  //----------------------------------------------------------------------------------------------------------------------
  bool m_compiled;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief what type of shader we are
  //----------------------------------------------------------------------------------------------------------------------
  SHADERTYPE m_shaderType;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the GL handle for this shader object used in linking etc
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_shaderHandle;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate the debug state
  //----------------------------------------------------------------------------------------------------------------------
  bool m_debugState;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief number of ProgramObjects referencing this shader
  //----------------------------------------------------------------------------------------------------------------------
  int m_refCount;
#ifdef NO_PYTHON_LIB
 public :
   /// @brief public default ctor for the python bindings
   /// @note this is the easiers workaround for the non default ctor and the not_init type flags
  /// for boost::python I can figure out needs to be investigated at some stage, however we will for
  /// now trust the user not to construct a default shader object otherwise we would need to create a
  /// new method just for the python version which makes porting a bit of a pain
   inline Shader(){;}
#endif
};
} // end NGL namespace
#endif
