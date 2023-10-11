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
#ifndef OBJ_H_
#define OBJ_H_

/// @file Obj.h
/// @brief basic obj loader inherits from AbstractMesh

// must include types.h first for Real and GLEW if required
#include "AbstractMesh.h"
#include <string_view>
#include <vector>

namespace ngl
{

/// @class Obj "include/Obj.h"
/// @brief used to load in an alias wave front obj format file and draw using open gl
/// removed all boost stuff
/// @author Jonathan Macey
/// @version 5.0


class NGL_DLLEXPORT Obj : public AbstractMesh
{

    public:
  
  /// @brief default constructor
  
  Obj() noexcept
    : ngl::AbstractMesh()
  {
  }
  
  /// @brief  constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  
  Obj(std::string_view _fname, CalcBB _calcBB = CalcBB::True) noexcept;
  
  /// @brief constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  /// @param[in]  &_texName the name of the texture file
  // avoid _texName being converted to bool via explicit conversion
  
  Obj(std::string_view _fname, std::string_view texName, CalcBB _calcBB = CalcBB::True) noexcept;

  Obj(const Obj &_c) noexcept;
  void setTexture(std::string_view _texName);
  void addVertex(const Vec3 &_v) noexcept;
  void addNormal(const Vec3 &_v) noexcept;
  void addUV(const Vec2 &_v) noexcept;
  void addUV(const Vec3 &_v) noexcept;
  void addFace(const Face &_f) noexcept;
  
  /// @brief  Method to load the file in
  /// @param[in]  _fname the name of the obj file to load
  /// @param[in] _calcBB if we only want to load data and not use GL then set this to false
  

  virtual bool load(std::string_view _fname, CalcBB _calcBB = CalcBB::True)  noexcept override;
  bool save(std::string_view _fname) const noexcept;
  bool isLoaded() const noexcept
  {
    return m_isLoaded;
  }

    protected:
  // note these are virtual so we can extend obj parser (see colour obj demo)
  virtual bool parseVertex(std::vector< std::string > &_tokens) noexcept;
  virtual bool parseNormal(std::vector< std::string > &_tokens) noexcept;
  virtual bool parseUV(std::vector< std::string > &_tokens) noexcept;
  static std::istream &safeGetline(std::istream &is, std::string &t);

  // face parsing is complex we have different layouts.
  // don't forget we can also have negative indices
  virtual bool parseFace(std::vector< std::string > &_tokens) noexcept;
  // f v v v v
  bool parseFaceVertex(std::vector< std::string > &_tokens) noexcept;
  // f v//vn v//vn v//vn v//vn
  bool parseFaceVertexNormal(std::vector< std::string > &_tokens) noexcept;
  // f v/vt v/vt v/vt v/vt
  bool parseFaceVertexUV(std::vector< std::string > &_tokens) noexcept;
  // f v/vt/vn v/vt/vn v/vt/vn v/vt/vn
  bool parseFaceVertexNormalUV(std::vector< std::string > &_tokens) noexcept;
  // as faces can use negative index values keep track of index
  int m_currentVertexOffset = 0;
  int m_currentNormalOffset = 0;
  int m_currentUVOffset = 0;
  bool m_isLoaded = false;
};

} // namespace ngl

#endif

