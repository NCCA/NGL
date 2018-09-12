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
#include "CheckerShaders.h"
#include "rapidjson/document.h"


//----------------------------------------------------------------------------------------------------------------------
/// @file ShaderLib.cpp
/// @brief implementation files for ShaderLibrary and manager class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::loadShader(const std::string_view &_shaderName, const std::string_view &_vert, const std::string_view &_frag, const std::string_view &_geo, const bool _exitOnError ) noexcept
{
  bool loaded=false;
  // must add code to do this next version
  createShaderProgram(_shaderName,_exitOnError);
  // we can't concatinate a view so make a new one.
  std::string shaderName=_shaderName.data();
  attachShader(shaderName+"Vertex",ShaderType::VERTEX,_exitOnError);
  attachShader(shaderName+"Fragment",ShaderType::FRAGMENT,_exitOnError);
  loadShaderSource(shaderName+"Vertex",_vert);
  loadShaderSource(shaderName+"Fragment",_frag);

  if ( (loaded=compileShader(shaderName+"Vertex")) )
    return loaded;
  if ( (loaded=compileShader(shaderName+"Fragment")) )
    return loaded;

  attachShaderToProgram(shaderName,shaderName+"Vertex");
  attachShaderToProgram(shaderName,shaderName+"Fragment");
  if( _geo !="")
  {
    attachShader(shaderName+"Geo",ShaderType::GEOMETRY);
    loadShaderSource(shaderName+"Geo",_geo);
    compileShader(shaderName+"Geo");
    attachShaderToProgram(shaderName,shaderName+"Geo");
  }

  loaded=linkProgramObject(_shaderName);
  autoRegisterUniforms(_shaderName);
  return loaded;
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
GLint ShaderLib::getAttribLocation( const std::string_view &_shaderName,   const std::string_view &_paramName   ) noexcept
{

  GLint attrib=0;

  // get an iterator to the shaders
  auto shader=m_shaderPrograms.find(_shaderName.data());
  // make sure we have a valid shader
  if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    attrib=glGetAttribLocation(shader->second->getID(),_paramName.data());
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
 loadCherckerShaders();
 m_debugState=true;
}
//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getShaderID(const std::string_view &_shaderName) noexcept
{
  GLuint value = 0;
  auto shader=m_shaders.find(_shaderName.data());
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

ngl::Shader* ShaderLib::getShader(const std::string_view &_shaderName) noexcept
{
  ngl::Shader* shaderPointer;
  auto shader=m_shaders.find(_shaderName.data());
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
void ShaderLib::attachShader(const std::string_view &_name, ShaderType _type , bool _errorOnExit) noexcept
{
  m_shaders[_name.data()]= new Shader(_name,_type,_errorOnExit);
  if(m_debugState==true)
    std::cout<<"just attached "<<_name<<" "<<m_shaders[_name.data()]->getShaderHandle()<<'\n';
}

//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::compileShader(const std::string_view &_name  ) noexcept
{
  // get an iterator to the shaders
  auto shader=m_shaders.find(_name.data());
  // make sure we have a valid shader
  if(shader!=m_shaders.end())
  {
    // grab the pointer to the shader and call compile
    return shader->second->compile();
  }
  else
  {
    std::cerr<<"Warning shader not know in compile "<<_name.data()<<'\n';
    return false;
  }

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::createShaderProgram(const std::string_view &_name , bool _exitOnError ) noexcept
{
  if(m_debugState)
    std::cerr<<"creating empty ShaderProgram "<<_name.data()<<'\n';
 m_shaderPrograms[_name.data()]= new ShaderProgram(_name,_exitOnError);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShaderToProgram(const std::string_view &_program, const std::string_view &_shader   ) noexcept
{

  // get an iterator to the shader and program
  auto shader=m_shaders.find(_shader.data());
  auto program=m_shaderPrograms.find(_program.data());

  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() && program !=m_shaderPrograms.end())
  {
    // now attach the shader to the program
    program->second->attachShader(shader->second);
    // now increment the shader ref count so we know if how many references
    shader->second->incrementRefCount();

    if (m_debugState == true)
    {
      std::cerr<<_shader.data()<<" attached to program "<<_program.data()<<'\n';
    }
  }
  else {std::cerr<<"Warning cant attach "<<_shader.data() <<" to "<<_program.data()<<'\n';}
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSource(std::string_view _shaderName,	std::string_view _sourceFile ) noexcept
{
  auto shader=m_shaders.find(_shaderName.data());
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->load(_sourceFile);
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.data();}

}


ShaderType ShaderLib::getShaderType(const std::string_view &type) noexcept
{
  // convert to low for test
  std::string tlower=type.data();
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


bool ShaderLib::loadFromJson(const std::string_view &_fname)  noexcept
{
  namespace rj=rapidjson;
  std::ifstream file;
  file.open(_fname.data(), std::ios::in);
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
    std::cerr<<"Parse Error for file "<<_fname<<'\n';
    return false;

  }

  if(!doc.HasMember("ShaderProgram"))
  {
    std::cerr<<"This does not seem to be a valid shader json file\n";
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
    if(progName ==nullptr || strlen(progName)==0 )
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
          std::cout<<"attempting to load "<<paths[p].GetString()<<'\n';
        }
        if (source.fail())
        {
            std::cerr<<"error opening shader file\n";
            exit(EXIT_FAILURE);
        }
        std::unique_ptr<std::string> f( new std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>()));
        if(debug)
        {
          std::cout<<"loaded data string \n"<< const_cast<char *>(f->c_str())<<'\n';
        }
        source.close();
        shaderSource+=*f;
        shaderSource+='\n';
      }
      loadShaderSourceFromString(name,shaderSource);
      if(debug)
      {
        std::cout<<"********* Final Shader String ***************\n";
        std::cout<<shaderSource<<'\n';
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
void ShaderLib::loadShaderSourceFromString(const std::string_view &_shaderName, const std::string_view &_string ) noexcept
{
  auto shader=m_shaders.find(_shaderName.data());
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->loadFromString(_string.data());
    //std::cout<<*_string<<'\n';
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.data();}

}


//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::linkProgramObject(const std::string_view &_name	) noexcept
{
  bool linked=false;
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    std::cerr<<"Linking "<<_name.data()<<'\n';
    linked=program->second->link();
  }
  else {std::cerr<<"Warning Program not known in link "<<_name.data();}
  return linked;

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::use(const std::string_view &_name  )  noexcept
{
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    //std::cerr<<"Shader manager Use\n";
    m_currentShader=_name.data();
    program->second->use();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.data()<<'\n';
    m_currentShader="NULL";
    glUseProgram(0);
  }

}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getProgramID(const std::string_view &_name ) noexcept
{
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    return program->second->getID();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.data();
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::autoRegisterUniforms(const std::string_view &_shaderName   ) noexcept
{
  auto program=m_shaderPrograms.find(_shaderName.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
     program->second->autoRegisterUniforms();
     program->second->autoRegisterUniformBlocks();
  }
  else
  {
    std::cerr<<"Warning Program not know in registerUniform "<<_shaderName.data()<<'\n';
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindAttribute(const std::string_view &_programName, GLuint _index, const std::string_view &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindAttribute(_index,_attribName);
  }
  else {std::cerr<<"Warning Program not know in bindAttribute "<<_programName.data();}
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindFragDataLocation(const std::string_view &_programName, GLuint _index, const std::string_view &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindFragDataLocation(_index,_attribName);
  }
  else {std::cerr<<"Warning Program not know in bindAttribute "<<_programName.data();}
}


////----------------------------------------------------------------------------------------------------------------------
//void ceckGLError( const std::string_view  &_file, const int _line  ) noexcept
//{

//  NGLCheckGLError(_file,_line);

//}


//----------------------------------------------------------------------------------------------------------------------
ShaderProgram * ShaderLib::operator[](const std::string_view &_name  ) noexcept
{
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    m_currentShader=_name;
    return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_name.data();
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


GLuint ShaderLib::getUniformBlockIndex( const std::string_view &_uniformBlockName  ) const  noexcept
{

  GLuint id=0;

  // get an iterator to the shaders
  auto shader=m_shaderPrograms.find(m_currentShader.data());
  // make sure we have a valid shader
  if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    id=shader->second->getUniformBlockIndex(_uniformBlockName.data());
  }
  else
  {
    std::cerr <<"Can't find id for uniform block " << _uniformBlockName.data() <<'\n';
  }

  return id;
}

void ShaderLib::setUniformBuffer(const std::string_view &_uniformBlockName, size_t _size, void *_data)
{
  (*this)[m_currentShader]->setUniformBuffer(_uniformBlockName,_size,_data);

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


void ShaderLib::loadCherckerShaders() noexcept
{

  createShaderProgram("nglCheckerShader");

  attachShader("nglCheckerVertex",ShaderType::VERTEX);
  attachShader("nglCheckerFragment",ShaderType::FRAGMENT);

  loadShaderSourceFromString("nglCheckerVertex",CheckerVertexShader);
  loadShaderSourceFromString("nglCheckerFragment",CheckerFragmentShader);

  compileShader("nglCheckerVertex");
  compileShader("nglCheckerFragment");


  attachShaderToProgram("nglCheckerShader","nglCheckerVertex");
  attachShaderToProgram("nglCheckerShader","nglCheckerFragment");

  bindAttribute("nglCheckerShader",0,"inVert");
  bindAttribute("nglCheckerShader",2,"inNormal");

  linkProgramObject("nglCheckerShader");
  use("nglCheckerShader");
  autoRegisterUniforms("nglCheckerShader");
  use("NULL");
}


void ShaderLib::printRegisteredUniforms(const std::string_view &_shader) const  noexcept
{
  auto program=m_shaderPrograms.find(_shader.data());
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
    std::cerr<<"Printing Properties for ShaderProgram "<<m_currentShader<<'\n';
    std::cerr<<"_______________________________________________________________________________________________________________________\n";
    program->second->printProperties();
    std::cerr<<"_______________________________________________________________________________________________________________________\n";
  }
  else {std::cerr<<"Warning no currently active shader to print properties for "<<m_currentShader<<'\n';}




}


void ShaderLib::setUniform(const std::string_view &_paramName,Real _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform1f(_paramName.data(),_v0);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Real _v0,Real _v1) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Real _v0,Real _v1,Real _v2) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0,_v1,_v2);

}

void ShaderLib::setUniform(const std::string_view &_paramName,Real _v0,Real _v1,Real _v2,Real _v3) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string_view &_paramName,GLint _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform1i(_paramName.data(),_v0);
}

