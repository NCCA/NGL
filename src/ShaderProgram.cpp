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
//----------------------------------------------------------------------------------------------------------------------
/// @file ShaderProgram.cpp
/// @brief implementation files for ShaderProgram class
//----------------------------------------------------------------------------------------------------------------------

#include "ShaderProgram.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
ShaderProgram::ShaderProgram(std::string _name) noexcept
{
  // we create a special NULL program so the shader manager can return
  // a NULL object.
if (_name !="NULL")
  {
    m_programID = glCreateProgram();
  }
  else
  {
    m_programID=0;
  }
  //std::cerr <<"Created program id is "<<m_programID<<"\n";
  m_debugState=true;
  m_programName=_name;
  m_linked=false;
  m_active=false;
}
ShaderProgram::~ShaderProgram()
{
  std::cerr<<"removing ShaderProgram "<< m_programName<<"\n";
  glDeleteProgram(m_programID);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::use() noexcept
{
 // std::cerr<<"Using shader "<<m_programName<<" id "<<m_programID<<"\n";
  glUseProgram(m_programID);
  //NGLCheckGLError(__FILE__,__LINE__);
  m_active=true;
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::unbind() noexcept
{
  m_active=false;
  glUseProgram(0);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::attachShader(Shader *_shader) noexcept
{
  m_shaders.push_back(_shader);
  glAttachShader(m_programID,_shader->getShaderHandle());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::bindAttribute(GLuint _index, const std::string &_attribName) noexcept
{
  if(m_linked == true)
  {
    std::cerr<<"Warning binding attribute after link\n";
  }
  m_attribs[_attribName]=_index;
  glBindAttribLocation(m_programID,_index,_attribName.c_str());
  //std::cerr<<"bindAttribLoc "<<m_programID<<" index "<<_index<<" name "<<_attribName<<"\n";
  NGLCheckGLError(__FILE__,__LINE__);
}

void ShaderProgram::bindFragDataLocation(GLuint _index, const std::string &_attribName) noexcept
{
  if(m_linked == true)
  {
    std::cerr<<"Warning binding attribute after link\n";
  }
  m_attribs[_attribName]=_index;
  glBindFragDataLocation(m_programID,_index,_attribName.c_str());
  //std::cerr<<"bindAttribLoc "<<m_programID<<" index "<<_index<<" name "<<_attribName<<"\n";
  NGLCheckGLError(__FILE__,__LINE__);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::link() noexcept
{
  glLinkProgram(m_programID);
  if(m_debugState==true)
  {
    std::cerr <<"linking Shader "<< m_programName.c_str()<<"\n";
  }
  GLint infologLength = 0;

  glGetProgramiv(m_programID,GL_INFO_LOG_LENGTH,&infologLength);

  if(infologLength > 0)
  {
    char *infoLog = new char[infologLength];
    GLint charsWritten  = 0;

    glGetProgramInfoLog(m_programID, infologLength, &charsWritten, infoLog);

    std::cerr<<infoLog<<std::endl;
    delete [] infoLog;
    glGetProgramiv(m_programID, GL_LINK_STATUS,&infologLength);
    if( infologLength == GL_FALSE)
    {
      std::cerr<<"Program link failed exiting \n";
      exit(EXIT_FAILURE);
    }
  }

  m_linked=true;
  glUseProgram(m_programID);
  autoRegisterUniforms();

}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderProgram::getUniformLocation(const char* _name   ) const noexcept
{
  GLint loc = glGetUniformLocation( m_programID ,_name);
  if (loc == -1)
  {
    std::cerr<<"Uniform \""<<_name<<"\" not found in Program \""<<m_programName<<"\"\n";
  }
  return loc;
}

void ShaderProgram::printProperties() const noexcept
{
  printActiveUniforms();
  std::cerr<<"_______________________________________________________________________________________________________________________\n";
  printActiveAttributes();
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::printActiveUniforms() const noexcept
{
  if(m_active !=true)
  {
    std::cerr<<"calling printActiveUniforms on unbound shader program\n";
  }
  GLint nUniforms;
  glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &nUniforms);
  char name[256];
  GLsizei l;
  for (GLint i=0; i<nUniforms; ++i)
  {
     glGetActiveUniformName(m_programID, i, 256, &l, name);
     std::cerr << "Uniform: "<<name<<"\n";
  }
}

void ShaderProgram::printActiveAttributes() const noexcept
{
  GLint nAttribs;

  glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
  GLint size; GLenum type;
  GLsizei l;
  char name[256];
  for (int i=0; i < nAttribs; ++i)
  {
    glGetActiveAttrib(m_programID, i, 256, &l, &size, &type, name);
    std::cerr << "Attribute"<<i<<":\""<<name<<"\" Size:"<<size<<" Type:";
    switch(type)
    {
    case GL_FLOAT: std::cerr << "GL_FLOAT\n"; break;
    case GL_FLOAT_VEC2: std::cerr << "GL_FLOAT_VEC2\n"; break;
    case GL_FLOAT_VEC3: std::cerr << "GL_FLOAT_VEC3\n"; break;
    case GL_FLOAT_VEC4: std::cerr << "GL_FLOAT_VEC4\n"; break;
    case GL_FLOAT_MAT2: std::cerr << "GL_FLOAT_MAT2\n"; break;
    case GL_FLOAT_MAT3: std::cerr << "GL_FLOAT_MAT3\n"; break;
    case GL_FLOAT_MAT4: std::cerr << "GL_FLOAT_MAT4\n"; break;
    case GL_FLOAT_MAT2x3: std::cerr << "GL_FLOAT_MAT2x3\n"; break;
    case GL_FLOAT_MAT2x4: std::cerr << "GL_FLOAT_MAT2x4\n"; break;
    case GL_FLOAT_MAT3x2: std::cerr << "GL_FLOAT_MAT3x2\n"; break;
    case GL_FLOAT_MAT3x4: std::cerr << "GL_FLOAT_MAT3x4\n"; break;
    case GL_FLOAT_MAT4x2: std::cerr << "GL_FLOAT_MAT4x2\n"; break;
    case GL_FLOAT_MAT4x3: std::cerr << "GL_FLOAT_MAT4x3\n"; break;
    default: std::cerr << "UNKNOWN\n";
    }
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1f( const char* _varname,  float _v0  ) const noexcept
{
  glUniform1f(getUniformLocation(_varname),_v0);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform1f( const std::string &_varname, float _v0    ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform1f(uniform->second.id,_v0);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2f(const char* _varname, float _v0, float _v1 ) const noexcept
{
  glUniform2f(getUniformLocation(_varname),_v0,_v1);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform2f(const std::string &_varname, float _v0, float _v1 ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform2f(uniform->second.id,_v0,_v1);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3f(const char* _varname, float _v0,  float _v1, float _v2  ) const noexcept
{
  glUniform3f(getUniformLocation(_varname),_v0,_v1,_v2);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform3f( const std::string &_varname, float _v0, float _v1, float _v2  ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform3f(uniform->second.id,_v0,_v1,_v2);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4f( const char* _varname, float _v0,float _v1,  float _v2, float _v3 ) const noexcept
{

  glUniform4f(getUniformLocation(_varname),_v0,_v1,_v2,_v3);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform4f( const std::string &_varname, float _v0, float _v1,  float _v2, float _v3  ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform4f(uniform->second.id,_v0,_v1,_v2,_v3);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1fv(const char* _varname,  size_t _count,  const float* _value ) const noexcept
{
  glUniform1fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2fv(const char* _varname,  size_t _count,  const float* _value ) const noexcept
{
  glUniform2fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3fv( const char* _varname, size_t _count, const float* _value  ) const noexcept
{
  glUniform3fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4fv(const char* _varname,size_t _count, const float* _value  ) const noexcept
{
  glUniform4fv(getUniformLocation(_varname),_count,_value);

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1i( const char* _varname, GLint _v0 ) const noexcept
{
  glUniform1i(getUniformLocation(_varname),_v0);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform1i( const std::string &_varname, int _v0  ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform1i(uniform->second.id,_v0);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform2i( const std::string &_varname, int _v0, int _v1   ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform2i(uniform->second.id,_v0,_v1);
  }

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform3i(const std::string &_varname,  int _v0,   int _v1,  int _v2   ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform3i(uniform->second.id,_v0,_v1,_v2);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform4i( const std::string &_varname,  int _v0,   int _v1, int _v2,  int _v3  ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform4i(uniform->second.id,_v0,_v1,_v2,_v3);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2i( const char* _varname,  GLint _v0,  GLint _v1 ) const noexcept
{
  glUniform2i(getUniformLocation(_varname),_v0,_v1);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3i( const char* _varname, GLint _v0,  GLint _v1,   GLint _v2  ) const noexcept
{
  glUniform3i(getUniformLocation(_varname),_v0,_v1,_v2);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4i( const char* _varname,   GLint _v0,GLint _v1,   GLint _v2, GLint _v3  ) const noexcept
{
  glUniform4i(getUniformLocation(_varname),_v0,_v1,_v2,_v3);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1iv( const char* _varname, size_t _count,  const GLint* _value ) const noexcept
{
  glUniform1iv(getUniformLocation(_varname),_count,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2iv( const char* _varname, size_t _count, const GLint* _value   ) const noexcept
{
  glUniform2iv(getUniformLocation(_varname),_count,_value);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3iv( const char* _varname,size_t _count, const GLint* _value ) const noexcept
{
  glUniform3iv(getUniformLocation(_varname),_count,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4iv(const char* _varname, size_t _count,const GLint* _value  ) const noexcept
{
  glUniform4iv(getUniformLocation(_varname),_count,_value);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2fv(const char* _varname,size_t _count, bool _transpose,const float* _value ) const noexcept
{
  glUniformMatrix2fv(getUniformLocation(_varname),_count,_transpose,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3fv( const char* _varname, size_t _count,bool _transpose, const float* _value ) const noexcept
{
  glUniformMatrix3fv(getUniformLocation(_varname),_count,_transpose,_value);

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniformMatrix3fv( const std::string &_varname,size_t _count, bool _transpose,const float* _value) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniformMatrix3fv(uniform->second.id,_count,_transpose,_value);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4fv(const char* _varname, size_t _count, bool _transpose, const float* _value ) const noexcept
{
  glUniformMatrix4fv(getUniformLocation(_varname),_count,_transpose,_value);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniformMatrix4fv(const std::string &_varname, size_t _count, bool _transpose,  const float* _value ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniformMatrix4fv(uniform->second.id,_count,_transpose,_value);
  }

}
//----------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2x3fv(const char* _varname,size_t _count,bool _transpose, const float* _value  ) const noexcept
{
  glUniformMatrix2x3fv(getUniformLocation(_varname),_count,_transpose,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2x4fv(const char* _varname, size_t _count,bool _transpose,const float* _value) const noexcept
{
  glUniformMatrix2x4fv(getUniformLocation(_varname),_count,_transpose,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3x2fv(const char* _varname,size_t _count,bool _transpose,const float* _value ) const noexcept
{
  glUniformMatrix3x2fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3x4fv(const char* _varname,size_t _count,bool _transpose, const float* _value) const noexcept
{
  glUniformMatrix3x4fv(getUniformLocation(_varname),_count,_transpose,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4x2fv(const char* _varname,size_t _count,bool _transpose,const float* _value ) const noexcept
{
  glUniformMatrix4x2fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4x3fv(const char* _varname,size_t _count,bool _transpose,const float* _value) const noexcept
{
  glUniformMatrix4x3fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::getUniformfv( const char* _varname,float* o_values ) const noexcept
{
  glGetUniformfv(m_programID, getUniformLocation(_varname),o_values);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::getUniformiv(const char* _varname,int *o_values ) const noexcept
{
  glGetUniformiv(m_programID,getUniformLocation(_varname),o_values);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::enableAttribArray( const char* _name) const noexcept
{

  auto index=m_attribs.find(_name);


  if(index!=m_attribs.end())
  {
    std::cerr<<"Enable attrib "<<index->second<<"\n";
    glEnableVertexAttribArray( index->second  );
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::disableAttribArray(const char* _name) const noexcept
{
  glDisableVertexAttribArray(getUniformLocation(_name));

}



void ShaderProgram::bindFragDataLocation(GLuint _colourNumber, const char *_name) noexcept
{
    glBindFragDataLocation(m_programID , _colourNumber, _name);
}

GLuint ShaderProgram::getUniformBlockIndex( const std::string &_uniformBlockName )const noexcept
{
  return glGetUniformBlockIndex(m_programID,_uniformBlockName.c_str());
}


void ShaderProgram::autoRegisterUniforms() noexcept
{


  GLint nUniforms;
  glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &nUniforms);
  // could use this with better OpenGL version
  // glGetProgramInterfaceiv(i, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);


  char name[256];
  uniformData data;
  GLint nameLen,num;
  for (GLint i=0; i<nUniforms; ++i)
  {
    GLenum type = GL_ZERO;
    glGetActiveUniform( m_programID, i, sizeof(name)-1, &nameLen, &num, &type, name );
    data.name=name;
    data.id=glGetUniformLocation(m_programID,name);
    data.type=type;
    m_registeredUniforms[name]=data;
  }

}

void ShaderProgram::printRegisteredUniforms() const noexcept
{
  std::cout<<"Registered Uniforms for shader "<< m_programName<<"\n";
  for(auto d : m_registeredUniforms)
  {
    std::cout<<"Uniform "<<d.first<<" ->"<<d.second.name<<" "<<d.second.id<<" "<<d.second.type<<"\n";

  }
}


} // end ngl namespace
