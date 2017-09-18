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
#include <cstdlib>
#include <fstream>
#include <memory>
#include <algorithm>
#include "ShaderLib.h"
#include "TextShaders.h"
#include "ColourShaders.h"
#include "DiffuseShaders.h"
#include "ToonShaders.h"
#include "rapidjson/document.h"


//----------------------------------------------------------------------------------------------------------------------
/// @file ShaderLib.cpp
/// @brief implementation files for ShaderLibrary and manager class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{













//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShader( const std::string &_shaderName,const std::string &_vert, const std::string &_frag,const std::string &_geo, const bool _exitOnError ) noexcept
{
  // must add code to do this next version
  NGL_UNUSED(_exitOnError);
  createShaderProgram(_shaderName);

  attachShader(_shaderName+"Vertex",ShaderType::VERTEX);
  attachShader(_shaderName+"Fragment",ShaderType::FRAGMENT);
  loadShaderSource(_shaderName+"Vertex",_vert);
  loadShaderSource(_shaderName+"Fragment",_frag);

  compileShader(_shaderName+"Vertex");
  compileShader(_shaderName+"Fragment");
  attachShaderToProgram(_shaderName,_shaderName+"Vertex");
  attachShaderToProgram(_shaderName,_shaderName+"Fragment");
  if( _geo !="")
  {
    attachShader(_shaderName+"Geo",ShaderType::GEOMETRY);
    loadShaderSource(_shaderName+"Geo",_geo);
    compileShader(_shaderName+"Geo");
    attachShaderToProgram(_shaderName,_shaderName+"Geo");
  }

  linkProgramObject(_shaderName);
  autoRegisterUniforms(_shaderName);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::reset() noexcept
{
  std::cerr<<"Closing down shader manager\n";
  for(auto programs : m_shaderPrograms)
    delete programs.second;
  for(auto shader : m_shaders)
    delete shader.second;
}


//----------------------------------------------------------------------------------------------------------------------
GLint ShaderLib::getAttribLocation( const std::string &_shaderName,   const std::string &_paramName   ) noexcept
{

  GLint attrib=0;

  // get an iterator to the shaders
  auto shader=m_shaderPrograms.find(_shaderName);
  // make sure we have a valid shader
  if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    attrib=glGetAttribLocation(shader->second->getID(),_paramName.c_str());
  }
  else
  {
    std::cerr <<"Warning trying to get attrib "<<_paramName<<" from "<<_shaderName<<" but not found\n";
  }

  return attrib;

}



//----------------------------------------------------------------------------------------------------------------------
ShaderLib::ShaderLib()  noexcept
{
//std::cout<<"Shader Manager ctor\n";
 m_debugState=false;
 m_numShaders=0;
 m_nullProgram = new ShaderProgram("NULL");
 m_currentShader="NULL";
 m_shaderPrograms["NULL"]=m_nullProgram;
 loadTextShaders();
 loadColourShaders();
 loadDiffuseShaders();
 loadToonShaders();
 m_debugState=true;
}
//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getShaderID(const std::string &_shaderName) noexcept
{
  GLuint value = 0;
  auto shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    value = shader->second->getShaderHandle();
  }
  else
  {
    std::cout<<"Warning: No shader named "<< _shaderName << " in " << m_currentShader <<" shader program \n";
  }
  return value;
}

