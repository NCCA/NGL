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
ShaderProgram::ShaderProgram(std::string _name)
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
  std::cerr<<"removing shader program "<< m_programName<<"\n";
  glDeleteProgram(m_programID);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::use()
{
 // std::cerr<<"Using shader "<<m_programName<<" id "<<m_programID<<"\n";
  glUseProgram(m_programID);
  //NGLCheckGLError(__FILE__,__LINE__);
  m_active=true;
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::unbind()
{
  m_active=false;
  glUseProgram(0);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::attachShader(Shader *_shader)
{
  m_shaders.push_back(_shader);
  glAttachShader(m_programID,_shader->getShaderHandle());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::bindAttribute(GLuint _index, const std::string &_attribName)
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

void ShaderProgram::bindFragDataLocation(GLuint _index, const std::string &_attribName)
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
void ShaderProgram::link()
{
  glLinkProgram(m_programID);
if(m_debugState==true)
  {
    std::cerr <<"linking Shader "<< m_programName.c_str()<<"\n";
  }
  GLint infologLength = 0;

  glGetProgramiv(m_programID,GL_INFO_LOG_LENGTH,&infologLength);
  //std::cerr<<"Link Log Length "<<infologLength<<"\n";

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
}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderProgram::getUniformLocation(const char* _name   ) const
{
  GLint loc = glGetUniformLocation( m_programID ,_name);
  if (loc == -1)
  {
    std::cerr<<"Uniform \""<<_name<<"\" not found in Program \""<<m_programName<<"\"\n";
  }
  return loc;
}

void ShaderProgram::printProperties() const
{
  printActiveUniforms();
  std::cerr<<"_______________________________________________________________________________________________________________________\n";
  printActiveAttributes();
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::printActiveUniforms() const
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

void ShaderProgram::printActiveAttributes() const
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
void ShaderProgram::setUniform1f( const char* _varname,  float _v0  ) const
{
  glUniform1f(getUniformLocation(_varname),_v0);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform1f( const std::string &_varname, float _v0    ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform1f(uniform->second,_v0);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2f(const char* _varname, float _v0, float _v1 ) const
{
  glUniform2f(getUniformLocation(_varname),_v0,_v1);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform2f(const std::string &_varname, float _v0, float _v1 ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform2f(uniform->second,_v0,_v1);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3f(const char* _varname, float _v0,  float _v1, float _v2  ) const
{
  glUniform3f(getUniformLocation(_varname),_v0,_v1,_v2);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform3f( const std::string &_varname, float _v0, float _v1, float _v2  ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform3f(uniform->second,_v0,_v1,_v2);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4f( const char* _varname, float _v0,float _v1,  float _v2, float _v3 ) const
{

  glUniform4f(getUniformLocation(_varname),_v0,_v1,_v2,_v3);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform4f( const std::string &_varname, float _v0, float _v1,  float _v2, float _v3  ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform4f(uniform->second,_v0,_v1,_v2,_v3);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1fv(const char* _varname,  size_t _count,  const float* _value ) const
{
  glUniform1fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2fv(const char* _varname,  size_t _count,  const float* _value ) const
{
  glUniform2fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3fv( const char* _varname, size_t _count, const float* _value  ) const
{
  glUniform3fv(getUniformLocation(_varname),_count,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4fv(const char* _varname,size_t _count, const float* _value  ) const
{
  glUniform4fv(getUniformLocation(_varname),_count,_value);

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1i( const char* _varname, GLint _v0 ) const
{
  glUniform1i(getUniformLocation(_varname),_v0);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform1i( const std::string &_varname, int _v0  ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform1i(uniform->second,_v0);
  }

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform2i( const std::string &_varname, int _v0, int _v1   ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform2i(uniform->second,_v0,_v1);
  }

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform3i(const std::string &_varname,  int _v0,   int _v1,  int _v2   ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform3i(uniform->second,_v0,_v1,_v2);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniform4i( const std::string &_varname,  int _v0,   int _v1, int _v2,  int _v3  ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniform4i(uniform->second,_v0,_v1,_v2,_v3);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2i( const char* _varname,  GLint _v0,  GLint _v1 ) const
{
  glUniform2i(getUniformLocation(_varname),_v0,_v1);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3i( const char* _varname, GLint _v0,  GLint _v1,   GLint _v2  ) const
{
  glUniform3i(getUniformLocation(_varname),_v0,_v1,_v2);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4i( const char* _varname,   GLint _v0,GLint _v1,   GLint _v2, GLint _v3  ) const
{
  glUniform4i(getUniformLocation(_varname),_v0,_v1,_v2,_v3);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform1iv( const char* _varname, size_t _count,  const GLint* _value ) const
{
  glUniform1iv(getUniformLocation(_varname),_count,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform2iv( const char* _varname, size_t _count, const GLint* _value   ) const
{
  glUniform2iv(getUniformLocation(_varname),_count,_value);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform3iv( const char* _varname,size_t _count, const GLint* _value ) const
{
  glUniform3iv(getUniformLocation(_varname),_count,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniform4iv(const char* _varname, size_t _count,const GLint* _value  ) const
{
  glUniform4iv(getUniformLocation(_varname),_count,_value);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2fv(const char* _varname,size_t _count, bool _transpose,const float* _value ) const
{
  glUniformMatrix2fv(getUniformLocation(_varname),_count,_transpose,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3fv( const char* _varname, size_t _count,bool _transpose, const float* _value ) const
{
  glUniformMatrix3fv(getUniformLocation(_varname),_count,_transpose,_value);

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniformMatrix3fv( const std::string &_varname,size_t _count, bool _transpose,const float* _value) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniformMatrix3fv(uniform->second,_count,_transpose,_value);
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4fv(const char* _varname, size_t _count, bool _transpose, const float* _value ) const
{
  glUniformMatrix4fv(getUniformLocation(_varname),_count,_transpose,_value);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setRegisteredUniformMatrix4fv(const std::string &_varname, size_t _count, bool _transpose,  const float* _value ) const
{
  std::map <std::string, GLuint >::const_iterator uniform=m_registeredUniforms.find(_varname);
  // make sure we have a valid shader
  if(uniform!=m_registeredUniforms.end())
  {
    glUniformMatrix4fv(uniform->second,_count,_transpose,_value);
  }

}
//----------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2x3fv(const char* _varname,size_t _count,bool _transpose, const float* _value  ) const
{
  glUniformMatrix2x3fv(getUniformLocation(_varname),_count,_transpose,_value);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix2x4fv(const char* _varname, size_t _count,bool _transpose,const float* _value) const
{
  glUniformMatrix2x4fv(getUniformLocation(_varname),_count,_transpose,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3x2fv(const char* _varname,size_t _count,bool _transpose,const float* _value ) const
{
  glUniformMatrix3x2fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix3x4fv(const char* _varname,size_t _count,bool _transpose, const float* _value) const
{
  glUniformMatrix3x4fv(getUniformLocation(_varname),_count,_transpose,_value);

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4x2fv(const char* _varname,size_t _count,bool _transpose,const float* _value ) const
{
  glUniformMatrix4x2fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::setUniformMatrix4x3fv(const char* _varname,size_t _count,bool _transpose,const float* _value) const
{
  glUniformMatrix4x3fv(getUniformLocation(_varname),_count,_transpose,_value);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::getUniformfv( const char* _varname,float* o_values ) const
{
  glGetUniformfv(m_programID, getUniformLocation(_varname),o_values);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::getUniformiv(const char* _varname,int *o_values ) const
{
  glGetUniformiv(m_programID,getUniformLocation(_varname),o_values);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::enableAttribArray( const char* _name) const
{

  std::map <std::string, GLuint >::const_iterator index=m_attribs.find(_name);


  if(index!=m_attribs.end())
  {
    std::cerr<<"Enable attrib "<<index->second<<"\n";
    glEnableVertexAttribArray( index->second  );
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderProgram::disableAttribArray(const char* _name) const
{
  glDisableVertexAttribArray(getUniformLocation(_name));

}



void ShaderProgram::bindFragDataLocation(GLuint _colourNumber, const char *_name)
{
    glBindFragDataLocation(m_programID , _colourNumber, _name);
}

GLuint ShaderProgram::getUniformBlockIndex( const std::string &_uniformBlockName )const
{
  return glGetUniformBlockIndex(m_programID,_uniformBlockName.c_str());
}


void ShaderProgram::registerUniform(std::string _uniformName )
{

  m_registeredUniforms[_uniformName]=getUniformLocation(_uniformName.c_str());

}

bool ShaderProgram::parseHashDefine(const std::string &_s,std::string &o_name,int &o_value ) const
{
  // typedef our tokenizer for speed and clarity
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  // these are the separators we are looking for (not droids ;-)
  boost::char_separator<char> sep(" \t\r\n");
  // generate our tokens based on the seperators above
  tokenizer tokens(_s, sep);
  // now we will copy them into a std::vector to process
  std::vector <std::string> data;
  // we do this as the tokenizer just does that so we can't get size etc
  data.assign(tokens.begin(),tokens.end());
  // we are parsing #define name value so check we have this format
  // we should as the glsl compiler will fail if we don't but best to be sure
  if(data.size() !=3)
  {
    return false;
  }
  else
  {
    //            data [0]     [1]   [2]
    // we are parsing #define name value
    o_name=data[1];
    o_value=boost::lexical_cast<int> (data[2]);
    // all was good so return true
    return true;
  }
}

// the uniform can be in two formats either
// uniform type name
// or
// uniform type name[ value ]
// where [ value ] can be either
// [ number(s)]
// [ a define ]
// we can't process these ones so will just put error message not harmful tho

void ShaderProgram::parseUniform(const std::string &_s, const std::map <std::string,int> &_defines  )
{
 typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

 // first lets see what we need to parse
 if(_s.find("[") ==std::string::npos)
 {
   boost::char_separator<char> sep(" \t\r\n;");
   // generate our tokens based on the seperators above
   tokenizer tokens(_s, sep);
   // now we will copy them into a std::vector to process
   std::vector <std::string> data;
   // we do this as the tokenizer just does that so we can't get size etc
   data.assign(tokens.begin(),tokens.end());
   // uniform type name
   // we should as the glsl compiler will fail if we don't but best to be sure
   if(data.size() >=3)
   {
     registerUniform(data[2]);
   }
 }
 else
 {
   boost::char_separator<char> sep(" []\t\r\n;");
   // generate our tokens based on the seperators above
   tokenizer tokens(_s, sep);
   // now we will copy them into a std::vector to process
   std::vector <std::string> data;
   // we do this as the tokenizer just does that so we can't get size etc
   data.assign(tokens.begin(),tokens.end());
   // uniform type name
   // we should as the glsl compiler will fail if we don't but best to be sure
   if(data.size() >=3)
   {
     // so in this case data[3] is either a number or a constant
     int arraySize=0;
     // so we try and convert it if it's not a number
     try
     {
       arraySize=boost::lexical_cast<int> (data[3]);
     }
     // catch and lookup in the uniform array
     catch(boost::bad_lexical_cast)
     {
       std::map <std::string, int >::const_iterator def=_defines.find(data[3]);
       if(def !=_defines.end())
       {
         arraySize=def->second;
       }
     } // end catch
    // now loop and register each of the uniforms
     for(int i=0; i<arraySize; ++i)
     {
       // convert our uniform and register
       std::string uniform=boost::str(boost::format("%s[%d]") %data[2] %i);
       registerUniform(uniform);
     }
   }

 }
}


void ShaderProgram::autoRegisterUniforms()
{

  unsigned int size=m_shaders.size();
  const std::string *source;
  std::vector<std::string> lines;

  boost::char_separator<char> sep(" \t\r\n");
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

  for(unsigned int i=0; i<size; ++i)
  {
    /// first grab all of the shader source for this program
    source=m_shaders[i]->getShaderSource();
    // and split on new lines
    boost::split(lines, *source, boost::is_any_of("\n\r"));

    // now we loop for the strings and tokenize looking for the uniform keyword
    // or the #define keyword
    std::vector<std::string>::iterator start=lines.begin();
    std::vector<std::string>::iterator end=lines.end();
    std::map<std::string,int> defines;

    while(start!=end)
    {
      // have we got #define
      if(start->find("#define") !=std::string::npos)
      {
        int value;
        std::string define;
        if( parseHashDefine(*start,define,value) )
         {
          defines[define]=value;
        }
      }
      // see if we have uniform in the string
      else if (start->find("uniform") !=std::string::npos)
      {
        parseUniform(*start,defines);
      }
      // got to the next line
      ++start;
     }
  }
}

void ShaderProgram::printRegisteredUniforms() const
{
  std::map<std::string,GLuint>::const_iterator start=m_registeredUniforms.begin();
  std::map<std::string,GLuint>::const_iterator end=m_registeredUniforms.end();

  std::cout<<"Registered Uniforms for shader "<< m_programName<<"\n";

  while(start !=end)
  {
    std::cout<<"Uniform "<<start->first<<"\n";
    ++start;
  }
}



} // end ngl namespace