void ShaderLib::setUniform(const std::string_view &_paramName,GLint _v0,GLint _v1) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2i(_paramName.data(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string_view &_paramName,GLint _v0,GLint _v1,GLint _v2) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3i(_paramName.data(),_v0,_v1,_v2);
}

void ShaderLib::setUniform(const std::string_view &_paramName,GLint _v0,GLint _v1,GLint _v2,GLint _v3) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4i(_paramName.data(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Vec2 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0.m_x,_v0.m_y);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Vec3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0.m_x,_v0.m_y,_v0.m_z);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Vec4 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0.m_x,_v0.m_y,_v0.m_z,_v0.m_w);
}

void ShaderLib::setUniform(const std::string_view &_paramName,Mat3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,GL_FALSE,_v0.openGL());

}

#ifdef USEGLM
void ShaderLib::setUniform(const std::string_view &_paramName,glm::vec2 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0.x,_v0.y);
}

void ShaderLib::setUniform(const std::string_view &_paramName,glm::vec3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0.x,_v0.y,_v0.z);
}

void ShaderLib::setUniform(const std::string_view &_paramName,glm::vec4 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0.x,_v0.y,_v0.z,_v0.w);
}

void ShaderLib::setUniform(const std::string_view &_paramName,glm::mat3 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,GL_FALSE,&_v0[0][0]);

}

#endif

void ShaderLib::setUniformMatrix4fv(const std::string_view &_paramName,const GLfloat *_value,MatrixTranspose _transpose) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix4fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}
void ShaderLib::setUniformMatrix3fv(const std::string_view &_paramName, const GLfloat *_value, MatrixTranspose _transpose) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}

void ShaderLib::setUniformMatrix2fv(const std::string_view &_paramName, const GLfloat *_value, MatrixTranspose _transpose) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix2fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}



void ShaderLib::setUniform(const std::string_view &_paramName,Mat4 _v0) noexcept
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix4fv(_paramName.data(),1,GL_FALSE,_v0.openGL());
}





} // end ngl namespace



//----------------------------------------------------------------------------------------------------------------------

