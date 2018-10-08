/*
  Copyright (C) 2010 Jon Macey

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

#include "NCCAPointBake.h"
#include "rapidxml/rapidxml.hpp"
#include "pystring.h"
#include <iostream>
#include <cstring>
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCAPointBake.cpp
/// @brief implementation files for NCCAPointBake class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
namespace ps=pystring;

//----------------------------------------------------------------------------------------------------------------------

bool NCCAPointBake::loadPointBake(const std::string &_fileName) noexcept
{
	m_numFrames=0;
	m_currFrame=0;
	m_nVerts=0;
	m_startFrame=0;
	m_endFrame=0;
  m_mesh=nullptr;
	m_binFile=false;
	rapidxml::xml_node<> * rootNode;
	// Read the xml file into a vector
  std::ifstream xmlFile (_fileName.data() );
	if(!xmlFile.is_open())
	{
    msg->addError(fmt::format("Could not open PointBake file {0} ",_fileName.data()));
		return false;
	}
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	rapidxml::xml_document<> doc;

	doc.parse<rapidxml::parse_trim_whitespace>(&buffer[0]);
	rootNode=doc.first_node();
	if(rootNode->name() !=std::string("NCCAPointBake"))
	{
    msg->addError(fmt::format("{0} is not a pointbake file ",_fileName.data()));
		return false;
	}

  rapidxml::xml_node<> * child=rootNode->first_node("MeshName");
  m_meshName=child->value();
  msg->addMessage(fmt::format("found mesh{0} ",m_meshName));

  try
  {
    child=rootNode->first_node("NumVerts");
    m_nVerts=std::stoul(child->value());
    msg->addMessage(fmt::format("NumVerts {0}",m_nVerts));
    child=rootNode->first_node("StartFrame");
    m_startFrame=std::stoul(child->value());
    msg->addMessage(fmt::format("StartFrame {0}",m_startFrame));;
    child=rootNode->first_node("EndFrame");
    m_endFrame=std::stoul(child->value());
    msg->addMessage(fmt::format("EndFrame {0}",m_endFrame));
    child=rootNode->first_node("NumFrames");
    m_numFrames=std::stoul(child->value());
    msg->addMessage(fmt::format("NumFrames  {0}",m_numFrames));
  }
  catch (std::invalid_argument)
  {
    msg->addError("error reading PointBake File");
    return false;
  }
  //first allocate base pointer [vertex]
  m_data.resize(m_numFrames);
  //cout <<"Size is now"<<m_data.size()<<endl;
  //now for each of these we need to allocate more space
  // NOTE the use of a reference here as we are changing the size
  for(auto &data : m_data)
  {
    data.resize(m_nVerts);
  }
  size_t CurrentFrame=0;
  // this is the line we wish to parse
  std::string lineBuffer;
  // say which separators should be used in this
  // case Spaces, Tabs and return \ new line
  const std::string sep(" \t\r\n");

  // now traverse each frame and grab the data
  for(child=rootNode->first_node("Frame"); child; child=child->next_sibling())
  {
    msg->addMessage(fmt::format("doing frame {0}",child->first_attribute("number")->value()));
    CurrentFrame=std::stoul(child->first_attribute("number")->value());
    CurrentFrame-=m_startFrame;

    for(rapidxml::xml_node<> * vertex=child->first_node("Vertex"); vertex; vertex=vertex->next_sibling())
    {
      size_t index=std::stoul(vertex->first_attribute("number")->value());
      lineBuffer=vertex->value();
      std::vector <std::string> tokens;
      ps::split(lineBuffer,tokens);
      try
      {
        float x=std::stof(tokens[0]);
        float y=std::stof(tokens[1]);
        float z=std::stof(tokens[2]);
        m_data[CurrentFrame][index].set(x,y,z);
      }
      catch (std::invalid_argument)
      {
        msg->addError("error converting buffer");
        msg->addError(fmt::format("{0} size {1} ",lineBuffer,tokens.size()));
        return false;
      }

    }

  }
  return true;
}




//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::~NCCAPointBake() noexcept
{

}
//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::NCCAPointBake(const std::string &_fileName) noexcept
{
  loadPointBake(_fileName);
}
//----------------------------------------------------------------------------------------------------------------------
void NCCAPointBake::setFrame(const size_t _frame) noexcept
{
 m_currFrame=_frame;
}

bool NCCAPointBake::loadBinaryPointBake(const std::string &_fileName) noexcept
{
  // open a file stream for ip in binary mode
  std::fstream file;
  file.open(_fileName.data(),std::ios::in | std::ios::binary);
  // see if it worked
  if (!file.is_open())
  {
    msg->addError(fmt::format("problems Opening File {0}",_fileName.data()));
    return false;
  }
  // lets read in the header and see if the file is valid
  char header[11];
  file.read(header,10*sizeof(char));
  header[10]=0; // for strcmp we need \n
  // basically I used the magick string ngl::bin (I presume unique in files!) and
  // we test against it.
  if(strcmp(header,"ngl::binpb"))
  {
    // best close the file and exit
    file.close();
    msg->addError("this is not an ngl::binpb file ");
    return false;
  }

  /// The number of vertices in the object
  //file.read(reinterpret_cast <char *> (&m_nVerts),sizeof(unsigned long int));

  file.read(reinterpret_cast <char *>(&m_numFrames),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_currFrame),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_nVerts),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_startFrame),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_binFile),sizeof(bool));
  msg->addMessage("Loaded header\n");

  m_data.resize(m_numFrames);
  for(unsigned int frame =0; frame<m_numFrames; ++frame)
  {
    m_data[frame].resize(m_nVerts);
    for(unsigned int v=0; v< m_nVerts; ++v)
    {
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_x),sizeof(Real));
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_y),sizeof(Real));
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_z),sizeof(Real));
   }
  }
  return true;
}

bool NCCAPointBake::saveBinaryPointBake(const std::string &_fileName) noexcept
{
  // so basically we need to save all the state data from the abstract mesh
  // then map the vbo on the gpu and dump that in one go, this means we have to
  // call CreateVBO first the Save
    std::fstream file;
    file.open(_fileName.data(),std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
      msg->addError(fmt::format("problems Opening File {0} ",_fileName.data()));
      return false;
    }

    // lets write out our own Magic Number file ID
    const std::string header("ngl::binpb");
    file.write(header.c_str(),static_cast<long>(header.length()));
    m_binFile=true;
    file.write(reinterpret_cast <char *>(&m_numFrames),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_currFrame),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_nVerts),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_startFrame),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_binFile),sizeof(bool));

    // now write out data
    for(unsigned int frame =0; frame<m_numFrames; ++frame)
    {
      for(unsigned int v=0; v< m_nVerts; ++v)
      {
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_x),sizeof(Real));
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_y),sizeof(Real));
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_z),sizeof(Real));
     }
    }

    file.close();
    return true;
}

void NCCAPointBake::setMeshToFrame(  const unsigned int _frame) noexcept
{
    // map the m_obj's vbo dat
    Real *ptr=m_mesh->mapVAOVerts();
    std::vector <Face> faces=m_mesh->getFaceList();
    //unsigned int nFaces=faces.size();
    // loop for each of the faces
    unsigned int step=0;
    for(auto face : faces)
    {
      // now for each triangle in the face (remember we ensured tri when loading)
      // loop for all the verts and set the new vert value
      // the data is packed uv, nx,ny,nz then x,y,z
      // as we only want to change x,y,z, we need to skip over
      // stuff

      for(unsigned int j=0;j<3;++j)
      {
        ptr[step]=m_data[_frame][face.m_vert[j]].m_x;
        ptr[step+1]=m_data[_frame][face.m_vert[j]].m_y;
        ptr[step+2]=m_data[_frame][face.m_vert[j]].m_z;
        step+=8;
      }

    }

    // unmap the vbo as we have finished updating
    m_mesh->unMapVAO();
    m_currFrame=_frame;
 }




//----------------------------------------------------------------------------------------------------------------------
bool NCCAPointBake::attachMesh(AbstractMesh *_mesh) noexcept
{
  msg->addMessage("doing attach mesh");
  if(_mesh->m_verts.size() != m_nVerts)
  {
    msg->addError(" Mesh can't be attached to this data as vert count does not match");
    msg->addError(fmt::format("mesh verts {0} file verts {1}",_mesh->m_verts.size(),m_nVerts));
    return false;
  }

  else
  {
    m_mesh=_mesh;
    return true;
  }

}


//----------------------------------------------------------------------------------------------------------------------
std::vector<Vec3> & NCCAPointBake::getRawDataPointerAtFrame(unsigned int _f) noexcept
{
	NGL_ASSERT(_f<=m_numFrames);
	return m_data[_f];
}



} // end ngl namespace
//----------------------------------------------------------------------------------------------------------------------
