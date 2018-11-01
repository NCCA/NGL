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

#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_
#include "Shader.h"
#include "Types.h"
#include "Util.h"
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"
#include <vector>
#include <unordered_map>

//----------------------------------------------------------------------------------------------------------------------
///  @class ShaderProgram  "ShaderProgram.h"
///  @brief This class contains a single ShaderProgram which may have many
///  different shaders attached to it as well as wrappers to call the various
/// OpenGL functions to set paramaters for this Program
///  @author Jonathan Macey
///  @version 1.0
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

class NGL_DLLEXPORT ShaderProgram
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief create an OpenGL shader program
  /// it is initially empty and just has a name for id
  /// @param _name the name of the Program Object
  //----------------------------------------------------------------------------------------------------------------------
  ShaderProgram(const std::string &_name, ErrorExit _exitOnError=ErrorExit::ON ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~ShaderProgram();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief use this Shader object as the current Active shader
  /// once this is set it is active until unbind us called
  //----------------------------------------------------------------------------------------------------------------------
  void use() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to unbind the current Program Object
  /// this will set the shader to be the glUseProgram(0) default value
  /// @note if we don't use this we will lose the m_active state values and we will not
  /// be able to check the current active state etc so use this once shader is finished.
  //----------------------------------------------------------------------------------------------------------------------
  void unbind() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief attach a shader to the ProgramObject
  /// @param _shader the Shader object to attach
  /// \note we can attach many shaders to the ProgramObject.
  //----------------------------------------------------------------------------------------------------------------------
  void attachShader( Shader *_shader ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind an attribute in the Program object to _index using attribname
  /// @param _index the index number we wish to bind to
  /// @param _attribName the name of the attribute we wish to use
  //----------------------------------------------------------------------------------------------------------------------
  void bindAttribute(GLuint index, const std::string &_attribName ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind fragment output location in the Program object to _index using attribname
  /// @param _index the index number we wish to bind to
  /// @param _attribName the name of the attribute we wish to use
  //----------------------------------------------------------------------------------------------------------------------
  void bindFragDataLocation(GLuint index, const std::string &_attribName ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief link our program object with the attatched shaders
  /// if shader are not attached the program will report the linker
  /// errors
  //----------------------------------------------------------------------------------------------------------------------
  bool link() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the ProgramID for the Program
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getID() const noexcept{return m_programID;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  returns the ID of the uniform attribute called 'name'.
  /// @return the uniform variable id
  //----------------------------------------------------------------------------------------------------------------------
  GLint getUniformLocation( const char* _name) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief   lists the available uniforms for the shader (this was a pain because the compiler quietly gets rid of unused uniforms).
  ///  method written by Richard Southern.
  //----------------------------------------------------------------------------------------------------------------------
  void printActiveUniforms() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief   lists the available Attributes for the shader (this was a pain because the compiler quietly gets rid of unused uniforms).
  ///  method written by Richard Southern.
  //----------------------------------------------------------------------------------------------------------------------
  void printActiveAttributes() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief   calls the printActiveUniforms followed by Attribs
  ///  method written by Richard Southern.
  //----------------------------------------------------------------------------------------------------------------------
  void printProperties() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @name  Set uniform argument values from the argument name
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single float
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform1f(const std::string &_varname, float _v0 ) const noexcept;
  void getRegisteredUniform1f(const std::string &_varname, float &o_v0 ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single float
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform2f(const std::string &_varname, float _v0, float _v1 ) const noexcept;
  void getRegisteredUniform2f(const std::string &_varname, float &o_v0, float &o_v1 ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single float
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable
  /// @param  _v2 - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform3f( const std::string &_varname,float _v0, float _v1, float _v2 ) const noexcept;
  void getRegisteredUniform3f( const std::string &_varname,float &_v0, float &_v1, float &_v2 ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single float
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable
  /// @param  _v2 - new value for the variable
  /// @param  _v3 - new value for the variable
  /////----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform4f(const std::string &_varname, float _v0,float _v1,float _v2, float _v3 ) const noexcept;
  void getRegisteredUniform4f( const std::string &_varname,float &_v0, float &_v1, float &_v2 , float &o_v3) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single int
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform1i(const std::string &_varname, int _v0  ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single int
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable

  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform2i(const std::string &_varname, int _v0, int _v1 ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single int
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable
  /// @param  _v2 - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform3i(const std::string &_varname, int _v0, int _v1,int _v2 ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the registered uniform to a single int
  /// @param  _varname - name of the uniform variable
  /// @param  _v0 - new value for the variable
  /// @param  _v1 - new value for the variable
  /// @param  _v2 - new value for the variable
  /// @param  _v3 - new value for the variable

  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform4i( const std::string &_varname,int _v0, int _v1, int _v2, int _v3 ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @name  Set Program Matrix Args
  //----------------------------------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets '_varname' as a 3D matrix array
  /// @param  _varname - name of the uniform variable
  /// @param  _count - num elements in the array
  /// @param  _transpose - if true will transpose the matrix values
  /// @param  _value - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformMatrix2fv(const std::string  &_varname, GLsizei _count, bool _transpose, const float* _value ) const noexcept;
  void getRegisteredUniformMatrix2fv(const std::string  &_varname, ngl::Mat2 &o_value ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets '_varname' as a 3D matrix array
  /// @param  _varname - name of the uniform variable
  /// @param  _count - num elements in the array
  /// @param  _transpose - if true will transpose the matrix values
  /// @param  _value - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformMatrix3fv(const std::string  &_varname, GLsizei _count, bool _transpose, const float* _value ) const noexcept;
  void getRegisteredUniformMatrix3fv(const std::string  &_varname, ngl::Mat3 &o_value ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets '_varname' as a 4D matrix array
  /// @param  _varname - name of the uniform variable
  /// @param  _count - num elements in the array
  /// @param  _transpose - if true will transpose the matrix values
  /// @param  _value - new value for the variable
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformMatrix4fv(const std::string  &_varname, GLsizei _count,  bool _transpose, const float* _value ) const noexcept;
  void getRegisteredUniformMatrix4fv(const std::string  &_varname, ngl::Mat4 &o_value ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  gets the current value of the specified uniform var
  /// @param  _name - name of the uniform variable to retrieve
  /// @param  o_values - the output value
  //----------------------------------------------------------------------------------------------------------------------
  void getUniformfv( const char* _name, float* o_values ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  gets the current value of the specified uniform var
  /// @param  _name - name of the uniform variable to retrieve
  /// @param  o_values - the output value
  //----------------------------------------------------------------------------------------------------------------------
  void getUniformiv( const char* _name, int* o_values ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @name   vertex array functions.
  /// @brief  These functions simplify the binding of per-vertex data as a
  ///         vertex array (or VBO).
  //----------------------------------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  enables the specified varying array
  /// @param  _name - the name of the varying attr array to enable
  //----------------------------------------------------------------------------------------------------------------------
  void enableAttribArray(const char* _name ) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  disables the specified varying array
  /// @param  _name - the name of the varying attr array to enable
  //----------------------------------------------------------------------------------------------------------------------
  void disableAttribArray(const char* _name) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  scan the shader source and find any uniforms and register them
  //----------------------------------------------------------------------------------------------------------------------
  void autoRegisterUniforms() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  scan the shader source and find any uniforms blocks and register them (will create buffers too)
  //----------------------------------------------------------------------------------------------------------------------
  void autoRegisterUniformBlocks() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  debug print the registered uniforms
  //----------------------------------------------------------------------------------------------------------------------
  void printRegisteredUniforms()const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind the fragment shader output
  /// @param [in] _colourNumber The color number to bind the user-defined varying out variable to
  /// @param [in] _name the name of the output variable to bind
  //----------------------------------------------------------------------------------------------------------------------
  void bindFragDataLocation(GLuint _colourNumber, const char *_name) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  get the index of a uniform bloc
  /// @param[in] _uniformBlockName the name of the uniform block to get the id for
  /// @returns the id of the block
  //----------------------------------------------------------------------------------------------------------------------

  GLuint getUniformBlockIndex( const std::string &_uniformBlockName  )const noexcept;


  void setUniformBuffer(const std::string &_uniformBlockName, size_t _size, void *_data);
  bool isLinked() const noexcept {return m_linked;}

private :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the current Program has been linked
  //----------------------------------------------------------------------------------------------------------------------
  bool m_linked=false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of the shader objects attached to the program
  //----------------------------------------------------------------------------------------------------------------------
  std::vector <Shader *> m_shaders;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the program id for this program object
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_programID=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug mode flag
  //----------------------------------------------------------------------------------------------------------------------
  bool m_debugState=true;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief errorExit mode flag
  //----------------------------------------------------------------------------------------------------------------------
  ErrorExit  m_errorExit=ErrorExit::ON;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief text name of the current program used in lookup and debugging
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_programName;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of attributes for this object, mapping name to ID number
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map <std::string, GLuint > m_attribs;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this structure holds information about the registered uniforms in the program
  /// id is the uniform location, name is the uniform name, type is the GLenum type
  //----------------------------------------------------------------------------------------------------------------------

  struct uniformData
  {
    GLint loc;
    std::string name;
    GLenum type;
  };

  struct uniformBlockData
  {
    GLuint loc;
    std::string name;
    GLuint buffer;
  };
  std::string getValueFromShader(const uniformData &_d)const noexcept ;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of uniforms for this object, mapping name to ID number must be added by the user
  /// using the registerUniform method
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map <std::string, uniformData> m_registeredUniforms;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of uniform blocks for this object, mapping name to ID number must be added by the user
  /// using the registerUniformBlock method
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map <std::string, uniformBlockData> m_registeredUniformBlocks;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief indicate if this program is the current active program
  //----------------------------------------------------------------------------------------------------------------------
  bool m_active=false;
  //----------------------------------------------------------------------------------------------------------------------

};
} // end NGL namespace
#endif
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
