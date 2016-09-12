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
#include "fmt/format.h"

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
  #ifndef USINGIOS_
    glBindFragDataLocation(m_programID,_index,_attribName.c_str());
  #endif
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
GLint ShaderProgram::getUniformLocation(const char* _name   ) const noexcept
{
  // nasty C lib uses -1 return value for error
  GLint loc = glGetUniformLocation( m_programID ,_name);
  if (loc == -1)
  {
    std::cerr<<"Uniform \""<<_name<<"\" not found in Program \""<<m_programName<<"\"\n";
  }
  // so we cast to correct value when returning!
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
#ifndef USINGIOS_
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
       glGetActiveUniformName(m_programID, static_cast<GLuint>(i), 256, &l, name);
       std::cerr << "Uniform: "<<name<<"\n";
    }
#endif

}

void ShaderProgram::printActiveAttributes() const noexcept
{
  GLint nAttribs;

  glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
  GLint size; GLenum type;
  GLsizei l;
  char name[256];
  for (GLint i=0; i < nAttribs; ++i)
  {
    glGetActiveAttrib(m_programID, static_cast<GLuint>(i), 256, &l, &size, &type, name);
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
    glUniform1f(uniform->second.loc,_v0);
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
    glUniform2f(uniform->second.loc,_v0,_v1);
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
    glUniform3f(uniform->second.loc,_v0,_v1,_v2);
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
    glUniform4f(uniform->second.loc,_v0,_v1,_v2,_v3);
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
    glUniform1i(uniform->second.loc,_v0);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform2i( const std::string &_varname, int _v0, int _v1   ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform2i(uniform->second.loc,_v0,_v1);
  }

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform3i(const std::string &_varname,  int _v0,   int _v1,  int _v2   ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform3i(uniform->second.loc,_v0,_v1,_v2);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform4i( const std::string &_varname,  int _v0,   int _v1, int _v2,  int _v3  ) const noexcept
{
  auto uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform4i(uniform->second.loc,_v0,_v1,_v2,_v3);
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
    glUniformMatrix3fv(uniform->second.loc,_count,_transpose,_value);
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
    glUniformMatrix4fv(uniform->second.loc,_count,_transpose,_value);
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
  #ifndef USINGIOS_
    glBindFragDataLocation(m_programID , _colourNumber, _name);
  #endif
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
  for (GLint i=0; i<nUniforms; ++i)
  {
    GLenum type = GL_ZERO;
    GLsizei nameLen=0;
    GLint num=0;
    glGetActiveUniform( m_programID, i, sizeof(name)-1, &nameLen, &num, &type, name );
    // two options we either have an array or single value
    // if not array
    if(num == 1)
    {
      data.name=name;
      data.loc=glGetUniformLocation(m_programID,name);
      data.type=type;
      m_registeredUniforms[name]=data;
    }
    else
    {
      std::string uniform(name);
      std::string baseName=uniform.substr(0, uniform.find("["));
      // nvidia returns uniform[0], ATI uniform, best way is to split on [
      for(int i=0; i<num; ++i)
      {
        std::string name=fmt::format("{0}[{1}]", baseName , i) ;

        data.name=name;
        data.loc=glGetUniformLocation(m_programID,name.c_str());
        data.type=type;
        m_registeredUniforms[name]=data;
      }
    }
  }
}

void ShaderProgram::printRegisteredUniforms() const noexcept
{
  const static std::unordered_map<GLenum,const char *> types=
  {
    {GL_FLOAT,"float"},
    {GL_FLOAT_VEC2,"vec2"},
    {GL_FLOAT_VEC3,"vec3"},
    {GL_FLOAT_VEC4,"vec4"},
  #ifndef USINGIOS_
    {GL_DOUBLE,"double"},
    {GL_DOUBLE_VEC2,"dvec2"},
    {GL_DOUBLE_VEC3,"dvec3"},
    {GL_DOUBLE_VEC4,"dvec4"},
  #endif
    {GL_INT,"int"},
    {GL_INT_VEC2,"ivec2"},
    {GL_INT_VEC3,"ivec3"},
    {GL_INT_VEC4,"ivec4"},
    {GL_UNSIGNED_INT,"unsigned int"},
    {GL_UNSIGNED_INT_VEC2,"uvec2"},
    {GL_UNSIGNED_INT_VEC3,"uvec3"},
    {GL_UNSIGNED_INT_VEC4,"uvec4"},
    {GL_BOOL,"bool"},
    {GL_BOOL_VEC2,"bvec2"},
    {GL_BOOL_VEC3,"bvec3"},
    {GL_BOOL_VEC4,"bvec4"},
    {GL_FLOAT_MAT2,"mat2"},
    {GL_FLOAT_MAT3,"mat3"},
    {GL_FLOAT_MAT4,"mat4"},
    {GL_FLOAT_MAT2x3,"mat2x3"},
    {GL_FLOAT_MAT2x4,"mat2x4"},
    {GL_FLOAT_MAT3x2,"mat3x2"},
    {GL_FLOAT_MAT3x4,"mat3x4"},
    {GL_FLOAT_MAT4x2,"mat4x2"},
    {GL_FLOAT_MAT4x3,"mat4x3"},
  #ifndef USINGIOS_
    {GL_DOUBLE_MAT2,"dmat2"},
    {GL_DOUBLE_MAT3,"dmat3"},
    {GL_DOUBLE_MAT4,"dmat4"},
    {GL_DOUBLE_MAT2x3,"dmat2x3"},
    {GL_DOUBLE_MAT2x4,"dmat2x4"},
    {GL_DOUBLE_MAT3x2,"dmat3x2"},
    {GL_DOUBLE_MAT3x4,"dmat3x4"},
    {GL_DOUBLE_MAT4x2,"dmat4x2"},
    {GL_DOUBLE_MAT4x3,"dmat4x3"},
    {GL_SAMPLER_1D,"sampler1D"},
    {GL_SAMPLER_1D_SHADOW,"sampler1DShadow"},
    {GL_SAMPLER_1D_ARRAY,"sampler1DArray"},
    {GL_SAMPLER_1D_ARRAY_SHADOW,"sampler1DArrayShadow"},
    {GL_SAMPLER_2D_MULTISAMPLE,"sampler2DMS"},
    {GL_SAMPLER_2D_MULTISAMPLE_ARRAY,"sampler2DMSArray"},
    {GL_SAMPLER_BUFFER,"samplerBuffer"},
    {GL_SAMPLER_2D_RECT,"sampler2DRect"},
    {GL_SAMPLER_2D_RECT_SHADOW,"sampler2DRectShadow"},
    {GL_INT_SAMPLER_1D,"isampler1D"},
    {GL_INT_SAMPLER_1D_ARRAY,"isampler1DArray"},
    {GL_INT_SAMPLER_2D_MULTISAMPLE,"isampler2DMS"},
    {GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"isampler2DMSArray"},
    {GL_INT_SAMPLER_BUFFER,"isamplerBuffer"},
    {GL_INT_SAMPLER_2D_RECT,"isampler2DRect"},
    {GL_UNSIGNED_INT_SAMPLER_1D,"usampler1D"},
    {GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,"usampler2DArray"},
    {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,"usampler2DMS"},
    {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"usampler2DMSArray"},
    {GL_UNSIGNED_INT_SAMPLER_BUFFER,"usamplerBuffer"},
    {GL_UNSIGNED_INT_SAMPLER_2D_RECT,"usampler2DRect"},
    {GL_IMAGE_1D,"image1D"},
    {GL_IMAGE_2D,"image2D"},
    {GL_IMAGE_3D,"image3D"},
    {GL_IMAGE_2D_RECT,"image2DRect"},
    {GL_IMAGE_CUBE,"imageCube"},
    {GL_IMAGE_BUFFER,"imageBuffer"},
    {GL_IMAGE_1D_ARRAY,"image1DArray"},
    {GL_IMAGE_2D_ARRAY,"image2DArray"},
    {GL_IMAGE_2D_MULTISAMPLE,"image2DMS"},
    {GL_IMAGE_2D_MULTISAMPLE_ARRAY,"image2DMSArray"},
    {GL_INT_IMAGE_1D,"iimage1D"},
    {GL_INT_IMAGE_2D,"iimage2D"},
    {GL_INT_IMAGE_3D,"iimage3D"},
    {GL_INT_IMAGE_2D_RECT,"iimage2DRect"},
    {GL_INT_IMAGE_CUBE,"iimageCube"},
    {GL_INT_IMAGE_BUFFER,"iimageBuffer"},
    {GL_INT_IMAGE_1D_ARRAY,"iimage1DArray"},
    {GL_INT_IMAGE_2D_ARRAY,"iimage2DArray"},
    {GL_INT_IMAGE_2D_MULTISAMPLE,"iimage2DMS"},
    {GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"iimage2DMSArray"},
    {GL_UNSIGNED_INT_IMAGE_1D,"uimage1D"},
    {GL_UNSIGNED_INT_IMAGE_2D,"uimage2D"},
    {GL_UNSIGNED_INT_IMAGE_3D,"uimage3D"},
    {GL_UNSIGNED_INT_IMAGE_2D_RECT,"uimage2DRect"},
    {GL_UNSIGNED_INT_IMAGE_CUBE,"uimageCube"},
    {GL_UNSIGNED_INT_IMAGE_BUFFER,"uimageBuffer"},
    {GL_UNSIGNED_INT_IMAGE_1D_ARRAY,"uimage1DArray"},
    {GL_UNSIGNED_INT_IMAGE_2D_ARRAY,"uimage2DArray"},
    {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,"uimage2DMS"},
    {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"uimage2DMSArray"},
    {GL_UNSIGNED_INT_ATOMIC_COUNTER,"atomic_uint"},

  #endif
    {GL_SAMPLER_2D,"sampler2D"},
    {GL_SAMPLER_3D,"sampler3D"},
    {GL_SAMPLER_CUBE,"samplerCube"},
    {GL_SAMPLER_2D_SHADOW,"sampler2DShadow"},
    {GL_SAMPLER_2D_ARRAY,"sampler2DArray"},
    {GL_SAMPLER_2D_ARRAY_SHADOW,"sampler2DArrayShadow"},
    {GL_SAMPLER_CUBE_SHADOW,"samplerCubeShadow"},
    {GL_INT_SAMPLER_2D,"isampler2D"},
    {GL_INT_SAMPLER_3D,"isampler3D"},
    {GL_INT_SAMPLER_CUBE,"isamplerCube"},
    {GL_INT_SAMPLER_2D_ARRAY,"isampler2DArray"},
    {GL_UNSIGNED_INT_SAMPLER_2D,"usampler2D"},
    {GL_UNSIGNED_INT_SAMPLER_3D,"usampler3D"},
    {GL_UNSIGNED_INT_SAMPLER_CUBE,"usamplerCube"},
    {GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,"usampler2DArray"}
  };
  std::cout<<"Registered Uniforms for shader "<< m_programName<<"\n";
  for(auto d : m_registeredUniforms)
  {
    std::string type;
    auto value=types.find(d.second.type);
    if(value !=types.end())
    {
      type=value->second;
    }
    else
    {
      type="unknown type";
    }
    std::cout<<"Uniform "<<d.first<<"-> "<<" location "<<d.second.loc<<" glsl type "<<type<<"\n";

  }
}


} // end ngl namespace
