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

#include <QFile>
#include <fstream>
#include "Shader.h"


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
	char *infoLog;

  glGetShaderiv(_obj, GL_INFO_LOG_LENGTH,&infologLength);
  //std::cerr<<"info log length "<<infologLength<<"\n";
  if(infologLength > 0)
  {
    infoLog = new char[infologLength];
    glGetShaderInfoLog(_obj, infologLength, &charsWritten, infoLog);

		std::cerr<<infoLog<<std::endl;
		delete [] infoLog;

	}

}


Shader::Shader( std::string _name,  ShaderType _type ) noexcept
{
  m_name=_name;
  m_shaderType = _type;
  m_debugState = true;
  m_compiled=false;

  switch (_type)
  {
    case ShaderType::VERTEX : { m_shaderHandle = glCreateShader(GL_VERTEX_SHADER); break; }
    case ShaderType::FRAGMENT : { m_shaderHandle = glCreateShader(GL_FRAGMENT_SHADER); break; }
    case ShaderType::GEOMETRY : { m_shaderHandle = glCreateShader(GL_GEOMETRY_SHADER); break; }
    case ShaderType::TESSCONTROL : { m_shaderHandle =glCreateShader(GL_TESS_CONTROL_SHADER); break; }
    case ShaderType::TESSEVAL : { m_shaderHandle =glCreateShader(GL_TESS_EVALUATION_SHADER); break; }
    case ShaderType::COMPUTE : { m_shaderHandle =glCreateShader(GL_COMPUTE_SHADER); break; }
    case ShaderType::NONE :{;}
  }
  m_compiled = false;
  m_refCount=0;
}
Shader::~Shader()
{
  std::cerr<<"removing shader "<<m_name<<"\n";
  glDeleteShader(m_shaderHandle);
}

void Shader::compile() noexcept
{
  if (m_source.empty() )
  {
    std::cerr<<"Warning no shader source loaded\n";
    return;
  }

  glCompileShader(m_shaderHandle);
  if(m_debugState==true)
  {
    GLint infologLength = 0;
    std::cerr <<"Compiling Shader "<<m_name<<"\n";
    glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS,&infologLength);
    if( infologLength == GL_FALSE)
    {
      std::cerr<<"Shader compile failed or had warnings \n";
      printInfoLog(m_shaderHandle);
      exit(EXIT_FAILURE);
    }
  }
  m_compiled=true;
}


void Shader::load( std::string _name ) noexcept
{
  // see if we already have some source attached
  if(m_source.empty())
  {
    std::cerr<<"deleting existing source code\n";
    m_source.clear();
  }
  std::ifstream shaderSource(_name.c_str());
  if (!shaderSource.is_open())
  {
   std::cerr<<"File not found "<<_name.c_str()<<"\n";
   exit(EXIT_FAILURE);
  }
  // now read in the data
  m_source =  std::string((std::istreambuf_iterator<char>(shaderSource)), std::istreambuf_iterator<char>());
  shaderSource.close();
  // glShaderSource needs null terminated const char *
  m_source+='\0';
  const char* data=m_source.c_str();
  glShaderSource(m_shaderHandle , 1, &data,NULL);
  m_compiled=false;

  if (m_debugState == true)
  {
    printInfoLog(m_shaderHandle);
  }
}

void Shader::loadFromString(const std::string &_string ) noexcept
{
  // see if we already have some source attached
  if(m_source.size()!=0)
  {
    std::cerr<<"deleting existing source code\n";
    m_source.clear();
  }

  // we need this for the check in the compile bit
  m_source=_string;
  const char* data=m_source.c_str();

  glShaderSource(m_shaderHandle , 1, &data,NULL);
  m_compiled=false;
 if (m_debugState == true)
  {
    printInfoLog(m_shaderHandle);
  }
}

} // end ngl namespace
