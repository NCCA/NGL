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
//----------------------------------------------------------------------------------------------------------------------
/// @file Obj.h
/// @brief basic obj loader inherits from AbstractMesh
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include <vector>
#include <string>
#include "AbstractMesh.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Obj "include/Obj.h"
/// @brief used to load in an alias wave front obj format file and draw using open gl
/// removed all boost stuff
/// @author Jonathan Macey
/// @version 5.0
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Obj : public AbstractMesh
{

  public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief default constructor
    //----------------------------------------------------------------------------------------------------------------------
    Obj()  noexcept: ngl::AbstractMesh(){}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  constructor to load an objfile as a parameter
    /// @param[in]  &_fname the name of the obj file to load
    //----------------------------------------------------------------------------------------------------------------------
    Obj( const std::string_view& _fname  , CalcBB _clacBB=CalcBB::True)  noexcept ;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor to load an objfile as a parameter
    /// @param[in]  &_fname the name of the obj file to load
    /// @param[in]  &_texName the name of the texture file
    // avoid _texName being converted to bool via explicit conversion
    //----------------------------------------------------------------------------------------------------------------------
    Obj(const std::string_view &_fname,  const std::string_view &_texName, CalcBB _calcBB=CalcBB::True ) noexcept;

    Obj(const Obj &_c);
    void addVertex(const Vec3 &_v);
    void addNormal(const Vec3 &_v);
    void addUV(const Vec2 &_v);
    void addUV(const Vec3 &_v);
    void addFace(const Face &_f);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  Method to load the file in
    /// @param[in]  _fname the name of the obj file to load
    /// @param[in] _calcBB if we only want to load data and not use GL then set this to false
    //----------------------------------------------------------------------------------------------------------------------

    virtual bool load(const std::string_view &_fname, CalcBB _calcBB=CalcBB::True ) noexcept;
    bool save(const std::string_view &_fname);
    bool isLoaded() const {return m_isLoaded;}
  private :
    bool parseVertex(std::vector<std::string> &_tokens);
    bool parseNormal(std::vector<std::string> &_tokens);
    bool parseUV(std::vector<std::string> &_tokens);
    // face parsing is complex we have different layouts.
    // don't forget we can also have negative indices
    bool parseFace(std::vector<std::string> &_tokens);
    // f v v v v
    bool parseFaceVertex(std::vector<std::string> &_tokens);
    // f v//vn v//vn v//vn v//vn
    bool parseFaceVertexNormal(std::vector<std::string> &_tokens);
    // f v/vt v/vt v/vt v/vt
    bool parseFaceVertexUV(std::vector<std::string> &_tokens);
    // f v/vt/vn v/vt/vn v/vt/vn v/vt/vn
    bool parseFaceVertexNormalUV(std::vector<std::string> &_tokens);

    std::vector<std::string> m_fileContents;
    bool m_isLoaded=false;
    // as faces can use negative index values keep track of index
    size_t m_currentVertexOffset=0;
    size_t m_currentNormalOffset=0;
    size_t m_currentUVOffset=0;
};

}


#endif
//----------------------------------------------------------------------------------------------------------------------

