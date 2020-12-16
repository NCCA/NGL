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
#include "pystring.h"
#include "ShaderLib.h"
#include "TextShaders.h"
#include "ColourShaders.h"
#include "DiffuseShaders.h"
#include "CheckerShaders.h"
#include <rapidjson/document.h>


//----------------------------------------------------------------------------------------------------------------------
/// @file ShaderLib.cpp
/// @brief implementation files for ShaderLibrary and manager class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{


std::shared_ptr<ShaderProgram> ShaderLib::m_nullProgram = std::make_shared<ShaderProgram>("NULL"); //=new ShaderProgram("NULL");

std::unordered_map <std::string,std::shared_ptr<ShaderProgram >> ShaderLib::m_shaderPrograms;

std::unordered_map <std::string,std::shared_ptr<Shader >> ShaderLib::m_shaders;

std::string ShaderLib::m_currentShader="NULL";
bool ShaderLib::m_debugState=true;
unsigned int ShaderLib::m_numShaders=0;
bool ShaderLib::m_defaultShadersLoaded=false;

void ShaderLib::loadDefaultShaders()
{
  std::cerr<<"calling loadDefaultShaders\n";
  if(m_defaultShadersLoaded == true)
    return;
  else
  {
    m_shaderPrograms["NULL"]=m_nullProgram;
    loadTextShaders();
    loadColourShaders();
    loadDiffuseShaders();
    loadCheckerShaders();
    m_defaultShadersLoaded =true;
  }
  
}

//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::loadShader(const std::string &_shaderName, const std::string &_vert, const std::string &_frag, const std::string &_geo, ErrorExit _exitOnError) noexcept
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

  if ( !(loaded=compileShader(shaderName+"Vertex")) )
    return loaded;
  if ( !(loaded=compileShader(shaderName+"Fragment")) )
    return loaded;

  attachShaderToProgram(shaderName,shaderName+"Vertex");
  attachShaderToProgram(shaderName,shaderName+"Fragment");
  attachShader(shaderName+"Geo",ShaderType::GEOMETRY);
  loadShaderSource(shaderName+"Geo",_geo);
  if( !(loaded=compileShader(shaderName+"Geo")))
    return loaded;
  attachShaderToProgram(shaderName,shaderName+"Geo");
  loaded=linkProgramObject(_shaderName);
  autoRegisterUniforms(_shaderName);
  return loaded;
}




bool ShaderLib::loadShader(const std::string &_shaderName, const std::string &_vert, const std::string &_frag,  ErrorExit _exitOnError ) noexcept
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
  if ( !(loaded=compileShader(shaderName+"Vertex")) )
    return loaded;
  if ( !(loaded=compileShader(shaderName+"Fragment")) )
    return loaded;

  attachShaderToProgram(shaderName,shaderName+"Vertex");
  attachShaderToProgram(shaderName,shaderName+"Fragment");
  if( (loaded=linkProgramObject(_shaderName)))
    return loaded;
  autoRegisterUniforms(_shaderName);
  printRegisteredUniforms(_shaderName);
  return loaded;
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::reset() noexcept
{
  m_shaders.clear();
  m_shaderPrograms.clear();
}


//----------------------------------------------------------------------------------------------------------------------
GLint ShaderLib::getAttribLocation( const std::string &_shaderName,   const std::string &_paramName   ) noexcept
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
    msg->addWarning(fmt::format("Warning trying to get attrib {0} from {1} but not found",_paramName.data(),_shaderName.data()));
  }

  return attrib;

}



//----------------------------------------------------------------------------------------------------------------------
ShaderLib::ShaderLib()  noexcept
{
/* m_debugState=false;
 m_numShaders=0;
 m_nullProgram = new ShaderProgram("NULL");
 m_currentShader="NULL";
 m_shaderPrograms["NULL"]=m_nullProgram;
 loadTextShaders();
 loadColourShaders();
 loadDiffuseShaders();
 loadCheckerShaders();
 m_debugState=true;
*/
}
//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getShaderID(const std::string &_shaderName) noexcept
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
    msg->addWarning(fmt::format("Warning: No shader named {0} in {1} shader program",_shaderName.data(),m_currentShader));
  }
  return value;
}

