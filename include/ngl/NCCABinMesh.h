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
#ifndef NCCABINMESH_H_
#define NCCABINMESH_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCABinMesh.h
/// @brief inherited from AbstractMesh export and load binary data in our own format
// must include types.h first for Real and GLEW if required
//----------------------------------------------------------------------------------------------------------------------
#include "Types.h"
#include "AbstractMesh.h"
#include "BBox.h"
#include "RibExport.h"
#include "Texture.h"
#include "Vec4.h"
#include <string>
#include <vector>
//#include <boost/tokenizer.hpp>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class NCCABinMesh "include/NCCABinMesh.h"
/// @brief basically this class Loads the contents of the current VBO to file,
/// this is basically the AbstractMesh packed Vert, Texture cord and Normal data
/// Which are stored in contiguous blocks from the Parent Save method.
/// this will then create a VBO which can be mapped and drawn etc.
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/05/10 initial development
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT NCCABinMesh : public  AbstractMesh
{

public :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default constructor
  //----------------------------------------------------------------------------------------------------------------------
    NCCABinMesh() noexcept{;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  //----------------------------------------------------------------------------------------------------------------------
  NCCABinMesh( const std::string& _fname  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  /// @param[in]  &_texName the name of the texture file
  //----------------------------------------------------------------------------------------------------------------------
  NCCABinMesh( const std::string& _fname, const std::string& _texName) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Method to load the file in
  /// @param[in]  _fname the name of the obj file to load
  //----------------------------------------------------------------------------------------------------------------------
  bool load( const std::string& _fname, bool _calcBB=true) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to save the obj
  /// @param[in] _fname the name of the file to save
  //----------------------------------------------------------------------------------------------------------------------
  void save( const std::string& _fname) noexcept;

protected :

  // not data all in parent
};

}


#endif
//----------------------------------------------------------------------------------------------------------------------

