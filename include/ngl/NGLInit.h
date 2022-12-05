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
#ifndef NGLINIT_H_
#define NGLINIT_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLInit.h
/// @brief basic class to initialise the NGL library
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "NGLMessage.h"
#include "Types.h"
#include "VAOPrimitives.h"
#include <memory>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @class NGLInit  "include/NGLInit.h"
/// @brief a class to initialise all of the ngl elements includeing GLEW if needed as well vbo prims
/// this class is a singletone so can only be created once
/// @author Jonathan Macey
/// @version 4.0
/// @date Last Revision 19/11/09 changed the whole lib to be NGL not GraphicsLib so change names to reflect
///	 29/09/09 Updated to meet NCCA Coding standard
/// @example GraphicsLibInitExample/GraphicsLibInitExample.cpp
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT NGLInit
{
    public:
  static void initialize();
  ~NGLInit() =default;

    protected:
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
  NGLInit();

  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
};
} // namespace ngl

#endif

//----------------------------------------------------------------------------------------------------------------------