std::shared_ptr<ngl::Shader> ShaderLib::getShader(const std::string &_shaderName) noexcept
{
  std::shared_ptr<ngl::Shader> shaderPointer;
  auto shader=m_shaders.find(_shaderName.data());
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shaderPointer = shader->second;
  }
  else
  {
    shaderPointer = nullptr;
    msg->addWarning(fmt::format("Warning: No shader named {0} in {1} shader program",_shaderName.data(),m_currentShader));
  }
  return shaderPointer;
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShader(const std::string &_name, ShaderType _type , ErrorExit _exitOnError) noexcept
{
  m_shaders[_name.data()]= std::make_shared< Shader>(_name,_type,_exitOnError);
  if(m_debugState==true)
    msg->addMessage(fmt::format("just attached {0} to ngl::ShaderLib",_name.data()));
}

//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::compileShader(const std::string &_name  ) noexcept
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
    msg->addWarning(fmt::format("Warning attempting to compile unknow shader {0} have you added it?",_name.data()));
    return false;
  }

}

bool ShaderLib::editShader(const std::string &_shader,const std::string &_toFind, const std::string &_edit )
{
  bool success=false;
  auto shader=m_shaders.find(_shader.data());
  if(shader!=m_shaders.end() )
    success=shader->second->editShader(_toFind,_edit);
  return success;
}

void ShaderLib::resetEdits(const std::string &_shader)
{
  auto shader=m_shaders.find(_shader.data());
  if(shader!=m_shaders.end() )
    shader->second->resetEdits();
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::createShaderProgram(const std::string &_name , ErrorExit _exitOnError ) noexcept
{
  if(m_debugState)
    msg->addMessage(fmt::format("creating empty ShaderProgram {0}",_name.data()));
 m_shaderPrograms[_name.data()]= std::make_shared< ShaderProgram>(_name,_exitOnError);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShaderToProgram(const std::string &_program, const std::string &_shader   ) noexcept
{

  // get an iterator to the shader and program
  auto shader=m_shaders.find(_shader.data());
  auto program=m_shaderPrograms.find(_program.data());

  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() && program !=m_shaderPrograms.end())
  {
    // now attach the shader to the program
    program->second->attachShader(shader->second.get());
    // now increment the shader ref count so we know if how many references
    shader->second->incrementRefCount();

    if (m_debugState == true)
    {
      msg->addMessage(fmt::format("{0} attached to program",_shader.data()));
    }
  }
  else {msg->addWarning(fmt::format("Warning cant attach {0} to {1} ",_shader.data() ,_program.data()));}
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSource(std::string _shaderName,	std::string _sourceFile ) noexcept
{
  auto shader=m_shaders.find(_shaderName.data());
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->load(_sourceFile);
  }
  else {msg->addWarning(fmt::format("Warning shader not know in loadShaderSource {0}",_shaderName.data()));}

}


ShaderType ShaderLib::getShaderType(const std::string &type) noexcept
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


void ShaderLib::setJsonUniform(const std::string &_name, const std::string &_type, const std::string &_value)
{
  namespace ps=pystring;

  if(m_debugState ==true)
    msg->addMessage(fmt::format("Setting Uniform {0}",_name));

  if(_type =="int")
  {
    setUniform(_name,atoi(_value.c_str()));
  }
  else if(_type == "ivec2")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==2)
    {
      setUniform(_name,atoi(tokens[0].c_str()),atoi(tokens[1].c_str()));

    }
  }

  else if(_type == "ivec3")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==3)
    {
      setUniform(_name,atoi(tokens[0].c_str()),
                       atoi(tokens[1].c_str()),
                       atoi(tokens[2].c_str()));
    }
  }
  else if(_type == "ivec4")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==4)
    {
      setUniform(_name,atoi(tokens[0].c_str()),
                       atoi(tokens[1].c_str()),
                       atoi(tokens[2].c_str()),
                       atoi(tokens[3].c_str()));
    }
  }
  else if(_type=="float")
  {
    setUniform(_name,float(atof(_value.c_str())));

  }
  else if(_type == "vec2")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==2)
    {
      setUniform(_name,float(atof(tokens[0].c_str())),float(atof(tokens[1].c_str())));

    }
  }
  else if(_type == "vec3")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==3)
    {
      setUniform(_name,float(atof(tokens[0].c_str())),
                       float(atof(tokens[1].c_str())),
                       float(atof(tokens[2].c_str())));
    }
  }
  else if(_type == "vec4")
  {
    std::vector<std::string> tokens;
    ps::split(_value,tokens);
    if(tokens.size()==4)
    {
      setUniform(_name,float(atof(tokens[0].c_str())),
                       float(atof(tokens[1].c_str())),
                       float(atof(tokens[2].c_str())),
                       float(atof(tokens[3].c_str())));
    }
  }

}


