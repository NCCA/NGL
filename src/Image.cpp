/*
  Copyright (C) 2015 Jon Macey

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
/// @file Image.cpp
/// @brief implementation files for Image class
//----------------------------------------------------------------------------------------------------------------------
#include "Image.h"

#if defined(USEQIMAGE)
  #include <QtGui/QImage>
#endif
#if defined(USEIMAGEMAGIC)
  #include <ImageMagick/Magick++.h>
#endif


#include <iostream>

namespace ngl
{


Image::Image() : m_width(0),m_height(0),m_bpp(0),m_format(GL_RGBA),m_loaded(false),m_hasAlpha(true){;}

Image::Image(const std::string &_fname)
{
  load(_fname);
}


#if defined(USEQIMAGE)

//----------------------------------------------------------------------------------------------------------------------
// Qt Image loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load( const std::string &_fName  )
{
  QImage *image = new QImage();
  bool loaded=image->load(_fName.c_str());
  if(loaded ==false)
  {
    std::cerr<<"error loading image "<<_fName.c_str()<<"\n";
  }
  if(loaded == true)
  {
    m_width=image->width();
    m_height=image->height();
    m_hasAlpha=image->hasAlphaChannel();
    if(m_hasAlpha == true)
    {
      m_bpp=4;
      m_format = GL_RGBA;
    }
    else
    {
      m_bpp=3;
      m_format = GL_RGB;
    }

    m_data.reset(new unsigned char[ m_width*m_height*m_bpp]);
    unsigned int index=0;
    QRgb colour;
    for(unsigned int y=m_height-1; y>0; y--)
    {
      for(unsigned int x=0; x<m_width; ++x)
      {
        colour=image->pixel(x,y);

        m_data[index++]=qRed(colour);
        m_data[index++]=qGreen(colour);
        m_data[index++]=qBlue(colour);
        if(m_hasAlpha)
        {
          m_data[index++]=qAlpha(colour);
        }
      }
    }

   return true;

  }

  else return false;
}

#endif

}