ngl::Shader* ShaderLib::getShader(const std::string &_shaderName) noexcept
{
  ngl::Shader* shaderPointer;
  auto shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shaderPointer = shader->second;
  }
  else
  {
    shaderPointer = nullptr;
    std::cout<<"Warning: No shader named "<< _shaderName << " in " << m_currentShader <<" shader program \n";
  }
  return shaderPointer;
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShader(const std::string &_name, ShaderType _type ) noexcept
{
  m_shaders[_name]= new Shader(_name,_type);
  if(m_debugState==true)
    std::cout<<"just attached "<<_name<<" "<<m_shaders[_name]->getShaderHandle()<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::compileShader( const std::string &_name  ) noexcept
{
  // get an iterator to the shaders
  auto shader=m_shaders.find(_name);
  // make sure we have a valid shader
  if(shader!=m_shaders.end())
  {
    // grab the pointer to the shader and call compile
    shader->second->compile();
  }
  else {std::cerr<<"Warning shader not know in compile "<<_name.c_str();}

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::createShaderProgram(const std::string &_name  ) noexcept
{
  if(m_debugState)
    std::cerr<<"creating empty ShaderProgram "<<_name.c_str()<<"\n";
 m_shaderPrograms[_name]= new ShaderProgram(_name);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShaderToProgram( const std::string &_program, const std::string &_shader   ) noexcept
{

  // get an iterator to the shader and program
  auto shader=m_shaders.find(_shader);
  auto program=m_shaderPrograms.find(_program);

  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() && program !=m_shaderPrograms.end())
  {
    // now attach the shader to the program
    program->second->attachShader(shader->second);
    // now increment the shader ref count so we know if how many references
    shader->second->incrementRefCount();

    if (m_debugState == true)
    {
      std::cerr<<_shader.c_str()<<" attached to program "<<_program.c_str()<<"\n";
    }
  }
  else {std::cerr<<"Warning cant attach "<<_shader.c_str() <<" to "<<_program.c_str()<<"\n";}
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSource(std::string _shaderName,	std::string _sourceFile ) noexcept
{
  auto shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->load(_sourceFile);
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.c_str();}

}


ShaderType ShaderLib::getShaderType(const std::string &type) noexcept
{
  // convert to low for test
  std::string tlower=type;
  std::transform(type.begin(), type.end(), tlower.begin(), ::tolower);
  const static std::unordered_map<std::string,ShaderType> stype=
  {
    {"vertex",ShaderType::VERTEX},
    {"fragment",ShaderType::FRAGMENT},
    {"geometry",ShaderType::GEOMETRY},
    {"tesscontrol",ShaderType::TESSCONTROL},
    {"tesseval",ShaderType::TESSEVAL},
    {"compute",ShaderType::COMPUTE}
  };

  auto value=stype.find(tlower);
  if(value !=stype.end())
  {
    return value->second;
  }
  else
  {
    return ShaderType::NONE;
  }
}


bool ShaderLib::loadFromJson(const std::string &_fname)  noexcept
{
  namespace rj=rapidjson;
  std::ifstream file;
  file.open(_fname.c_str(), std::ios::in);
  if (file.fail())
  {
      std::cerr<<"error opening json file\n";
      exit(EXIT_FAILURE);
  }
  std::unique_ptr<std::string> source( new std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()) );
  file.close();
  // we need a mutable string for parsing so copy to a char * buffer

  std::unique_ptr<char []> buffer(new char[source->size()]);
  memcpy(buffer.get(), source->c_str(), source->size());
  // null terminate the string!
  buffer[source->size()]='\0';

  rj::Document doc;

  if (doc.ParseInsitu<0>(buffer.get()).HasParseError())
  {
    std::cerr<<"Parse Error for file "<<_fname<<"\n";
    return false;

  }

  if(!doc.HasMember("ShaderProgram"))
  {
    std::cerr<<"This does not seem to be a valid shader json file"<<std::endl;
    return false;
  }
  std::cout<<"***************Loading Shaders from JSON*****************\n";

  bool debug=false;
  // Now we iterate through the json and gather our data.
  for (rj::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
  {
    if(itr->value.HasMember("debug"))
    {
      debug=itr->value["debug"].GetBool();
    }
    const rj::Value::Ch* progName=itr->value["name"].GetString();
    if(progName ==NULL || strlen(progName)==0 )
    {
      std::cerr<<"ShaderProgram must have a name (or could be 0 length) \n";
      return false;
    }
    createShaderProgram(progName);
    const rj::Value& shaders = itr->value["Shaders"];
    for (rj::SizeType i = 0; i < shaders.Size(); i++)
    {
      const rj::Value &currentShader = shaders[i];
      const rj::Value::Ch *name=currentShader["name"].GetString();
      ShaderType shadertype=getShaderType(currentShader["type"].GetString());

      attachShader(name,shadertype);
      const rj::Value& paths = currentShader["path"];
      std::string shaderSource;
      for (rj::SizeType p = 0; p < paths.Size(); p++)
      {
        // load the shader sources in order.
        std::ifstream source;
        source.open(paths[p].GetString(), std::ios::in);
        if(debug)
        {
          std::cout<<"attempting to load "<<paths[p].GetString()<<"\n";
        }
        if (source.fail())
        {
            std::cerr<<"error opening shader file\n";
            exit(EXIT_FAILURE);
        }
        std::unique_ptr<std::string> f( new std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>()));
        if(debug)
        {
          std::cout<<"loaded data string \n"<< const_cast<char *>(f->c_str())<<"\n";
        }
        source.close();
        shaderSource+=*f;
        shaderSource+="\n";
      }
      loadShaderSourceFromString(name,shaderSource);
      if(debug)
      {
        std::cout<<"********* Final Shader String ***************\n";
        std::cout<<shaderSource<<"\n";
      }
      compileShader(name);
      attachShaderToProgram(progName,name);
    } // end parse shader loop
    if(debug)
    {
      std::cout<<"Linking and registering Uniforms to ShaderLib\n";
    }
    linkProgramObject(progName);
    //autoRegisterUniforms(progName);
    std::cout<<"**********************DONE********************\n";
  }
  return true;
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSourceFromString(const std::string &_shaderName, const std::string &_string ) noexcept
{
  auto shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->loadFromString(_string);
    //std::cout<<*_string<<"\n";
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.c_str();}

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::linkProgramObject(const std::string &_name	) noexcept
{

  auto program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    std::cerr<<"Linking "<<_name.c_str()<<"\n";
    program->second->link();
  }
  else {std::cerr<<"Warning Program not known in link "<<_name.c_str();}

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::use( const std::string &_name  )  noexcept
{
  auto program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    //std::cerr<<"Shader manager Use\n";
    m_currentShader=_name;
    program->second->use();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.c_str()<<"\n";
    m_currentShader="NULL";
    glUseProgram(0);
  }

}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getProgramID(const std::string &_name ) noexcept
{
  auto program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    return program->second->getID();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.c_str();
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::autoRegisterUniforms(const std::string &_shaderName   ) noexcept
{
  auto program=m_shaderPrograms.find(_shaderName);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
     program->second->autoRegisterUniforms();
  }
  else
  {
    std::cerr<<"Warning Program not know in registerUniform "<<_shaderName<<"\n";
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindAttribute(const std::string &_programName, GLuint _index, const std::string &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindAttribute(_index,_attribName);
  }
  else {std::cerr<<"Warning Program not know in bindAttribute "<<_programName.c_str();}
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindFragDataLocation( const std::string &_programName, GLuint _index, const std::string &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindFragDataLocation(_index,_attribName);
  }
  else {std::cerr<<"Warning Program not know in bindAttribute "<<_programName.c_str();}
}


//----------------------------------------------------------------------------------------------------------------------
void ceckGLError( const std::string  &_file, const int _line  ) noexcept
{

  NGLCheckGLError(_file,_line);

}


//----------------------------------------------------------------------------------------------------------------------
ShaderProgram * ShaderLib::operator[](const std::string &_name  ) noexcept
{
  auto program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    m_currentShader=_name;
    return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_name.c_str();
    std::cerr<<"returning a null program and hoping for the best\n";
    return m_nullProgram;
  }
}


//----------------------------------------------------------------------------------------------------------------------
ShaderProgram * ShaderLib::operator[]( const char *_name ) noexcept
{
  auto program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    m_currentShader=_name;

    return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_name;
    std::cerr<<"returning a null program and hoping for the best\n";
    return m_nullProgram;
  }
}