bool ShaderLib::loadFromJson(const std::string &_fname)  noexcept
{
  namespace ps=pystring;

  namespace rj=rapidjson;
  std::ifstream file;
  file.open(_fname.data(), std::ios::in);
  if (file.fail())
  {
      msg->addError(fmt::format("error opening json file {0}",_fname.data()));
      exit(EXIT_FAILURE);
  }
  std::string jsonsource=std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();
  //msg->addMessage(fmt::format("loaded json\n {}",source));
  // we need a mutable string for parsing so copy to a char * buffer
  std::unique_ptr<char []> buffer(new char[jsonsource.size()]);
  memcpy(buffer.get(), jsonsource.c_str(), jsonsource.size());
  // null terminate the string!
  buffer[jsonsource.size()]='\0';

  rj::Document doc;

  if (doc.ParseInsitu<0>(buffer.get()).HasParseError())
  {
    msg->addError(fmt::format("Parse Error for file {0}",_fname.data()));
    return false;

  }

  if(!doc.HasMember("ShaderProgram"))
  {
    msg->addError(fmt::format("This does not seem to be a valid shader json file"));
    return false;
  }
  if(m_debugState ==true)
  {
    msg->drawLine();
    msg->addMessage(fmt::format("***************Loading Shaders from JSON*****************"));
    msg->drawLine();
  }
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
       msg->addError(fmt::format("ShaderProgram must have a name (or could be 0 length) "));
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
           msg->addMessage(fmt::format("attempting to load {0}",paths[p].GetString()));
        }
        if (source.fail())
        {
             msg->addError(fmt::format("error opening shader file"));
            exit(EXIT_FAILURE);
        }
        std::unique_ptr<std::string> f( new std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>()));
        if(debug)
        {
         msg->addMessage(fmt::format("loaded data string\n {0}",const_cast<char *>(f->c_str())));
        }
        source.close();
        shaderSource+=*f;
        shaderSource+='\n';
        if(currentShader.HasMember("edit"))
        {
          msg->addMessage("found edits\n");

          auto &edits = currentShader["edit"];
          msg->addMessage(fmt::format("found edits {0}",edits.Size()));
          for (rj::SizeType i = 0; i < edits.Size(); i++)
          {
           auto &currentEdit = edits[i];
           msg->addMessage(fmt::format("{0} {1}",currentEdit["search"].GetString(),currentEdit["replace"].GetString()));
          shaderSource=ps::replace(shaderSource,currentEdit["search"].GetString(),currentEdit["replace"].GetString());
          }
        }

      }
      loadShaderSourceFromString(name,shaderSource);
      if(debug)
      {
         msg->addMessage("********* Final Shader String ***************");
         msg->addMessage(shaderSource);
      }

      compileShader(name);
      attachShaderToProgram(progName,name);
      msg->addMessage("Searching for edits\n");


    } // end parse shader loop
    if(debug)
    {
      msg->addMessage("Linking and registering Uniforms to ShaderLib");
    }
    linkProgramObject(progName);
    msg->addMessage(fmt::format("Using shader {0}",progName));
    use(progName);
    // load uniforms and set defaults if present.
    if(itr->value.HasMember("Uniforms"))
    {
      std::cerr<<"have uniforms\n";
      auto &uniforms = itr->value["Uniforms"];

      for (rj::SizeType i = 0; i < uniforms.Size(); i++)
      {
//       std::cerr<<"i "<<i<<'\n';
      // const rj::Value::Ch *name=uniforms["name"].GetString();
       auto &currentUniform = uniforms[i];
       const rj::Value::Ch *name=currentUniform["name"].GetString();
       const rj::Value::Ch *type=currentUniform["type"].GetString();
       const rj::Value::Ch *value=currentUniform["value"].GetString();
       setJsonUniform(name,type,value);
      }
    }

    msg->drawLine();
    msg->addMessage("**********************DONE********************");
    msg->drawLine();

  }
  return true;
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSourceFromString(const std::string &_shaderName, const std::string &_string ) noexcept
{
  auto shader=m_shaders.find(_shaderName.data());
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->loadFromString(_string.data());
  }
  else {msg->addError( fmt::format("shader not know in loadShaderSource {0}",_shaderName.data()));}

}


