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
#include "pystring.h"
#include <cstring>
#include <iostream>
#include <rapidxml/rapidxml.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCAPointBake.cpp
/// @brief implementation files for NCCAPointBake class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
namespace ps = pystring;

//----------------------------------------------------------------------------------------------------------------------

bool NCCAPointBake::loadPointBake(std::string_view _fileName) noexcept
{
  m_numFrames = 0;
  m_currFrame = 0;
  m_nVerts = 0;
  m_startFrame = 0;
  m_endFrame = 0;
  m_mesh = nullptr;
  m_binFile = false;
  const rapidxml::xml_node<> *rootNode;
  // Read the xml file into a vector
  std::ifstream xmlFile(_fileName.data());
  if(!xmlFile.is_open())
  {
    NGLMessage::addError(fmt::format("Could not open PointBake file {0} ", _fileName.data()));
    return false;
  }
  std::vector< char > buffer((std::istreambuf_iterator< char >(xmlFile)), std::istreambuf_iterator< char >());
  buffer.push_back('\0');
  rapidxml::xml_document<> doc;

  doc.parse< rapidxml::parse_trim_whitespace >(&buffer[0]);
  rootNode = doc.first_node();
  if(rootNode->name() != std::string("NCCAPointBake"))
  {
    NGLMessage::addError(fmt::format("{0} is not a pointbake file ", _fileName.data()));
    return false;
  }

  auto child = rootNode->first_node("MeshName");
  m_meshName = child->value();
  NGLMessage::addMessage(fmt::format("found mesh{0} ", m_meshName));

  try
  {
    child = rootNode->first_node("NumVerts");
    m_nVerts = std::stoul(child->value());
    NGLMessage::addMessage(fmt::format("NumVerts {0}", m_nVerts));
    child = rootNode->first_node("StartFrame");
    m_startFrame = std::stoul(child->value());
    NGLMessage::addMessage(fmt::format("StartFrame {0}", m_startFrame));
    child = rootNode->first_node("EndFrame");
    m_endFrame = std::stoul(child->value());
    NGLMessage::addMessage(fmt::format("EndFrame {0}", m_endFrame));
    child = rootNode->first_node("NumFrames");
    m_numFrames = std::stoul(child->value());
    NGLMessage::addMessage(fmt::format("NumFrames  {0}", m_numFrames));
  }
  catch(std::invalid_argument const &)
  {
    NGLMessage::addError("error reading PointBake File");
    return false;
  }
  // first allocate base pointer [vertex]
  m_data.resize(m_numFrames);
  // now for each of these we need to allocate more space
  //  NOTE the use of a reference here as we are changing the size
  for(auto &data : m_data)
  {
    data.resize(m_nVerts);
  }
  // this is the line we wish to parse
  std::string lineBuffer;
  // say which separators should be used in this
  // case Spaces, Tabs and return \ new line
  const std::string sep(" \t\r\n");

  // now traverse each frame and grab the data
  for(child = rootNode->first_node("Frame"); child; child = child->next_sibling())
  {
    size_t CurrentFrame;

    NGLMessage::addMessage(fmt::format("doing frame {0}", child->first_attribute("number")->value()));
    CurrentFrame = std::stoul(child->first_attribute("number")->value());
    CurrentFrame -= m_startFrame;

    for(auto vertex = child->first_node("Vertex"); vertex; vertex = vertex->next_sibling())
    {
      size_t index = std::stoul(vertex->first_attribute("number")->value());
      lineBuffer = vertex->value();
      std::vector< std::string > tokens;
      ps::split(lineBuffer, tokens);
      try
      {
        float x = std::stof(tokens[0]);
        float y = std::stof(tokens[1]);
        float z = std::stof(tokens[2]);
        m_data[CurrentFrame][index].set(x, y, z);
      }
      catch(std::invalid_argument const &)
      {
        NGLMessage::addError("error converting buffer");
        NGLMessage::addError(fmt::format("{0} size {1} ", lineBuffer, tokens.size()));
        return false;
      }
    }
  }
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::NCCAPointBake(std::string_view _fileName) noexcept
{
  loadPointBake(_fileName);
}
//----------------------------------------------------------------------------------------------------------------------
void NCCAPointBake::setFrame(const size_t _frame) noexcept
{
  m_currFrame = _frame;
}


void NCCAPointBake::setMeshToFrame(const unsigned int _frame) noexcept
{
  // map the m_obj's vbo dat
  Real *ptr = m_mesh->mapVAOVerts();
  std::vector< Face > faces = m_mesh->getFaceList();
  // unsigned int nFaces=faces.size();
  //  loop for each of the faces
  unsigned int step = 0;
  for(auto face : faces)
  {
    // now for each triangle in the face (remember we ensured tri when loading)
    // loop for all the verts and set the new vert value
    // the data is packed uv, nx,ny,nz then x,y,z
    // as we only want to change x,y,z, we need to skip over
    // stuff

    for(unsigned int j = 0; j < 3; ++j)
    {
      ptr[step] = m_data[_frame][face.m_vert[j]].m_x;
      ptr[step + 1] = m_data[_frame][face.m_vert[j]].m_y;
      ptr[step + 2] = m_data[_frame][face.m_vert[j]].m_z;
      step += 8;
    }
  }

  // unmap the vbo as we have finished updating
  m_mesh->unMapVAO();
  m_currFrame = _frame;
}

//----------------------------------------------------------------------------------------------------------------------
bool NCCAPointBake::attachMesh(AbstractMesh *_mesh) noexcept
{
  NGLMessage::addMessage("doing attach mesh");
  if(_mesh->m_verts.size() != m_nVerts)
  {
    NGLMessage::addError(" Mesh can't be attached to this data as vert count does not match");
    NGLMessage::addError(fmt::format("mesh verts {0} file verts {1}", _mesh->m_verts.size(), m_nVerts));
    return false;
  }

  else
  {
    m_mesh = _mesh;
    return true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
std::vector< Vec3 > &NCCAPointBake::getRawDataPointerAtFrame(unsigned int _f) noexcept
{
  NGL_ASSERT(_f <= m_numFrames)
  return m_data[_f];
}

} // namespace ngl
//----------------------------------------------------------------------------------------------------------------------