void ShaderLib::useNullProgram() noexcept
{
  m_currentShader="NULL";
  m_nullProgram->use();
}


GLuint ShaderLib::getUniformBlockIndex( const std::string &_uniformBlockName  ) const  noexcept
{

  GLuint id=0;

  // get an iterator to the shaders
  auto shader=m_shaderPrograms.find(m_currentShader);
  // make sure we have a valid shader
  if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    id=shader->second->getUniformBlockIndex(_uniformBlockName);
  }
  else
  {
    std::cerr <<"Can't find id for uniform block " << _uniformBlockName <<"\n";
  }

  return id;
}

void ShaderLib::loadTextShaders() noexcept
{

  createShaderProgram("nglTextShader");

  attachShader("nglTextVertex",ShaderType::VERTEX);
  attachShader("nglTextFragment",ShaderType::FRAGMENT);

  loadShaderSourceFromString("nglTextVertex",textVertexShader);
  loadShaderSourceFromString("nglTextFragment",textFragmentShader);

  compileShader("nglTextVertex");
  compileShader("nglTextFragment");


  attachShaderToProgram("nglTextShader","nglTextVertex");
  attachShaderToProgram("nglTextShader","nglTextFragment");

  bindAttribute("nglTextShader",0,"inVert");
  bindAttribute("nglTextShader",1,"inUV");

  linkProgramObject("nglTextShader");
  use("nglTextShader");
  autoRegisterUniforms("nglTextShader");

  use("NULL");
}


void ShaderLib::loadColourShaders() noexcept
{

  createShaderProgram("nglColourShader");

  attachShader("nglColourVertex",ShaderType::VERTEX);
  attachShader("nglColourFragment",ShaderType::FRAGMENT);

  loadShaderSourceFromString("nglColourVertex",colourVertexShader);
  loadShaderSourceFromString("nglColourFragment",colourFragmentShader);

  compileShader("nglColourVertex");
  compileShader("nglColourFragment");


  attachShaderToProgram("nglColourShader","nglColourVertex");
  attachShaderToProgram("nglColourShader","nglColourFragment");

  bindAttribute("nglColourShader",0,"inVert");

  linkProgramObject("nglColourShader");
  use("nglColourShader");
  autoRegisterUniforms("nglColourShader");
  use("NULL");
}