//----------------------------------------------------------------------------------------------------------------------
bool ShaderLib::linkProgramObject(const std::string &_name	) noexcept
{
  bool linked=false;
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    if(m_debugState==true)
      msg->addMessage(fmt::format("Linking {0}",_name.data()));
    linked=program->second->link();
  }
  else { msg->addError(fmt::format(fmt::format("Program not known in link {0} ",_name.data())));}
  return linked;

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::use(const std::string &_name  )  noexcept
{
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    m_currentShader=_name.data();
    program->second->use();
  }
  else
  {
    msg->addWarning(fmt::format("Warning Program not know in use {0}",_name.data()));
    m_currentShader="NULL";
    glUseProgram(0);
  }

}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getProgramID(const std::string &_name ) noexcept
{
  auto program=m_shaderPrograms.find(_name.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    return program->second->getID();
  }
  else
  {
    msg->addWarning(fmt::format("Warning Program not know in use {0}",_name.data()));
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::autoRegisterUniforms(const std::string &_shaderName   ) noexcept
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
    msg->addWarning(fmt::format("Warning Program not know in registerUniform {0} ",_shaderName.data()));
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindAttribute(const std::string &_programName, GLuint _index, const std::string &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindAttribute(_index,_attribName);
  }
  else {msg->addWarning(fmt::format("Warning Program not know in bindAttribute {0}",_programName.data()));}
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindFragDataLocation(const std::string &_programName, GLuint _index, const std::string &_attribName	) noexcept
{
  auto program=m_shaderPrograms.find(_programName.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->bindFragDataLocation(_index,_attribName);
  }
  else {msg->addWarning(fmt::format("Warning Program not know in bindAttribute {0}",_programName.data()));}
}


////----------------------------------------------------------------------------------------------------------------------
//void ceckGLError( const std::string  &_file, const int _line  ) noexcept
//{

//  NGLCheckGLError(_file,_line);

//}



void ShaderLib::useNullProgram() noexcept
{
  m_currentShader="NULL";
  m_nullProgram->use();
}


GLuint ShaderLib::getUniformBlockIndex( const std::string &_uniformBlockName  )   noexcept
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
    msg->addWarning(fmt::format("Can't find id for uniform block {0}", _uniformBlockName.data()));
  }

  return id;
}

void ShaderLib::setUniformBuffer(const std::string &_uniformBlockName, size_t _size, void *_data)
{
  m_shaderPrograms[m_currentShader]->setUniformBuffer(_uniformBlockName,_size,_data);

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


void ShaderLib::loadCheckerShaders() noexcept
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


void ShaderLib::printRegisteredUniforms(const std::string &_shader)   noexcept
{
  auto program=m_shaderPrograms.find(_shader.data());
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->printRegisteredUniforms();
  }
}

void ShaderLib::printProperties()  noexcept
{

  auto program=m_shaderPrograms.find(m_currentShader);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    msg->addMessage("_______________________________________________________________________________________________________________________",Colours::WHITE,TimeFormat::NONE);
    msg->addMessage(fmt::format("Printing Properties for ShaderProgram {0} ",m_currentShader),Colours::WHITE,TimeFormat::NONE);
    msg->addMessage("_______________________________________________________________________________________________________________________",Colours::WHITE,TimeFormat::NONE);
    program->second->printProperties();
    msg->addMessage("_______________________________________________________________________________________________________________________",Colours::WHITE,TimeFormat::NONE);
  }
  else {msg->addWarning(fmt::format("Warning no currently active shader to print properties for {0} ",m_currentShader));}




}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform1f(_paramName.data(),_v0);
}

void ShaderLib::getUniform(const std::string &_paramName, Real &o_v0)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniform1f(_paramName.data(),o_v0);
}

void ShaderLib::getUniform(const std::string &_paramName, Real &o_v0, Real &o_v1)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniform2f(_paramName.data(),o_v0,o_v1);
}

void ShaderLib::getUniform(const std::string &_paramName, ngl::Vec2 &o_v)  noexcept
{
  float x,y;
 m_shaderPrograms[m_currentShader]->getRegisteredUniform2f(_paramName.data(),x,y);
  o_v.set(x,y);
}



