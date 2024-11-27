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
/// @file Obj.cpp
/// @brief implementation files for Obj class
//----------------------------------------------------------------------------------------------------------------------
#include "Obj.h"
#include "pystring.h"
#include <cmath>
#include <iostream>

#if defined(WIN32)

namespace std
{
template < typename T >
bool signbit(T t)
{
  return signbit(double(t));
}
} // namespace std

#endif

namespace ngl
{

namespace ps = pystring;

Obj::Obj(std::string_view _fname, CalcBB _calcBB) noexcept
  : AbstractMesh()
{
  if(!load(_fname, _calcBB) )
  {
    NGLMessage::addError(fmt::format("Error loading file {0} ", _fname.data()));
    exit(EXIT_FAILURE);
  }
}

Obj::Obj(std::string_view _fname, std::string_view _texName, CalcBB _calcBB) noexcept
  : AbstractMesh()
{
  if(!load(_fname, _calcBB))
  {
    NGLMessage::addError(fmt::format("Error loading file {0} ", _fname.data()));
    exit(EXIT_FAILURE);
  }
  // load texture
  loadTexture(_texName);
  m_texture = true;
}

void Obj::setTexture(std::string_view _texName)
{
  loadTexture(_texName);
}

Obj::Obj(const Obj &_c) noexcept
{
  m_verts = _c.m_verts;
  m_norm = _c.m_norm;
  m_uv = _c.m_uv;
  m_face = _c.m_face;
  m_center = _c.m_center;
  m_vbo = false;
  m_vao = false;
  m_vboMapped = false;
  m_texture = _c.m_texture;
  m_textureID = _c.m_textureID;
  m_maxX = _c.m_maxX;
  m_minX = _c.m_minX;
  m_maxY = _c.m_maxY;
  m_minY = _c.m_minY;
  m_maxZ = _c.m_maxZ;
  m_minZ = _c.m_minZ;
  m_loaded = true;
  m_sphereCenter = _c.m_sphereCenter;
  m_sphereRadius = _c.m_sphereRadius;
}

void Obj::addVertex(const ngl::Vec3 &_v) noexcept
{
  m_verts.push_back(_v);
}
void Obj::addNormal(const ngl::Vec3 &_v) noexcept
{
  m_norm.push_back(_v);
}
void Obj::addUV(const ngl::Vec2 &_v) noexcept
{
  ngl::Vec3 v(_v.m_x, _v.m_y, 0.0f);
  m_uv.push_back(v);
}
void Obj::addUV(const ngl::Vec3 &_v) noexcept
{
  m_uv.push_back(_v);
}

void Obj::addFace(const ngl::Face &_f) noexcept
{
  m_face.push_back(_f);
}

bool Obj::save(std::string_view _fname) const noexcept
{
  std::ofstream out(_fname.data());
  if(!out.is_open() )
  {
    NGLMessage::addError(fmt::format(" could not open file  {0} for writing ", _fname.data()));
    return false;
  }
  // write out some comments
  out << "# This file was created by ngl Obj exporter " << _fname.data() << '\n';
  // write out the verts
  for(auto v : m_verts)
  {
    out << "v " << v.m_x << " " << v.m_y << " " << v.m_z << '\n';
  }

  // write out the tex cords
  for(auto v : m_uv)
  {
    out << "vt " << v.m_x << " " << v.m_y << '\n';
  }
  // write out the normals

  for(auto v : m_norm)
  {
    out << "vn " << v.m_x << " " << v.m_y << " " << v.m_z << '\n';
  }
  // finally the faces
  for(auto f : m_face)
  {
    out << "f ";
    // we now have V/T/N for each to write out
    for(unsigned int i = 0; i < f.m_vert.size(); ++i)
    {
      // don't forget that obj indices start from 1 not 0 (I did originally !)
      out << f.m_vert[i] + 1;
      if( ! m_uv.empty() )
      {
        out << '/';
        out << f.m_uv[i] + 1;
      }
      if( ! m_norm.empty())
      {
        out << '/';
        // weird case where we need to do f 1//1
        if(m_uv.empty())
        {
          out << '/';
        }
        out << f.m_norm[i] + 1;
        out << " ";
      }
      out << ' ';
    }
    out << '\n';
  }
  return true;
}

// function from https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
// added after windows build broke NGL tests,
std::istream &Obj::safeGetline(std::istream &is, std::string &t)
{
  t.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(is, true);
  std::streambuf *sb = is.rdbuf();

  for(;;)
  {
    int c = sb->sbumpc();
    switch(c)
    {
      case '\n':
        return is;
      case '\r':
        if(sb->sgetc() == '\n')
          sb->sbumpc();
        return is;
      case std::streambuf::traits_type::eof():
        // Also handle the case when the last line has no line ending
        if(t.empty())
          is.setstate(std::ios::eofbit);
        return is;
      default:
        t += static_cast< char >(c);
    }
  }
}

bool Obj::load(std::string_view _fname, CalcBB _calcBB) noexcept
{
  std::ifstream in(_fname.data());
  if(!in.is_open() )
  {
    NGLMessage::addError(fmt::format(" file {0} not found  ", _fname.data()));
    return false;
  }

  std::string str;
  // Read the next line from File untill it reaches the end.
  // while (std::getline(in, str))
  while(!safeGetline(in, str).eof())
  {
    bool status = true;
    // Line contains string of length > 0 then parse it
    if(!str.empty())
    {
      std::vector< std::string > tokens;
      ps::split(str, tokens);
      if(tokens[0] == "v")
      {
        status = parseVertex(tokens);
      }
      else if(tokens[0] == "vn")
      {
        status = parseNormal(tokens);
      }

      else if(tokens[0] == "vt")
      {
        status = parseUV(tokens);
      }
      else if(tokens[0] == "f")
      {
        status = parseFace(tokens);
      }
    } // str.size()
    // early out sanity checks!
    if(!status )
      return false;
  } // while

  in.close();
  // Calculate the center of the object.
  if(_calcBB == CalcBB::True)
  {
    this->calcDimensions();
  }
  m_isLoaded = true;
  return true;
}

bool Obj::parseVertex(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  try
  {
    float x = std::stof(_tokens[1]);
    float y = std::stof(_tokens[2]);
    float z = std::stof(_tokens[3]);
    m_verts.push_back({x, y, z});
    ++m_currentVertexOffset;
  }
  catch(std::invalid_argument &arg)
  {
    NGLMessage::addError("problem converting Obj file vertex ");
    NGLMessage::addError(arg.what());
    parsedOK = false;
  }
  return parsedOK;
}

bool Obj::parseNormal(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  try
  {
    float x = std::stof(_tokens[1]);
    float y = std::stof(_tokens[2]);
    float z = std::stof(_tokens[3]);
    m_norm.push_back({x, y, z});
    ++m_currentNormalOffset;
  }
  catch(std::invalid_argument &arg)
  {
    NGLMessage::addError("problem converting Obj file normals");
    NGLMessage::addError(arg.what());
    parsedOK = false;
  }
  return parsedOK;
}

bool Obj::parseUV(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  try
  {
    auto z=0.0f;
    auto x = std::stof(_tokens[1]);
    auto y = std::stof(_tokens[2]);
    if(_tokens.size() == 4)
    {
      z = std::stof(_tokens[3]);
    }

    m_uv.push_back({x, y, z});
    ++m_currentUVOffset;
  }
  catch(std::invalid_argument &arg)
  {
    NGLMessage::addError("problem converting Obj file UV's");
    NGLMessage::addError(arg.what());

    parsedOK = false;
  }
  return parsedOK;
}

bool Obj::parseFace(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  // first let's find what sort of face we are dealing with
  // I assume most likely case is all
  if(ps::count(_tokens[1], "/") == 2 && ps::find(_tokens[1], "//") == -1)
  {
    parsedOK = parseFaceVertexNormalUV(_tokens);
  }

  else if(ps::find(_tokens[1], "/") == -1)
  {
    parsedOK = parseFaceVertex(_tokens);
  }
  // look for VertNormal
  else if(ps::find(_tokens[1], "//") != -1)
  {
    parsedOK = parseFaceVertexNormal(_tokens);
  }
  // if we have 1 / it is a VertUV format
  else if(ps::count(_tokens[1], "/") == 1)
  {
    parsedOK = parseFaceVertexUV(_tokens);
  }

  return parsedOK;
}
// f v v v v
bool Obj::parseFaceVertex(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  ngl::Face f;
  // token still starts with f so skip
  for(size_t i = 1; i < _tokens.size(); ++i)
  {
    try
    {
      // note we need to subtract one from the list
      int idx = std::stoi(_tokens[i]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentVertexOffset + (idx + 1);
      }
      f.m_vert.push_back(static_cast< uint32_t >(idx));
    }
    catch(std::invalid_argument &arg)
    {
      NGLMessage::addError("problem converting Obj file face");
      NGLMessage::addError(arg.what());
      parsedOK = false;
    }
  }
  m_face.push_back(f);
  return parsedOK;
}
// f v//vn v//vn v//vn v//vn
bool Obj::parseFaceVertexNormal(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  ngl::Face f;
  // token still starts with f so skip
  for(size_t i = 1; i < _tokens.size(); ++i)
  {
    std::vector< std::string > vn;
    ps::split(_tokens[i], vn, "//");
    try
    {
      // note we need to subtract one from the list
      int idx = std::stoi(vn[0]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentVertexOffset + (idx + 1);
      }
      f.m_vert.push_back(static_cast< uint32_t >(idx));
      idx = std::stoi(vn[1]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentNormalOffset + (idx + 1);
      }
      f.m_norm.push_back(static_cast< uint32_t >(idx));
    }
    catch(std::invalid_argument &arg)
    {
      NGLMessage::addError("problem converting Obj file face");
      NGLMessage::addError(arg.what());
      parsedOK = false;
    }
  }
  m_face.push_back(f);
  return parsedOK;
}
// f v/vt v/vt v/vt v/vt
bool Obj::parseFaceVertexUV(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  ngl::Face f;
  // token still starts with f so skip
  for(size_t i = 1; i < _tokens.size(); ++i)
  {
    std::vector< std::string > vn;
    ps::split(_tokens[i], vn, "/");
    try
    {
      // note we need to subtract one from the list
      int idx = std::stoi(vn[0]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentVertexOffset + (idx + 1);
      }
      f.m_vert.push_back(static_cast< uint32_t >(idx));
      idx = std::stoi(vn[1]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentUVOffset + (idx + 1);
      }
      f.m_uv.push_back(static_cast< uint32_t >(idx));
    }
    catch(std::invalid_argument &arg)
    {
      NGLMessage::addError("problem converting Obj file face");
      NGLMessage::addError(arg.what());
      parsedOK = false;
    }
  }
  m_face.push_back(f);
  return parsedOK;
}
// f v/vt/vn v/vt/vn v/vt/vn v/vt/vn
bool Obj::parseFaceVertexNormalUV(std::vector< std::string > &_tokens) noexcept
{
  bool parsedOK = true;
  ngl::Face f;
  // token still starts with f so skip
  for(size_t i = 1; i < _tokens.size(); ++i)
  {
    std::vector< std::string > vn;
    ps::split(_tokens[i], vn, "/");
    try
    {
      // note we need to subtract one from the list
      int idx = std::stoi(vn[0]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentVertexOffset + (idx + 1);
      }
      f.m_vert.push_back(static_cast< uint32_t >(idx));

      idx = std::stoi(vn[1]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentUVOffset + (idx + 1);
      }
      f.m_uv.push_back(static_cast< uint32_t >(idx));

      idx = std::stoi(vn[2]) - 1;
      // check if we are a negative index
      if(std::signbit(idx))
      {
        // note we index from 0 not 1 like obj so adjust
        idx = m_currentNormalOffset + (idx + 1);
      }
      f.m_norm.push_back(static_cast< uint32_t >(idx));
    }
    catch(std::invalid_argument &arg)
    {
      NGLMessage::addError("problem converting Obj file face");
      NGLMessage::addError(arg.what());
      parsedOK = false;
    }
  }
  m_face.push_back(f);
  return parsedOK;
}

} // namespace ngl
