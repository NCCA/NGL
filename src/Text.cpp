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
//---------------------------------------------------------------------------

#include <iostream>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

//#include <QPainter>
#include <array>
#include <memory>
#include "Text.h"
#include "ShaderLib.h"
#include "Util.h"
#include "NGLStream.h"
namespace ngl
{

// This has now been updated to use freetype and the text position now based from bottom right being 0,0
// See https://learnopengl.com/In-Practice/Text-Rendering for freetype stuff.
Text::Text(const std::string &_name, int _size)
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
      ngl::NGLMessage::addError("ERROR::FREETYPE: Could not init FreeType Library \n");
      exit(EXIT_FAILURE);
  }

  FT_Face face;
  if (FT_New_Face(ft, _name.c_str(), 0, &face))
  {
      ngl::NGLMessage::addError("ERROR::FREETYPE: Failed to load font");
      exit(EXIT_FAILURE);
  }
  // now set the font size
  FT_Set_Pixel_Sizes(face, 0,_size);  

  // loop for all basic keyboard chars we will use space to ~
  // should really change this to unicode at some stage
  const static char startChar=' ';
  const static char endChar='~';

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

  for(char c=startChar; c<=endChar; ++c)
  {

  if (FT_Load_Char(face, c, FT_LOAD_RENDER))
  {
      ngl::NGLMessage::addError("ERROR::FREETYTPE: Failed to load Glyph \n");
      exit(EXIT_FAILURE);
  }
  FontChar fc;


  // now we create the OpenGL texture ID and bind to make it active
  glGenTextures(1, &fc.textureID);
  glBindTexture(GL_TEXTURE_2D, fc.textureID);

  glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,
  0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
  // set texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//  glGenerateMipmap(GL_TEXTURE_2D);


  fc.sizex=face->glyph->bitmap.width;
  fc.sizey=face->glyph->bitmap.rows;
  fc.bearingx=face->glyph->bitmap_left;
  fc.bearingy=face->glyph->bitmap_top;
  fc.advance=static_cast<unsigned int>(face->glyph->advance.x);
  m_characters[c]=fc;
  }
  // set a default colour (black) incase user forgets
  setColour(0.0f,0.0f,0.0f);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  
  m_texVAO=VAOFactory::createVAO("simpleVAO",GL_TRIANGLES);



}



//---------------------------------------------------------------------------
Text::~Text()
{
  // our dtor should clear out the textures and remove the VAO's
  for( auto &m : m_characters)
  {
    glDeleteTextures(1,&m.second.textureID);
  }

}


void Text::renderText( float _x, float _y,  const char *_text ) const noexcept
{
  renderText(_x,_y,std::string(_text));
}


//---------------------------------------------------------------------------
void Text::renderText( float _x, float _y,  const std::string &_text ) const noexcept
{
  // make sure we are in texture unit 0 as this is what the
  // shader expects
  glActiveTexture(GL_TEXTURE0);
  // grab an instance of the shader manager
  // use the built in text rendering shader
  ShaderLib::use("nglTextShader");
  // the y pos will always be the same so set it once for each
  // string we are rendering
  // now enable blending and disable depth sorting so the font renders
  // correctly
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  // now loop for each of the char and draw our billboard
  int textLength=_text.length();
  float scale=1.0f;
  m_texVAO->bind();

  for ( int i = 0; i < textLength; ++i)
  {
  auto fc = m_characters.find(_text[i]);
  float xpos = _x + fc->second.bearingx * scale;
  float ypos = _y - (fc->second.sizey - fc->second.bearingy) * scale;

  float w = fc->second.sizex * scale;
  float h = fc->second.sizey * scale;
  // update VBO for each character
  float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 0.0f },            
      { xpos,     ypos,       0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 1.0f },

      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos + w, ypos,       1.0f, 1.0f },
      { xpos + w, ypos + h,   1.0f, 0.0f }           
  };

    // // bind the pre-generated texture
     glBindTexture(GL_TEXTURE_2D, fc->second.textureID);
    m_texVAO->setData(SimpleVAO::VertexData(sizeof(vertices),vertices[0][0],GL_DYNAMIC_DRAW));
    // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)
    m_texVAO->setVertexAttributePointer(0,4,GL_FLOAT,0,0);
    // say how many indices to be rendered
    m_texVAO->setNumIndices(6);
    m_texVAO->draw();
    _x += (fc->second.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
  }
    m_texVAO->unbind();

  // finally disable the blend and re-enable depth sort
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

}

//---------------------------------------------------------------------------
void Text::setScreenSize(int _w, int _h ) noexcept
{

  ShaderLib::use("nglTextShader");

  auto orth= ngl::ortho(0,_w,0,_h);
  ShaderLib::setUniform("projection",orth);
}

//---------------------------------------------------------------------------
// our text shader uses the alpha of the texture to modulate visibility
// when we render the text we use this colour passed to the shader
// it is default to black but this will change it
// the shader uses the following code

void Text::setColour(const Vec3 &_c ) noexcept
{
  // get shader instance
  ShaderLib::use("nglTextShader");
  // set the values
  ShaderLib::setUniform("textColour",_c.m_r,_c.m_g,_c.m_b);
}


//---------------------------------------------------------------------------
void Text::setColour(Real _r,  Real _g, Real _b) noexcept
{
  ShaderLib::use("nglTextShader");
  ShaderLib::setUniform("textColour",_r,_g,_b);
}

} //end namespace
//---------------------------------------------------------------------------

