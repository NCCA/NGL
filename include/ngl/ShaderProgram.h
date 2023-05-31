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
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Shader.h"
#include "Types.h"
#include "Util.h"
#include <string_view>
#include <unordered_map>
#include <vector>
#include <ngl/NGLStream.h>
#include <iostream>
#include <cassert>
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
    public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief create an OpenGL shader program
  /// it is initially empty and just has a name for id
  /// @param _name the name of the Program Object
  //----------------------------------------------------------------------------------------------------------------------
  ShaderProgram(std::string_view _name, ErrorExit _exitOnError = ErrorExit::ON) noexcept;
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
  void attachShader(Shader *_shader) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind an attribute in the Program object to _index using attribname
  /// @param _index the index number we wish to bind to
  /// @param _attribName the name of the attribute we wish to use
  //----------------------------------------------------------------------------------------------------------------------
  void bindAttribute(GLuint index, std::string_view _attribName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind fragment output location in the Program object to _index using attribname
  /// @param _index the index number we wish to bind to
  /// @param _attribName the name of the attribute we wish to use
  //----------------------------------------------------------------------------------------------------------------------
  void bindFragDataLocation(GLuint index, std::string_view _attribName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief link our program object with the attatched shaders
  /// if shader are not attached the program will report the linker
  /// errors
  //----------------------------------------------------------------------------------------------------------------------
  bool link() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the ProgramID for the Program
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getID() const noexcept
  {
    return m_programID;
  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  returns the ID of the uniform attribute called 'name'.
  /// @return the uniform variable id
  //----------------------------------------------------------------------------------------------------------------------
  GLint getUniformLocation(const char *_name) const noexcept;

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

  // template< typename Ts> 
  // bool setRegisteredUniform(std::string_view _varname ,Ts &&arg ) const noexcept
  // {
  //   auto uniform = m_registeredUniforms.find(_varname.data());
  //   if(uniform != m_registeredUniforms.end())
  //   {
  //     if constexpr (std::is_same<Ts,float&>::value )
  //     {
  //         glUniform1f(uniform->second.loc, arg);
  //         return true;
  //     } // end of float
  //     else if constexpr (std::is_same<Ts,int&>::value )
  //     {
  //         glUniform1i(uniform->second.loc, arg);
  //         return true;
  //     }// end of int
  //     else if constexpr(std::is_same<Ts,Mat2&>::value)
  //     {
  //         glUniformMatrix2fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
  //         return true;
  //     } // end of mat2

  //     else if constexpr(std::is_same<Ts,Mat3&>::value)
  //     {
  //         glUniformMatrix3fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
  //         return true;
  //     } // end of mat3
  //     else if constexpr(std::is_same<Ts,Mat4&>::value)
  //     {
  //         glUniformMatrix4fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
  //         return true;
  //     } // end of mat4
  //     else if constexpr(std::is_same<Ts,glm::mat2&>::value)
  //     {
  //         glUniformMatrix2fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
  //         return true;
  //     } // end of glmmat2
  //     else if constexpr(std::is_same<Ts,glm::mat3&>::value)
  //     {
  //         glUniformMatrix3fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
  //         return true;
  //     } // end of glmmat3
  //     else if constexpr(std::is_same<Ts,glm::mat4&>::value)
  //     {
  //         glUniformMatrix4fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
  //         return true;
  //     } // end of glmmat2
  //     else if constexpr(std::is_same<Ts,Vec2&>::value)
  //     {
  //         glUniform2f(uniform->second.loc,arg.m_x,arg.m_y);
  //         return true;
  //     }
  //     else if constexpr(std::is_same<Ts,Vec3&>::value)
  //     {
  //         glUniform3f(uniform->second.loc,arg.m_x,arg.m_y,arg.m_z);
  //         return true;
  //     }
  //     else if constexpr(std::is_same<Ts,Vec4&>::value)
  //     {
  //         glUniform4f(uniform->second.loc,arg.m_x,arg.m_y,arg.m_z,arg.m_w);
  //         return true;
  //     }
  //     else if constexpr(std::is_array<Ts>::value)
  //     {
  //       std::cout<<"have array\n";
  //       return true;
  //     }
  //   }
  //   else
  //   {
  //       ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
  //       return false;
  //   }
  //   return false;
  // }

  
  // template< typename... Ts>
  // bool setRegisteredUniform(std::string_view _varname ,Ts &&...args ) const noexcept
  // {
  //   auto uniform = m_registeredUniforms.find(_varname.data());
  //   // make sure we have a valid shader
  //   if(uniform != m_registeredUniforms.end())
  //   {         
  //     if constexpr (std::conjunction_v<std::is_same<float&, Ts>...>)
  //     {
  //         if constexpr (sizeof...(args) == 2)
  //         {
  //             auto values =std::forward_as_tuple(args...);        
  //             glUniform2f(uniform->second.loc,std::get<0>(values),std::get<1>(values));
  //             return true;
  //         }
  //         else if constexpr (sizeof...(args) == 3)
  //         {
  //             auto values = std::forward_as_tuple(args...);
  //             glUniform3f(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values));
  //             return true;
  //         }
  //         else if constexpr (sizeof...(args) == 4)
  //         {
  //             auto values = std::forward_as_tuple(args...);
  //             glUniform4f(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values),std::get<3>(values));
  //             return true;
  //         }
  //         else
  //         {
  //             ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
  //            return false;
  //         }
  //     } // end float values
  //   else if constexpr (std::conjunction_v<std::is_same<int&, Ts>...>)
  //   {
  //   if constexpr (sizeof...(args) == 2)
  //       {
  //           auto values =std::forward_as_tuple(args...);        
  //           glUniform2i(uniform->second.loc,std::get<0>(values),std::get<1>(values));
  //           return true;
  //       }
  //       else if constexpr (sizeof...(args) == 3)
  //       {
  //           auto values = std::forward_as_tuple(args...);
  //           glUniform3i(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values));
  //           return true;
  //       }
  //       else if constexpr (sizeof...(args) == 4)
  //       {
  //           auto values = std::forward_as_tuple(args...);
  //           glUniform4i(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values),std::get<3>(values));
  //           return true;
  //       }
  //       else
  //       {
  //           ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));

  //           return false;
  //       }
  //   }
  //   }
  // return false;
  // }


  template< typename Ts> 
  bool setRegisteredUniform(std::string_view _varname ,Ts &&arg ) const noexcept;

  template< typename... Ts>
  bool setRegisteredUniform(std::string_view _varname ,Ts &&...args ) const noexcept;

  bool getRegisteredUniform1f(std::string_view _varname, float &o_v0) const noexcept;
  bool getRegisteredUniform2f(std::string_view _varname, float &o_v0, float &o_v1) const noexcept;
  bool getRegisteredUniform3f(std::string_view _varname, float &_v0, float &_v1, float &_v2) const noexcept;
  bool getRegisteredUniform4f(std::string_view _varname, float &_v0, float &_v1, float &_v2, float &o_v3) const noexcept;
  bool getRegisteredUniform1i(std::string_view _varname, int& o_v0) const noexcept;
  bool getRegisteredUniform2i(std::string_view _varname, int &o_v0, int &o_v1) const noexcept;
  bool getRegisteredUniform3i(std::string_view _varname, int &o_v0, int &o_v1,int &o_v2) const noexcept;
  bool getRegisteredUniform4i(std::string_view _varname, int &o_v0, int &o_v1,int &o_v2,int &o_v3) const noexcept;
  bool getRegisteredUniformMatrix2fv(std::string_view _varname, ngl::Mat2 &o_value) const noexcept;
  bool getRegisteredUniformMatrix3fv(std::string_view _varname, ngl::Mat3 &o_value) const noexcept;
  bool getRegisteredUniformMatrix4fv(std::string_view _varname, ngl::Mat4 &o_value) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  gets the current value of the specified uniform var
  /// @param  _name - name of the uniform variable to retrieve
  /// @param  o_values - the output value
  //----------------------------------------------------------------------------------------------------------------------
  void getUniformfv(const char *_name, float *o_values) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  gets the current value of the specified uniform var
  /// @param  _name - name of the uniform variable to retrieve
  /// @param  o_values - the output value
  //----------------------------------------------------------------------------------------------------------------------
  void getUniformiv(const char *_name, int *o_values) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @name   vertex array functions.
  /// @brief  These functions simplify the binding of per-vertex data as a
  ///         vertex array (or VBO).
  //----------------------------------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  enables the specified varying array
  /// @param  _name - the name of the varying attr array to enable
  //----------------------------------------------------------------------------------------------------------------------
  void enableAttribArray(const char *_name) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  disables the specified varying array
  /// @param  _name - the name of the varying attr array to enable
  //----------------------------------------------------------------------------------------------------------------------
  void disableAttribArray(const char *_name) const noexcept;

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
  void printRegisteredUniforms() const noexcept;

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

  GLuint getUniformBlockIndex(std::string_view _uniformBlockName) const noexcept;

  bool setUniformBuffer(std::string_view _uniformBlockName, size_t _size, void *_data);
  
  bool isLinked() const noexcept 
  {
    return m_linked;
  }

    private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the current Program has been linked
  //----------------------------------------------------------------------------------------------------------------------
  bool m_linked = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of the shader objects attached to the program
  //----------------------------------------------------------------------------------------------------------------------
  std::vector< Shader * > m_shaders;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the program id for this program object
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_programID = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug mode flag
  //----------------------------------------------------------------------------------------------------------------------
  bool m_debugState = true;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief errorExit mode flag
  //----------------------------------------------------------------------------------------------------------------------
  ErrorExit m_errorExit = ErrorExit::ON;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief text name of the current program used in lookup and debugging
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_programName;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of attributes for this object, mapping name to ID number
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map< std::string, GLuint > m_attribs;
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
  std::string getValueFromShader(const uniformData &_d) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of uniforms for this object, mapping name to ID number must be added by the user
  /// using the registerUniform method
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map< std::string, uniformData > m_registeredUniforms;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a list of uniform blocks for this object, mapping name to ID number must be added by the user
  /// using the registerUniformBlock method
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map< std::string, uniformBlockData > m_registeredUniformBlocks;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief indicate if this program is the current active program
  //----------------------------------------------------------------------------------------------------------------------
  bool m_active = false;
  //----------------------------------------------------------------------------------------------------------------------
};

#include "ngl//ShaderProgram.inl"
} // namespace ngl
#endif
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
