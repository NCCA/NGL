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
#include <QtGui/QImage>
#include <QFontMetrics>
#include <QPainter>
#include <array>
#include <memory>
#include "Text.h"
#include "ShaderLib.h"

namespace ngl
{


//---------------------------------------------------------------------------
/// @brief code taken from here http://jeffreystedfast.blogspot.com/2008/06/calculating-nearest-power-of-2.html
/// @param _num the number we wish to get the nearest power from
// OpenGL needs textures to be in powers of two, this function will get the
// nearest power of two to the current value passed in
//---------------------------------------------------------------------------
unsigned int nearestPowerOfTwo ( unsigned int _num )
{
    unsigned int j, k;
    (j = _num & 0xFFFF0000) || (j = _num);
    (k = j & 0xFF00FF00) || (k = j);
    (j = k & 0xF0F0F0F0) || (j = k);
    (k = j & 0xCCCCCCCC) || (k = j);
    (j = k & 0xAAAAAAAA) || (j = k);
    return j << 1;
}
// end citation

//---------------------------------------------------------------------------
Text::Text( const QFont &_f)  noexcept
{

  // so first we grab the font metric of the font being used
  QFontMetrics metric(_f);
  // this allows us to get the height which should be the same for all
  // fonts of the same class as this is the total glyph height
  int fontHeight=metric.height();

  // loop for all basic keyboard chars we will use space to ~
  // should really change this to unicode at some stage
  const static char startChar=' ';
  const static char endChar='~';
  // Most OpenGL cards need textures to be in powers of 2 (128x512 1024X1024 etc etc) so
  // to be safe we will conform to this and calculate the nearest power of 2 for the glyph height
  // we will do the same for each width of the font below
  unsigned int heightPow2=nearestPowerOfTwo(fontHeight);

  // we are now going to create a texture / billboard for each font
  // they will be the same height but will possibly have different widths
  // as some of the fonts will be the same width, to save VAO space we will only create
  // a vao if we don't have one of the set width. To do this we use the has below
  QHash <int,AbstractVAO *> widthVAO;

  for(char c=startChar; c<=endChar; ++c)
  {
    QChar ch(c);
    FontChar fc;
    // get the width of the font and calculate the ^2 size
    int width=metric.width(c);
    unsigned int widthPow2=nearestPowerOfTwo(width);
    // now we set the texture co-ords for our quad it is a simple
    // triangle billboard with tex-cords as shown
    //  s0/t0  ---- s1,t0
    //         |\ |
    //         | \|
    //  s0,t1  ---- s1,t1
    // each quad will have the same s0 and the range s0-s1 == 0.0 -> 1.0
    Real s0=0.0;
    // we now need to scale the tex cord to it ranges from 0-1 based on the coverage
    // of the glyph and not the power of 2 texture size. This will ensure that kerns
    // / ligatures match
    Real s1=width*1.0f/widthPow2;
    // t0 will always be the same
    Real t0=0.0f;
    // this will scale the height so we only get coverage of the glyph as above
    Real t1=metric.height()*-1.0f/heightPow2;
    // we need to store the font width for later drawing
    fc.width=width;
    // now we will create a QImage to store the texture, basically we are going to draw
    // into the qimage then save this in OpenGL format and load as a texture.
    // This is relativly quick but should be done as early as possible for max performance when drawing
    QImage finalImage(nearestPowerOfTwo(width),nearestPowerOfTwo(fontHeight),QImage::Format_ARGB32);
    // set the background for transparent so we can avoid any areas which don't have text in them
    finalImage.fill(Qt::transparent);
    // we now use the QPainter class to draw into the image and create our billboards
    QPainter painter;
    painter.begin(&finalImage);
    // try and use high quality text rendering (works well on the mac not as good on linux)
    painter.setRenderHints(QPainter::HighQualityAntialiasing
                   | QPainter::TextAntialiasing);
    // set the font to draw with
    painter.setFont(_f);
    // we set the glyph to be drawn in black the shader will override the actual colour later
    // see TextShader.h in src/shaders/
    painter.setPen(Qt::black);
    // finally we draw the text to the Image
    painter.drawText(0, metric.ascent(), QString(c));
    painter.end();
    // for debug purposes we can save the files as .png and view them
    // not needed just useful when developing the class/
    /*
    QString filename=".png";
    filename.prepend(c);
    finalImage.save(filename);
    */

    // now we create the OpenGL texture ID and bind to make it active
    glGenTextures(1, &fc.textureID);
    glBindTexture(GL_TEXTURE_2D, fc.textureID);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);


    // QImage has a method to convert itself to a format suitable for OpenGL
    finalImage=finalImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    // set rgba image data
    int widthTexture=finalImage.width();
    int heightTexture=finalImage.height();
    std::unique_ptr<unsigned char []> data(new unsigned char[ widthTexture*heightTexture * 4]);
    unsigned int index=0;
    QRgb colour;
    for(int y=heightTexture-1; y>0; --y)
    {
      for(int x=0; x<widthTexture; ++x)
      {
        colour=finalImage.pixel(x,y);
        data[index++]=static_cast<unsigned char>(qRed(colour));
        data[index++]=static_cast<unsigned char>(qGreen(colour));
        data[index++]=static_cast<unsigned char>(qBlue(colour));
        data[index++]=static_cast<unsigned char>(qAlpha(colour));
        }
    }



    // the image in in RGBA format and unsigned byte load it ready for later
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTexture, heightTexture,0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
    glGenerateMipmap(GL_TEXTURE_2D);

    // see if we have a Billboard of this width already
    if (!widthVAO.contains(width))
    {
        // this structure is used by the VAO to store the data to be uploaded
        // for drawing the quad
        struct textVertData
        {
        Real x;
        Real y;
        Real u;
        Real v;
        };
        // we are creating a billboard with two triangles so we only need the
        // 6 verts, (could use index and save some space but shouldn't be too much of an
        // issue
        std::array<textVertData,6> d;
        // load values for triangle 1
        d[0].x=0;
        d[0].y=0;
        d[0].u=s0;
        d[0].v=t0;

        d[1].x=fc.width;
        d[1].y=0;
        d[1].u=s1;
        d[1].v=t0;

        d[2].x=0;
        d[2].y=fontHeight;
        d[2].u=s0;
        d[2].v=t1;
        // load values for triangle two
        d[3].x=0;
        d[3].y=0+fontHeight;
        d[3].u=s0;
        d[3].v=t1;


        d[4].x=fc.width;
        d[4].y=0;
        d[4].u=s1;
        d[4].v=t0;


        d[5].x=fc.width;
        d[5].y=fontHeight;
        d[5].u=s1;
        d[5].v=t1;


        // now we create a VAO to store the data
        AbstractVAO *vao=VAOFactory::createVAO("simpleVAO",GL_TRIANGLES);
        // bind it so we can set values
        vao->bind();
        // set the vertex data (2 for x,y 2 for u,v)
        vao->setData(SimpleVAO::VertexData(6*sizeof(textVertData),d[0].x));
        // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)
        vao->setVertexAttributePointer(0,2,GL_FLOAT,sizeof(textVertData),0);
        // We can now create another set of data (which will be added to the VAO)
        // in this case the UV co-ords
        // now we set this as the 2nd attribute pointer (1) to match inUV in the shader
        vao->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(textVertData),2);
        // say how many indecis to be rendered
        vao->setNumIndices(6);

        // now unbind
        vao->unbind();
        // store the vao pointer for later use in the draw method
        fc.vao =vao;
        widthVAO[width]=vao;
    }
    else
    {
      fc.vao=widthVAO[width];
    }
    // finally add the element to the map, this must be the last
    // thing we do
    m_characters[c]=std::move(fc);
  }
  std::cout<<"created "<<widthVAO.size()<<" unique billboards\n";
  // set a default colour (black) incase user forgets
  this->setColour(0,0,0);
  this->setTransform(1.0,1.0);
}


