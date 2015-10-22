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
#include "Types.h"
#include <vector>
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Vec4.h"
#include "AbstractMesh.h"
#include "BBox.h"
#include "RibExport.h"
#include <cmath>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Obj "include/Obj.h"
/// @brief used to load in an alias wave front obj format file and draw using open gl
///  has been completly re-written to use boost::spirit parser, most of this code is a
/// modified version of the OBJReader class from the cortex-vfx lib framework here
/// http://code.google.com/p/cortex-vfx/
/// @author Jonathan Macey
/// @version 4.0
/// @date 22/10/09 updated to use boost::spirit parser framework
/// @example AnimatedObj/AnimatedObj.cpp
/// @example ObjViewer/ObjViewer.cpp
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Obj : public AbstractMesh
{

public :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default constructor
  //----------------------------------------------------------------------------------------------------------------------
  Obj()  noexcept: AbstractMesh(){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  //----------------------------------------------------------------------------------------------------------------------
  Obj( const std::string& _fname ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  /// @param[in]  &_texName the name of the texture file
  //----------------------------------------------------------------------------------------------------------------------
  Obj( const std::string& _fname,  const std::string& _texName ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Method to load the file in
  /// @param[in]  _fname the name of the obj file to load
  /// @param[in] _calcBB if we only want to load data and not use GL then set this to false
  //----------------------------------------------------------------------------------------------------------------------
  bool load(const std::string& _fname, bool _calcBB=true ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  method to save the obj
  /// @param[in] _fname the name of the file to save
  //----------------------------------------------------------------------------------------------------------------------
  void save( const std::string& _fname  ) const  noexcept;

protected :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the vertex used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseVertex( const char *_begin ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the Norma used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseNormal( const char *_begin  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the text cord used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseTextureCoordinate( const char * _begin ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the Face data used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseFace( const char * _begin ) noexcept;

};

}


#endif
//----------------------------------------------------------------------------------------------------------------------