void ShaderLib::getUniform(const std::string &_paramName, Real &o_v0, Real &o_v1, Real &o_v2)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniform3f(_paramName.data(),o_v0,o_v1,o_v2);
}

void ShaderLib::getUniform(const std::string &_paramName, ngl::Vec3 &o_v)  noexcept
{
  float x,y,z;
 m_shaderPrograms[m_currentShader]->getRegisteredUniform3f(_paramName.data(),x,y,z);
  o_v.set(x,y,z);
}


void ShaderLib::getUniform(const std::string &_paramName, Real &o_v0, Real &o_v1, Real &o_v2, Real &o_v3)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniform4f(_paramName.data(),o_v0,o_v1,o_v2,o_v3);
}

void ShaderLib::getUniform(const std::string &_paramName, ngl::Vec4 &o_v)  noexcept
{
  float x,y,z,w;
 m_shaderPrograms[m_currentShader]->getRegisteredUniform4f(_paramName.data(),x,y,z,w);
  o_v.set(x,y,z,w);
}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0,_v1,_v2);

}

void ShaderLib::setUniform(const std::string &_paramName,Real _v0,Real _v1,Real _v2,Real _v3) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform1i(_paramName.data(),_v0);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform2i(_paramName.data(),_v0,_v1);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform3i(_paramName.data(),_v0,_v1,_v2);
}

void ShaderLib::setUniform(const std::string &_paramName,GLint _v0,GLint _v1,GLint _v2,GLint _v3) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform4i(_paramName.data(),_v0,_v1,_v2,_v3);
}

void ShaderLib::setUniform(const std::string &_paramName,Vec2 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0.m_x,_v0.m_y);
}

void ShaderLib::setUniform(const std::string &_paramName,Vec3 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0.m_x,_v0.m_y,_v0.m_z);
}

void ShaderLib::setUniform(const std::string &_paramName,Vec4 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0.m_x,_v0.m_y,_v0.m_z,_v0.m_w);
}

void ShaderLib::setUniform(const std::string &_paramName,Mat2 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix2fv(_paramName.data(),1,GL_FALSE,_v0.openGL());
}


void ShaderLib::getUniform(const std::string &_paramName, ngl::Mat2 &o_v)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniformMatrix2fv(_paramName.data(),o_v);
}


void ShaderLib::setUniform(const std::string &_paramName,Mat3 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,GL_FALSE,_v0.openGL());
}


void ShaderLib::getUniform(const std::string &_paramName, ngl::Mat3 &o_v)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniformMatrix3fv(_paramName.data(),o_v);
}

void ShaderLib::getUniform(const std::string &_paramName, ngl::Mat4 &o_v)  noexcept
{
 m_shaderPrograms[m_currentShader]->getRegisteredUniformMatrix4fv(_paramName.data(),o_v);
}

#ifdef USEGLM
void ShaderLib::setUniform(const std::string &_paramName,glm::vec2 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform2f(_paramName.data(),_v0.x,_v0.y);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::vec3 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform3f(_paramName.data(),_v0.x,_v0.y,_v0.z);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::vec4 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniform4f(_paramName.data(),_v0.x,_v0.y,_v0.z,_v0.w);
}

void ShaderLib::setUniform(const std::string &_paramName,glm::mat3 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,GL_FALSE,&_v0[0][0]);

}

#endif

void ShaderLib::setUniformMatrix4fv(const std::string &_paramName,const GLfloat *_value,MatrixTranspose _transpose) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix4fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}
void ShaderLib::setUniformMatrix3fv(const std::string &_paramName, const GLfloat *_value, MatrixTranspose _transpose) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}

void ShaderLib::setUniformMatrix2fv(const std::string &_paramName, const GLfloat *_value, MatrixTranspose _transpose) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix2fv(_paramName.data(),1,static_cast<bool>(_transpose),_value);

}



void ShaderLib::setUniform(const std::string &_paramName,Mat4 _v0) noexcept
{
  m_shaderPrograms[m_currentShader]->setRegisteredUniformMatrix4fv(_paramName.data(),1,GL_FALSE,_v0.openGL());
}





} // end ngl namespace



//----------------------------------------------------------------------------------------------------------------------

