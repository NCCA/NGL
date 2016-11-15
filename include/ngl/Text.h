/*
  Copyright (C) 2011 Jon Macey

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
#ifndef TEXT_H_
#define TEXT_H_


//----------------------------------------------------------------------------------------------------------------------
/// @file Text.h
/// @brief Basic text rendering for OpenGL 3.x
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/10/11 Initial version
/// @todo support unicode ASCII is so 1980's ;-0
/// This class will generate billboard textures and VertexArrayObjects
/// for each of the font glyphs, this means we need a valid OpenGL context before
/// using this class, therefore it should be constructed in initalizeGL or after.
/// Note for efficiency once the font has been created we can only change the colour, if you
/// need different sizes / emphasis you will need to create a new Text object with the
/// desired size / emphasis. This is accelerated as much as possible but text rendering will sometimes be slow
/// as we bind a new texture for each char being drawn
/// for more details look at the blog post here
/// http://jonmacey.blogspot.com/2011/10/text-rendering-using-opengl-32.html
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required

#include "Colour.h"
#include "Types.h"
#include "Vec2.h"
#include "VAOFactory.h"
#include "SimpleVAO.h"

#include <QtCore/QHash>
#include <memory>
#include <QFont>
#include "Mat4.h"

namespace ngl
{

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a structure to hold the font char texture id
  /// and the vao. The vao for each font will be a different size
  /// need to investigate is a scale would be quicker / more efficient
  /// than storing multiple billboards (some will be the same size)
  //----------------------------------------------------------------------------------------------------------------------
  struct FontChar
  {
    int width; /// @brief the width of the font
    GLuint textureID; /// @brief the texture id of the font billboard
    AbstractVAO *vao; /// a vao for the font
  };

class NGL_DLLEXPORT Text
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor must pass in a ready constructed QFont make sure the size and emphasis
  /// is set before doing this as you can't modify the font after construction and you will
  /// need a new Text class for each different type of text / font
  /// @param[in] _f the font to use for drawing the text
  //----------------------------------------------------------------------------------------------------------------------
  Text( const QFont &_f ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor will clean / remove textures and VAO's for the class
  //----------------------------------------------------------------------------------------------------------------------
  ~Text();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief render the text to the screen at _x,_y where 0,0 is top left of the screen
  /// all positioning is relative to the screen size set with the setScreenSize method so it is important that
  /// changes in screen size are updated. These value will be sent to the nglTextShader to be rendered (see source )
  /// @note font quad is drawn as 0,0 being bottom left so if we draw at 0,0 the font will not be visible, we need
  /// to add the offset of the font height to any y value (i.e. a 16pt font drawn at 0,16 will appear at top right of the screen)
  /// @param[in] _x the x position of the text in screen space
  /// @param[in] _y the y position of the text in screen space
  /// @param[in] _text the text to draw (this is limited to ASCII chars ' '->'~' at present but unicode will be done soon
  //----------------------------------------------------------------------------------------------------------------------
  void renderText(float _x, float _y, const QString &_text ) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the size of the screen to scale our font to fit correctly
  /// this basically creates the orthographic projection needed for x/y assuming that the
  /// openGL window has 0,0 at the center and we use NDC co-ordinates -1 -> 1 in X and Y
  /// we then get x=(x*xScale)+xtran y=(y*yScale)+ytrans; to place the text in screen space
  /// @param[in] _w the current width of the screen
  /// @param[in] _h the current height of the screen
  //----------------------------------------------------------------------------------------------------------------------
  void setScreenSize( int _w, int _h  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the colour of the font from an Colour
  /// @param[in] _c the colour to set for the font (alpha is overridden by the texture)
  //----------------------------------------------------------------------------------------------------------------------
  void setColour( const Colour &_c  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the colour of the font from three floats as a convenience method
  /// @param[in] _r the red component of the colour for the font
  /// @param[in] _g the green component of the colour for the font
  /// @param[in] _b the blue component of the colour for the font
  //----------------------------------------------------------------------------------------------------------------------
  void setColour( Real _r, Real _g,  Real _b  ) noexcept;

  void setTransform(float _x, float _y) noexcept;
protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a hash to store our FontChar data looked up by the char we want
  /// to render according to the Qt Docs a hash has faster lookups than QMap
  /// so using this
  //----------------------------------------------------------------------------------------------------------------------
  QHash <char,FontChar> m_characters;
};

}

#endif






//----------------------------------------------------------------------------------------------------------------------
