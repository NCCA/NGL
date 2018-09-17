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

//#include <QFile>
#include <fstream>
#include "Shader.h"
#include <string> // needed for windows build as get error otherwise
#include <memory>
//----------------------------------------------------------------------------------------------------------------------
/// @file Shader.cpp
/// @brief implementation files for Shader class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
void printInfoLog( const GLuint &_obj)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
  std::unique_ptr<char []> infoLog;
  glGetShaderiv(_obj, GL_INFO_LOG_LENGTH,&infologLength);
  //std::cerr<<"info log length "<<infologLength<<'\n';
  if(infologLength > 0)
  {
    infoLog.reset (new char[infologLength]);
    glGetShaderInfoLog(_obj, infologLength, &charsWritten, infoLog.get());

    msg->addError(infoLog.get(),TimeFormat::NONE);
	}

}


Shader::Shader(const std::string_view &_name,  ShaderType _type , bool _exitOnError) noexcept
{
  m_name=_name;
  m_shaderType = _type;
  m_errorExit=_exitOnError;
  switch (_type)
  {
    case ShaderType::VERTEX : { m_shaderHandle = glCreateShader(GL_VERTEX_SHADER); break; }
    case ShaderType::FRAGMENT : { m_shaderHandle = glCreateShader(GL_FRAGMENT_SHADER); break; }
    #ifndef USINGIOS_
      case ShaderType::GEOMETRY : { m_shaderHandle = glCreateShader(GL_GEOMETRY_SHADER); break; }
      case ShaderType::TESSCONTROL : { m_shaderHandle =glCreateShader(GL_TESS_CONTROL_SHADER); break; }
      case ShaderType::TESSEVAL : { m_shaderHandle =glCreateShader(GL_TESS_EVALUATION_SHADER); break; }
      case ShaderType::COMPUTE :
      #if defined(__APPLE__)
       msg->addError("Apple doesn't support Computer Shaders ");
      #else
        {
          m_shaderHandle =glCreateShader(GL_COMPUTE_SHADER);
        }
      #endif
      break;
    #endif
    case ShaderType::NONE :{;}
  }
  m_compiled = false;
  m_refCount=0;
}
Shader::~Shader()
{
  msg->addMessage(fmt::format("removing shader {0}",m_name),Colours::WHITE,TimeFormat::NONE);
  glDeleteShader(m_shaderHandle);
}

bool Shader::compile() noexcept
{
  if (m_source.empty() )
  {
    msg->addError("Warning no shader source loaded");
    return false;
  }

  glCompileShader(m_shaderHandle);

  GLint compileStatus = 0;
  glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS,&compileStatus);
  m_compiled=static_cast<bool>(compileStatus);
  if(m_debugState==true)
  {
    msg->addMessage(fmt::format("Compiling Shader {0}",m_name));
    if( compileStatus == GL_FALSE)
    {
      msg->addError("Shader compile failed or had warnings ");
      printInfoLog(m_shaderHandle);
      if(m_errorExit)
        exit(EXIT_FAILURE);
    }
  }
  return m_compiled;
}


void Shader::load(const std::string_view &_name ) noexcept
{
  // see if we already have some source attached
  if(!m_source.empty())
  {
    msg->addWarning("deleting existing source code\n");
    m_source.clear();
  }
  std::ifstream shaderSource(_name.data());
  if (!shaderSource.is_open())
  {
   msg->addError(fmt::format("File not found {0}",_name.data()));
   exit(EXIT_FAILURE);
  }
  // now read in the data
  m_source =  std::string((std::istreambuf_iterator<char>(shaderSource)), std::istreambuf_iterator<char>());
  shaderSource.close();
  // glShaderSource needs null terminated const char *
  m_source+='\0';
  const char* data=m_source.c_str();
  glShaderSource(m_shaderHandle , 1, &data,nullptr);
  m_compiled=false;

  if (m_debugState == true)
  {
    printInfoLog(m_shaderHandle);
  }
}

void Shader::loadFromString(const std::string_view &_string ) noexcept
{
  // see if we already have some source attached
  if(m_source.size()!=0)
  {
    msg->addWarning("deleting existing source code\n");
    m_source.clear();
  }

  // we need this for the check in the compile bit
  m_source=_string;
  const char* data=m_source.c_str();

  glShaderSource(m_shaderHandle , 1, &data,nullptr);
  m_compiled=false;
 if (m_debugState == true)
  {
    printInfoLog(m_shaderHandle);
  }
}

} // end ngl namespace
