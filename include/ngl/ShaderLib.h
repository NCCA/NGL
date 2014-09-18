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
#ifndef SHADERLIB__
#define SHADERLIB__
/// @file ShaderLib.h
/// @brief main shader loader / manager class for GLSL shaders
// must include types.h first for Real and GLEW if required

#include "Colour.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Singleton.h"
#include "Types.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Vec4.h"

#include <string>
#include <map>

//----------------------------------------------------------------------------------------------------------------------
// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include <boost/python.hpp>
  #include <boost/format.hpp>
#endif

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


class NGL_DLLEXPORT ShaderLib : public  Singleton<ShaderLib>
{
  friend class Singleton<ShaderLib>;

public :


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief create an empty ShaderProgram for us to attach shaders etc to
  /// @param _name the name of the ShaderProgram to link
  //----------------------------------------------------------------------------------------------------------------------
  void createShaderProgram( std::string _name  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief attatch a Shader to the ShaderProgram referenced by _name
  /// @param _name the name of the ShaderProgram to attach
  //----------------------------------------------------------------------------------------------------------------------
  void attachShader( std::string _name, SHADERTYPE _type );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief attatch a Shader to the ShaderProgram referenced by _name
  /// @param _program the name of the ShaderProgram to attach to
  /// @param _shader the name of the Shader to attach to Program
  //----------------------------------------------------------------------------------------------------------------------

  void attachShaderToProgram( std::string _program, std::string _shader );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the Program ID of the GL Program by name
  /// @param _name the name of the ShaderProgram to find
  /// @returns the id of the program found or -1 on error
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getProgramID(  std::string _name );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compile the shader from _name
  /// @param _name the name of the ShaderProgram to compile
  //----------------------------------------------------------------------------------------------------------------------
  void compileShader(std::string _name );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief link the program Object  from _name
  /// @param _name the name of the ShaderProgram to link
  //----------------------------------------------------------------------------------------------------------------------
  void linkProgramObject( std::string _name );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle debug mode
  //----------------------------------------------------------------------------------------------------------------------
  inline void toggleDebug() { m_debugState ^=true;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set active shader to name (if not found sets glProgramObject(0)
  /// @param _name the name of the ShaderProgram to use
  //----------------------------------------------------------------------------------------------------------------------
  void use( std::string _name );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bind an attribute at index by name
  /// @param _programName  the name of the ShaderProgram to use
  /// @param _index the attribute index to bind
  /// @param _attribName the name of the attribute in the shader to be bound to this index
  /// @note if using glsl > 400 we can use layout qualifiers and don't need this
  //----------------------------------------------------------------------------------------------------------------------
  void bindAttribute( std::string _programName, GLuint _index, std::string _attribName );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief fragment shader output location
  /// @param _programName  the name of the ShaderProgram to use
  /// @param _index the attribute index to bind
  /// @param _attribName the name of the attribute in the shader to be bound to this index
  /// @note if using glsl > 420 we can use layout qualifiers and don't need this
  //----------------------------------------------------------------------------------------------------------------------
  void bindFragDataLocation( std::string _programName, GLuint _index, std::string _attribName );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accessor to the shader program using the subscript operatoir
  /// @param _name  the name of the ShaderProgram to use
  /// @returns a ShaderProgram if name exist else null shader program
  //----------------------------------------------------------------------------------------------------------------------
  ShaderProgram * operator[](const std::string &_name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accessor to the shader program using the subscript operatoir
  /// @param _name  the name of the ShaderProgram to use
  /// @returns a ShaderProgram if name exist else null shader program
  //----------------------------------------------------------------------------------------------------------------------
  ShaderProgram * operator[](const char *_name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load shaders
  /// @param[in] _shaderName the name of the shader to be stored in the Manager
  /// @param[in] _vert the vertex shader to load
  /// @param[in] _frag the fragment shader to load
  /// @param[in] _geo an optional geo shader to load
  /// @param[in] _exitOnError exit if there is an error in the shader
  //----------------------------------------------------------------------------------------------------------------------
  void loadShader(const std::string &_shaderName, const std::string &_vert, const std::string &_frag,
                  const std::string &_geo="",
                  const bool _exitOnError=false );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Toggle debug mode on
  //----------------------------------------------------------------------------------------------------------------------
  inline void debugOn()
  {
    m_debugState=true;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Toggle debug mode off
  //----------------------------------------------------------------------------------------------------------------------
  inline void debugOff()
  {
    m_debugState=false;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the number of shaders stored
  /// @returns the number of shaders
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int getNumShaders() const
  {
    return m_shaders.size();
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the matrix to set from (float 16) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParamFromMat4(const std::string &_paramName, Mat4 _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _registeredUniformName the name of the registered uniform in the shader to set
  /// @param[in] _p1 the matrix to set from (float 16) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformFromMat4(const std::string &_registeredUniformName, Mat4 _p1  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the matrix to set from (float 16) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParamFromMat3( const std::string &_paramName, Mat3 _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the registered uniform from Max3x3
  /// @param[in] _uniformName the name of the uniform in the shader to set
  /// @param[in] _p1 the matrix to set from (float 16) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformFromMat3( const std::string &_paramName,  Mat3 _p1 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from (float 4) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParamFromVec4( const std::string &_paramName,  Vec4 _p1  );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform from an Vec4
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformVec4( const std::string &_paramName, Vec4 _p1  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from (float 4) value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParamFromColour( const std::string &_paramName, Colour _p1 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform from an Colour
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformFromColour(  const std::string &_paramName, Colour _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform from an Vector
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformVec3( const std::string &_paramName, Vec3 _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform from a Vector
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniformVec2( const std::string &_paramName, Vec2 _p1 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParam1i(const std::string &_paramName,  int _p1  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform1i(const std::string &_paramName, int _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 1 float param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParam1f(const std::string &_paramName,float _p1 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform1f(const std::string &_paramName,  float _p1 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 2 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParam2f(const std::string &_paramName, float _p1, float _p2 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform2f( const std::string &_paramName, float _p1, float _p2 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 3 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  /// @param[in] _p3 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParam3f(const std::string &_paramName, float _p1, float _p2, float _p3 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the pre-registered uniform
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  /// @param[in] _p3 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform3f(const std::string &_paramName, float _p1,float _p2, float _p3  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a shader param by name for 4 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  /// @param[in] _p3 the float value of the parameter to set
  /// @param[in] _p4 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setShaderParam4f(const std::string &_paramName,float _p1, float _p2, float _p3,float _p4 );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set the pre-registered uniform
    /// @param[in] _paramName the name of the parameter in the shader to set
    /// @param[in] _p1 the float value of the parameter to set
    /// @param[in] _p2 the float value of the parameter to set
    /// @param[in] _p3 the float value of the parameter to set
    //----------------------------------------------------------------------------------------------------------------------
    void setRegisteredUniform4f(const std::string &_paramName,float _p1,float _p2,float _p3,float _p4);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief print the properties of the currently active shader
  //----------------------------------------------------------------------------------------------------------------------
  void printProperties() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset the Shader manager which will delete all shader objects
  //----------------------------------------------------------------------------------------------------------------------
  void reset();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the index to the shader attribute location
  /// @param _shaderName the name of the shader program
  /// @param _paramName the name of the parameter to find
  /// @returns the Attrib index location
  //----------------------------------------------------------------------------------------------------------------------
  GLint getAttribLocation(const std::string &_shaderName,const std::string &_paramName );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Load shader source from text file the path will be relative from current dir
  /// unless a full path is specified
  /// @param _shaderName the name of the shader program
  /// @param _sourceFile the path of the file to load
  //----------------------------------------------------------------------------------------------------------------------
  void loadShaderSource(std::string _shaderName, std::string _sourceFile);

   //----------------------------------------------------------------------------------------------------------------------
  /// @brief load shader from a C string, useful for including code in headers etc
  /// @param _shaderName the name of the shader program
  /// @param _string the text array of shader data
  //----------------------------------------------------------------------------------------------------------------------
  void loadShaderSourceFromString( const std::string &_shaderName, const char **_string );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief use the null program (this will turn off any shaders), if using some drivers this
  /// will go to the fixed function pipeline
  //----------------------------------------------------------------------------------------------------------------------
  void useNullProgram();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief grab the index of the unifrom block, this may not be supported on all GPU's
  /// @param _uniformBlockName the name of the block to get the index for
  /// @returns the index of the block or -1 on error
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getUniformBlockIndex(const std::string &_uniformBlockName  ) const;
 //----------------------------------------------------------------------------------------------------------------------
  /// @brief register a uniform so we don't have to call glGet functions when using
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _uniformName the name of the uniform to register
  //----------------------------------------------------------------------------------------------------------------------
  void registerUniform( std::string _shaderName, std::string _uniformName  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief will parse the shader source and find any uniforms it can and register them
  /// @param[in] _shaderName the name of the shader to set the param for
  //----------------------------------------------------------------------------------------------------------------------

  void autoRegisterUniforms( std::string _shaderName );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug print any registered uniforms
  //----------------------------------------------------------------------------------------------------------------------
  void printRegisteredUniforms(std::string _shader) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Real _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Real _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Real _v0,Real _v1);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Real _v0,Real _v1);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  /// @param[in] _v2 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  /// @param[in] _v2 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  /// @param[in] _v2 the float value of the parameter to set
  /// @param[in] _v3 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2,Real _v3);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the float value of the parameter to set
  /// @param[in] _v1 the float value of the parameter to set
  /// @param[in] _v2 the float value of the parameter to set
  /// @param[in] _v3 the float value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2,Real _v3);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,GLint _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,GLint _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,GLint _v0,GLint _v1);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,GLint _v0,GLint _v1);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  /// @param[in] _v2 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  /// @param[in] _v2 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  /// @param[in] _v2 the int value of the parameter to set
  /// @param[in] _v3 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2,GLint _v3);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the int value of the parameter to set
  /// @param[in] _v1 the int value of the parameter to set
  /// @param[in] _v2 the int value of the parameter to set
  /// @param[in] _v3 the int value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2,GLint _v3);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the colour value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Colour _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Colour value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Colour _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec3 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Vec2 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec2 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Vec2 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec3 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Vec3 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec3 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Vec3 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec4 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Vec4 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Vec4 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Vec4 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Mat3 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Mat3 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Mat3 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Mat3 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Mat4 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setUniform(const std::string &_paramName,Mat4 _v0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded method to set shader Uniforms that have been pre-registered
  /// using auto-register uniforms method
  /// must be the currently active shader of else this will fail
  /// @param[in] _paramName the name of the Uniform to set
  /// @param[in] _v0 the Mat4 value of the parameter to set
  //----------------------------------------------------------------------------------------------------------------------
  void setRegisteredUniform(const std::string &_paramName,Mat4 _v0);


protected:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/TextShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  void loadTextShaders();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/ColourShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  void loadColourShaders();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/DiffuseShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  void loadDiffuseShaders();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this will load the pre-defined text rendering shaders
  /// these are stored in the file src/shaders/ToonShaders.h
  //----------------------------------------------------------------------------------------------------------------------
  void loadToonShaders();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a map of shader Programs using name as key to shader pointer
  //----------------------------------------------------------------------------------------------------------------------
  std::map <std::string,ShaderProgram *> m_shaderPrograms;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief map of shaders using name as key
  //----------------------------------------------------------------------------------------------------------------------
  std::map <std::string,Shader *> m_shaders;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief null ShaderProgram so we can return when shader not know;
  //----------------------------------------------------------------------------------------------------------------------
  ShaderProgram *m_nullProgram;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the name of the currently active shader
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_currentShader;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  flag to indicate the debug state
  //----------------------------------------------------------------------------------------------------------------------
  bool m_debugState;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the nunmber of shaders loaded
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_numShaders;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor private as a singleton
  //----------------------------------------------------------------------------------------------------------------------
  ShaderLib();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  copy ctor private as singleton
  //----------------------------------------------------------------------------------------------------------------------
  ShaderLib(
             const ShaderLib&
           );

	/// extra glue for python lib bindings nothing to see here (unless ....)
	#ifdef NO_PYTHON_LIB
		public :
			ShaderProgram *getShaderProgram(
																			const std::string &_programName
																		 );
	#endif


}; // end of class

} // end ngl Namespace

#endif
//----------------------------------------------------------------------------------------------------------------------