//---------------------------------------------------------------------------
Text::~Text()
{
  // our dtor should clear out the textures and remove the VAO's
  for( auto &m : m_characters)
  {
    glDeleteTextures(1,&m.textureID);
    m.vao->removeVAO();
  }

}




//---------------------------------------------------------------------------
void Text::renderText( float _x, float _y,  const QString &text ) const noexcept
{
  // make sure we are in texture unit 0 as this is what the
  // shader expects
  glActiveTexture(GL_TEXTURE0);
  // grab an instance of the shader manager
  ShaderLib *shader=ShaderLib::instance();
  // use the built in text rendering shader
  (*shader)["nglTextShader"]->use();
  // the y pos will always be the same so set it once for each
  // string we are rendering
  shader->setRegisteredUniform1f("ypos",_y);
  // now enable blending and disable depth sorting so the font renders
  // correctly
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // now loop for each of the char and draw our billboard
  int textLength=text.length();

  for ( int i = 0; i < textLength; ++i)
  {
    // set the shader x position this will change each time
    // we render a glyph by the width of the char
    shader->setRegisteredUniform1f("xpos",_x);
    // so find the FontChar data for our current char
//    FontChar f = m_characters[text[i].toAscii()];
    FontChar f = m_characters[text[i].toLatin1()];

    // bind the pre-generated texture
    glBindTexture(GL_TEXTURE_2D, f.textureID);
    // bind the vao
    f.vao->bind();
    // draw
    f.vao->draw();
    // now unbind the vao
    f.vao->unbind();
    // finally move to the next glyph x position by incrementing
    // by the width of the char just drawn
    _x+=f.width;

  }
  // finally disable the blend and re-enable depth sort
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

}

//---------------------------------------------------------------------------
void Text::setScreenSize(int _w, int _h ) noexcept
{

  float scaleX=2.0f/_w;
  float scaleY=-2.0f/_h;
  // in shader we do the following code to transform from
  // x,y to NDC
  // gl_Position=vec4( ((xpos+inVert.x)*scaleX)-1,((ypos+inVert.y)*scaleY)+1.0,0.0,1.0); "
  // so all we need to do is calculate the scale above and pass to shader every time the
  // screen dimensions change
  ShaderLib *shader=ShaderLib::instance();
  (*shader)["nglTextShader"]->use();

  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);
}

//---------------------------------------------------------------------------
// our text shader uses the alpha of the texture to modulate visibility
// when we render the text we use this colour passed to the shader
// it is default to black but this will change it
// the shader uses the following code
// vec4 text=texture(tex,vertUV.st);
// fragColour.rgb=textColour.rgb;
// fragColour.a=text.a;

void Text::setColour(const Colour &_c ) noexcept
{
  // get shader instance
  ShaderLib *shader=ShaderLib::instance();
  // make current shader active
  (*shader)["nglTextShader"]->use();
  // set the values
  shader->setRegisteredUniform3f("textColour",_c.m_r,_c.m_g,_c.m_b);
}


//---------------------------------------------------------------------------
void Text::setColour(Real _r,  Real _g, Real _b) noexcept
{

  ShaderLib *shader=ShaderLib::instance();
  (*shader)["nglTextShader"]->use();

  shader->setRegisteredUniform3f("textColour",_r,_g,_b);
}

void Text::setTransform(float _x, float _y) noexcept
{

  ShaderLib *shader=ShaderLib::instance();
  (*shader)["nglTextShader"]->use();

  shader->setRegisteredUniform2f("transform",_x,_y);
}


} //end namespace
//---------------------------------------------------------------------------

