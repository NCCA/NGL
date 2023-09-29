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
#ifndef SHADER_H_
#define SHADER_H_

#include "Types.h"

#include <string>
#include <string_view>
namespace ngl
{

/// @enum Type of shader this object is
// for c++ 11 use enum class at present internal only
enum class ShaderType : char
{
  VERTEX,
  FRAGMENT,
  GEOMETRY,
  TESSCONTROL,
  TESSEVAL,
  COMPUTE,
  NONE
};
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
    public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor
  /// @param _name the name of the program object
  /// @param[in] _type the type of shader we are building
  //----------------------------------------------------------------------------------------------------------------------
  Shader(std::string_view _name, ShaderType _type, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor, will clean up shader source and remove shader from GL
  //----------------------------------------------------------------------------------------------------------------------
  ~Shader();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compile the current shader will check to see if source
  /// is attached and issue warning if not
  //----------------------------------------------------------------------------------------------------------------------
  bool compile() noexcept;
  /// @brief load in shader source and attach it to the shader object
  /// if source is already loaded it will re-load and re-attached
  /// @param _name the file name for the source we are loading
  //----------------------------------------------------------------------------------------------------------------------
  void load(std::string_view _name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  void loadFromString(std::string_view _string) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle the debug state
  //----------------------------------------------------------------------------------------------------------------------
  void toggleDebug() noexcept
  {
    m_debugState ^= true;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the shader handle for this shader
  /// @return the hand for this shader
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getShaderHandle() const noexcept
  {
    return m_shaderHandle;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief increment the shader ref count so we can see how many
  /// program objects are using this shader
  //----------------------------------------------------------------------------------------------------------------------
  void incrementRefCount() noexcept
  {
    ++m_refCount;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief decrement the reference counteer
  //----------------------------------------------------------------------------------------------------------------------
  void decrementRefCount() noexcept
  {
    --m_refCount;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the number of ProgramObjects referencing this shader
  /// @returns the number of references
  //----------------------------------------------------------------------------------------------------------------------
  int getRefCount() const noexcept
  {
    return m_refCount;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the shader source
  /// @returns the shader source
  //----------------------------------------------------------------------------------------------------------------------
  std::string_view getShaderSource() const noexcept
  {
    return m_source;
  }
  bool isCompiled() const noexcept
  {
    return m_compiled;
  }
  bool editShader(std::string_view _toFind, std::string_view _edit);
  void resetEdits();

    private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the text name of this Shader used in the search for shader
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_name;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the actual source code for this shader (used for debug and initial loading)
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_source;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the actual source code for this shader as loaded and may be edited.
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_originalSource;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate is the shader has been edited
  //----------------------------------------------------------------------------------------------------------------------
  bool m_edited = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the shader has been compiled
  /// this will get channged on re-load of source to false
  //----------------------------------------------------------------------------------------------------------------------
  bool m_compiled = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the GL handle for this shader object used in linking etc
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_shaderHandle;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate the debug state
  //----------------------------------------------------------------------------------------------------------------------
  bool m_debugState = true;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate the errorExit state
  //----------------------------------------------------------------------------------------------------------------------
  ErrorExit m_errorExit = ErrorExit::ON;
  //----------------------------------------------------------------------------------------------------------------------  //----------------------------------------------------------------------------------------------------------------------
  /// @brief number of ProgramObjects referencing this shader
  //----------------------------------------------------------------------------------------------------------------------
  int m_refCount;
};
} // namespace ngl
#endif
