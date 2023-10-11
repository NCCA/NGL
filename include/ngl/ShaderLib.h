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
#ifndef SHADERLIB_
#define SHADERLIB_
/// @file ShaderLib.h
/// @brief main shader loader / manager class for GLSL shaders
// must include types.h first for Real and GLEW if required

#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Types.h"
#include "Vec4.h"
#ifdef USEGLM
#include <glm/glm.hpp>
#endif
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <iostream>
#include <algorithm>


//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
///  @class ShaderLib  "include/ShaderLib.h"
///  @brief Singleton Class to init and Use GLSL Shaders
///  the class stores the shaders as a map of shader objects and they can be found by name
/// Updated to use templated singleton
/// Updated to use a map to store the shaders by name and hence removed the name from the ShaderObject Class
/// Also Added methods to adjust shader parameters by shader / param name, at present use only 1-4 Floats and
/// a few others need to think of a better way of doing this
///  @author Jonathan Macey
///  @version 3.0
///  @date Last Revision 20/04/10 used templated singleton
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT ShaderLib
{

    public:
  enum class MatrixTranspose : bool
  {
    TransposeOn = GL_TRUE,
    TransposeOff = GL_FALSE
  };
  static void loadDefaultShaders();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief create an empty ShaderProgram for us to attach shaders etc to
  /// @param _name the name of the ShaderProgram to link
  //----------------------------------------------------------------------------------------------------------------------
  static void createShaderProgram(std::string_view _name, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief attatch a Shader to the ShaderProgram referenced by _name
  /// @param _name the name of the ShaderProgram to attach
  //----------------------------------------------------------------------------------------------------------------------
  static void attachShader(std::string_view _name, ShaderType _type, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief attatch a Shader to the ShaderProgram referenced by _name
  /// @param _program the name of the ShaderProgram to attach to
  /// @param _shader the name of the Shader to attach to Program
  //----------------------------------------------------------------------------------------------------------------------

  static void attachShaderToProgram(std::string_view _program, std::string_view _shader) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the Program ID of the GL Program by name
  /// @param _name the name of the ShaderProgram to find
  /// @returns the id of the program found or -1 on error
  //----------------------------------------------------------------------------------------------------------------------
  static GLuint getProgramID(std::string_view _name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compile the shader from _name
  /// @param _name the name of the ShaderProgram to compile
  //----------------------------------------------------------------------------------------------------------------------
  static bool compileShader(std::string_view _name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief link the program Object  from _name
  /// @param _name the name of the ShaderProgram to link
  //----------------------------------------------------------------------------------------------------------------------
  static bool linkProgramObject(std::string_view _name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle debug mode
  //----------------------------------------------------------------------------------------------------------------------
  static void toggleDebug() noexcept
  {
    m_debugState ^= true;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set active shader to name (if not found sets glProgramObject(0)
  /// @param _name the name of the ShaderProgram to use
  //----------------------------------------------------------------------------------------------------------------------
  static void use(std::string_view _name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief edit the shader source
  /// @param _name the name of the ShaderProgram to use
  //----------------------------------------------------------------------------------------------------------------------
  static bool editShader(std::string_view _shader, std::string_view _toFind, std::string_view _edit);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset all edits
  //----------------------------------------------------------------------------------------------------------------------
  static void resetEdits(std::string_view _shader);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind an attribute at index by name
  /// @param _programName  the name of the ShaderProgram to use
  /// @param _index the attribute index to bind
  /// @param _attribName the name of the attribute in the shader to be bound to this index
  /// @note if using glsl > 400 we can use layout qualifiers and don't need this
  //----------------------------------------------------------------------------------------------------------------------
  static void bindAttribute(std::string_view _programName, GLuint _index, std::string_view _attribName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief fragment shader output location
  /// @param _programName  the name of the ShaderProgram to use
  /// @param _index the attribute index to bind
  /// @param _attribName the name of the attribute in the shader to be bound to this index
  /// @note if using glsl > 420 we can use layout qualifiers and don't need this
  //----------------------------------------------------------------------------------------------------------------------
  static void bindFragDataLocation(std::string_view _programName, GLuint _index, std::string_view _attribName) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load shaders
  /// @param[in] _shaderName the name of the shader to be stored in the Manager
  /// @param[in] _vert the vertex shader to load
  /// @param[in] _frag the fragment shader to load
  /// @param[in] _geo an optional geo shader to load
  /// @param[in] _exitOnError exit if there is an error in the shader
  //----------------------------------------------------------------------------------------------------------------------
  static bool loadShader(std::string_view _shaderName, std::string_view _vert, std::string_view _frag, std::string_view _geo, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
  
  static bool loadShader(std::string_view _shaderName, std::string_view _vert, std::string_view _frag, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load multiple shaders from a json file
  /// @param[in] _shaderName the name of the json resource file
  static bool loadFromJson(std::string_view _fname) noexcept;
  static void setJsonUniform(std::string_view _name, std::string_view _type, std::string_view _value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Toggle debug mode on
  //----------------------------------------------------------------------------------------------------------------------
  static void debugOn() noexcept
  {
    m_debugState = true;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Toggle debug mode off
  //----------------------------------------------------------------------------------------------------------------------
  static void debugOff() noexcept
  {
    m_debugState = false;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the number of shaders stored
  /// @returns the number of shaders
  //----------------------------------------------------------------------------------------------------------------------
  static size_t getNumShaders() noexcept
  {
    return m_shaders.size();
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief print the properties of the currently active shader
  //----------------------------------------------------------------------------------------------------------------------
  static void printProperties() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset the Shader manager which will delete all shader objects
  //----------------------------------------------------------------------------------------------------------------------
  static void reset() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the current shader name
  //----------------------------------------------------------------------------------------------------------------------
  static std::string getCurrentShaderName()
  {
    return m_currentShader;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the index to the shader attribute location
  /// @param _shaderName the name of the shader program
  /// @param _paramName the name of the parameter to find
  /// @returns the Attrib index location
  //----------------------------------------------------------------------------------------------------------------------
  static GLint getAttribLocation(std::string_view _shaderName, std::string_view _paramName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Load shader source from text file the path will be relative from current dir
  /// unless a full path is specified
  /// @param _shaderName the name of the shader program
  /// @param _sourceFile the path of the file to load
  //----------------------------------------------------------------------------------------------------------------------
  static void loadShaderSource(std::string_view _shaderName, std::string_view _sourceFile) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load shader from a C string, useful for including code in headers etc
  /// @param _shaderName the name of the shader program
  /// @param _string the text array of shader data
  //----------------------------------------------------------------------------------------------------------------------
  static void loadShaderSourceFromString(std::string_view _shaderName, std::string_view _string) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief use the null program (this will turn off any shaders), if using some drivers this
  /// will go to the fixed function pipeline
  //----------------------------------------------------------------------------------------------------------------------
  static void useNullProgram() noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief grab the index of the unifrom block, this may not be supported on all GPU's
  /// @param _uniformBlockName the name of the block to get the index for
  /// @returns the index of the block or -1 on error
  //----------------------------------------------------------------------------------------------------------------------
  static GLuint getUniformBlockIndex(std::string_view _uniformBlockName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief register a uniform so we don't have to call glGet functions when using
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _uniformName the name of the uniform to register
  //----------------------------------------------------------------------------------------------------------------------
  static void registerUniform(std::string_view _shaderName, std::string_view _uniformName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief will parse the shader source and find any uniforms it can and register them
  /// @param[in] _shaderName the name of the shader to set the param for
  //----------------------------------------------------------------------------------------------------------------------

  static void autoRegisterUniforms(std::string_view _shaderName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug print any registered uniforms
  //----------------------------------------------------------------------------------------------------------------------
  static void printRegisteredUniforms(std::string_view _shader) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to return a shader ID
  /// @param _shaderName the name of the shader who's ID to return
  //----------------------------------------------------------------------------------------------------------------------
  static GLuint getShaderID(std::string_view _shaderName) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to return the specified shader object
  /// @param _shaderName the name of the shader to return
  //----------------------------------------------------------------------------------------------------------------------
  static bool setUniformBuffer(std::string_view _uniformBlockName, size_t _size, void *_data);

  
  template< typename Ts>
  static bool setUniform(std::string_view _varname ,Ts &&arg )  noexcept;
  template< typename... Ts>
  static bool setUniform(std::string_view _varname ,Ts &&...args )  noexcept;

  template< typename Ts>
  static bool getUniform(std::string_view _varname ,Ts &&arg )  noexcept;
  template< typename... Ts>
  static bool getUniform(std::string_view _varname ,Ts &&...args )  noexcept;
  

    protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  get shader type from string (used for json parsing)
  //----------------------------------------------------------------------------------------------------------------------
  static ShaderType getShaderType(std::string_view type) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/TextShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  static void loadTextShaders() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/ColourShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  static void loadColourShaders() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/DiffuseShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  static void loadDiffuseShaders() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/ToonShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  static void loadCheckerShaders() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a map of shader Programs using name as key to shader pointer
  //----------------------------------------------------------------------------------------------------------------------
  static std::unordered_map< std::string, std::unique_ptr< ShaderProgram>> m_shaderPrograms;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief map of shaders using name as key
  //----------------------------------------------------------------------------------------------------------------------
  static std::unordered_map< std::string, std::unique_ptr< Shader>> m_shaders;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief null ShaderProgram so we can return when shader not know;
  //----------------------------------------------------------------------------------------------------------------------
  static std::unique_ptr< ShaderProgram > m_nullProgram;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the name of the currently active shader
  //    ----------------------------------------------------------------------------------------------------------------------
  static std::string m_currentShader;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  flag to indicate the debug state
  //----------------------------------------------------------------------------------------------------------------------
  static bool m_debugState;

  static bool m_defaultShadersLoaded;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor private as a singleton
  //----------------------------------------------------------------------------------------------------------------------
  ShaderLib()=default ;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor private as a singleton
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~ShaderLib() noexcept
  {
    reset();
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  copy ctor private as singleton
  //----------------------------------------------------------------------------------------------------------------------
  ShaderLib(const ShaderLib &) = delete;

}; // end of class

#include "ngl/ShaderLib.inl"

} // namespace ngl

#endif
//----------------------------------------------------------------------------------------------------------------------
