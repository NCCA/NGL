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
#include "NGLassert.h"

#if defined(USEQIMAGE)
  #include <QtGui/QImage>
#endif
#if defined(USEIMAGEMAGIC)
  #include <ImageMagick-6/Magick++.h>
#endif


#include <iostream>

namespace ngl
{


Image::Image() : m_width(0),m_height(0),m_bpp(0),m_format(GL_RGBA),m_loaded(false),m_hasAlpha(true){;}

Image::Image(const std::string &_fname)
{
	load(_fname);
}

Colour Image::getColour(const GLuint _x,const GLuint _y ) const
{
// make sure were in the image range
	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		int offset=_x*m_bpp+((_y)*m_width*m_bpp);
		if(m_bpp == 3)
		{
		return Colour(m_data[offset],m_data[offset+1],m_data[offset+2]);
		}
		else
		{
		return Colour(m_data[offset],m_data[offset+1],m_data[offset+2],m_data[offset+3]);
		}
	}
	else
	{
		return Colour(0,0,0,0);
	}
}


Colour Image::getColour(const Real _uvX, const Real _uvY ) const
{

  GLuint xx = _uvX * (m_width-1);
  GLuint yy = _uvY * (m_height-1);

  NGL_ASSERT(xx<m_width && yy<m_height);

  if(m_data!=0)
  {
    int offset = xx * m_bpp + (yy * m_width * m_bpp );
    if(m_bpp == 4)
    {
      return Colour(m_data[offset],m_data[offset+1],m_data[offset+2],m_data[offset+3]);
    }
    else
    {
      return Colour(m_data[offset],m_data[offset+1],m_data[offset+2],1.0);
    }
  }
  else
  {
    return Colour(0,0,0,0);
  }
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
    for(unsigned int y=0; y<m_height; ++y)
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

#endif // end of QImage loading routines


#if defined(USEIMAGEMAGIC)

//----------------------------------------------------------------------------------------------------------------------
// Image Magick Image loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load( const std::string &_fname  )
{
  Magick::Image image;
  Magick::Blob blob;

  try
  {
    image.read(_fname);
    image.write(&blob, "RGBA");
  }
  catch (Magick::Error& Error)
  {
  std::cout << "Error loading texture '" << _fname << "': " << Error.what() << std::endl;
  return false;
  }
  m_width=image.columns();
  m_height=image.rows();
  m_bpp=4;
  m_format=GL_RGBA;
  m_data.reset(new unsigned char[ m_width*m_height*m_bpp]);
  memcpy(m_data.get(),blob.data(),blob.length());
}
#endif // end of image magick loading routines




} // end of namespace