void ShaderLib::loadDiffuseShaders() noexcept
{

  createShaderProgram("nglDiffuseShader");

  attachShader("nglDiffuseVertex",ShaderType::VERTEX);
  attachShader("nglDiffuseFragment",ShaderType::FRAGMENT);

  loadShaderSourceFromString("nglDiffuseVertex",diffuseVertexShader);
  loadShaderSourceFromString("nglDiffuseFragment",diffuseFragmentShader);

  compileShader("nglDiffuseVertex");
  compileShader("nglDiffuseFragment");


  attachShaderToProgram("nglDiffuseShader","nglDiffuseVertex");
  attachShaderToProgram("nglDiffuseShader","nglDiffuseFragment");

  bindAttribute("nglDiffuseShader",0,"inVert");
  bindAttribute("nglDiffuseShader",2,"inNormal");

  linkProgramObject("nglDiffuseShader");
  use("nglDiffuseShader");
  autoRegisterUniforms("nglDiffuseShader");
  use("NULL");
}


void ShaderLib::loadToonShaders() noexcept
{

  createShaderProgram("nglToonShader");

  attachShader("nglToonVertex",ShaderType::VERTEX);
  attachShader("nglToonFragment",ShaderType::FRAGMENT);

  loadShaderSourceFromString("nglToonVertex",toonVertexShader);
  loadShaderSourceFromString("nglToonFragment",toonFragmentShader);

  compileShader("nglToonVertex");
  compileShader("nglToonFragment");


  attachShaderToProgram("nglToonShader","nglToonVertex");
  attachShaderToProgram("nglToonShader","nglToonFragment");

  bindAttribute("nglToonShader",0,"inVert");
  bindAttribute("nglToonShader",2,"inNormal");

  linkProgramObject("nglToonShader");
  use("nglToonShader");
  autoRegisterUniforms("nglToonShader");
  use("NULL");
}


void ShaderLib::printRegisteredUniforms(const std::string &_shader) const  noexcept
{
  auto program=m_shaderPrograms.find(_shader);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->printRegisteredUniforms();
  }
}

void ShaderLib::printProperties() const noexcept
{

  auto program=m_shaderPrograms.find(m_currentShader);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    std::cerr<<"_______________________________________________________________________________________________________________________\n";
    std::cerr<<"Printing Properties for ShaderProgram "<<m_currentShader<<"\n";
    std::cerr<<"_______________________________________________________________________________________________________________________\n";
    program->second->printProperties();
    std::cerr<<"_______________________________________________________________________________________________________________________\n";
  }
  else {std::cerr<<"Warning no currently active shader to print properties for "<<m_currentShader<<"\n";}




}


void ShaderLib::setUniform(const std::string &_paramName,Real _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform1f(_paramName.c_str(),_v0);
}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.c_str(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.c_str(),_v0,_v1,_v2);

}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2,Real _v3) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.c_str(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform1i(_paramName.c_str(),_v0);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2i(_paramName.c_str(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3i(_paramName.c_str(),_v0,_v1,_v2);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2,GLint _v3) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4i(_paramName.c_str(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string &_paramName,Colour _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.c_str(),_v0.m_r,_v0.m_g,_v0.m_b,_v0.m_a);
}
void ShaderLib::setUniform(const std::string &_paramName,Vec2 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.c_str(),_v0.m_x,_v0.m_y);
}

void ShaderLib::setUniform(const std::string &_paramName,Vec3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.c_str(),_v0.m_x,_v0.m_y,_v0.m_z);
}

void ShaderLib::setUniform(const std::string &_paramName,Vec4 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.c_str(),_v0.m_x,_v0.m_y,_v0.m_z,_v0.m_w);
}

void ShaderLib::setUniform(const std::string &_paramName,Mat3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.c_str(),1,GL_FALSE,_v0.openGL());

}

#ifdef USEGLM
void ShaderLib::setUniform(const std::string &_paramName,glm::vec2 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.c_str(),_v0.x,_v0.y);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::vec3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.c_str(),_v0.x,_v0.y,_v0.z);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::vec4 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.c_str(),_v0.x,_v0.y,_v0.z,_v0.w);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::mat3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.c_str(),1,GL_FALSE,&_v0[0][0]);

}

#endif

void ShaderLib::setUniformMatrix4fv(const std::string &_paramName,const GLfloat *_value,MatrixTranspose _transpose) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix4fv(_paramName.c_str(),1,static_cast<bool>(_transpose),_value);

}
void ShaderLib::setUniformMatrix3fv(const std::string &_paramName, const GLfloat *_value, MatrixTranspose _transpose) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.c_str(),1,static_cast<bool>(_transpose),_value);

}




void ShaderLib::setUniform(const std::string &_paramName,Mat4 _v0) noexcept
{
  (*this)[m_currentShader]->setUniformMatrix4fv(_paramName.c_str(),1,GL_FALSE,_v0.openGL());
}





} // end ngl namespace



//----------------------------------------------------------------------------------------------------------------------

