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
#if defined(USEOIIO)
  #include <OpenImageIO/imageio.h>
#endif

#include <iostream>

namespace ngl
{

#define IMAGE_DEBUG_ON 1

Image::Image() : m_width(0),m_height(0),m_channels(0),m_format(GL_RGBA),m_loaded(false),m_hasAlpha(true){;}

Image::Image(const std::string &_fname)
{
	load(_fname);
}

Image::Image(const Image &_i) :m_width(_i.m_width),m_height(_i.m_height),
															 m_channels(_i.m_channels),m_format(_i.m_format),
															 m_loaded(_i.m_loaded),m_hasAlpha(_i.m_hasAlpha)
{
	size_t size=m_width*m_height*m_channels;
	m_data.reset(new unsigned char[ size]);
	memcpy(m_data.get(),_i.m_data.get(),size);

}

Colour Image::getColour(const GLuint _x,const GLuint _y ) const
{
// make sure were in the image range
	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		int offset=_x*m_channels+((_y)*m_width*m_channels);
		if(m_channels == 3)
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
    int offset = xx * m_channels + (yy * m_width * m_channels );
    if(m_channels == 4)
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
#ifdef IMAGE_DEBUG_ON
  std::cerr<<"loading with QImage"<<std::endl;
#endif
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
      m_channels=4;
      m_format = GL_RGBA;
    }
    else
    {
      m_channels=3;
      m_format = GL_RGB;
    }

    m_data.reset(new unsigned char[ m_width*m_height*m_channels]);
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
  #ifdef IMAGE_DEBUG_ON
  std::cerr<<"loading with ImageMagick"<<std::endl;
  #endif
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
  m_channels=4;
  m_format=GL_RGBA;
  m_data.reset(new unsigned char[ m_width*m_height*m_channels]);
  // simple memcpy of the blob data to our internal data, not worrying about RGB/RGBA
  // here (as OpenGL doesn't really either).
  memcpy(m_data.get(),blob.data(),blob.length());
}
#endif // end of image magick loading routines

#if defined(USEOIIO)

//----------------------------------------------------------------------------------------------------------------------
// Open Image I/O loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load( const std::string &_fname  )
{
#ifdef IMAGE_DEBUG_ON
  std::cerr<<"loading with OpenImageIO"<<std::endl;
#endif
  OpenImageIO::ImageInput *in = OpenImageIO::ImageInput::open (_fname);
  if (! in)
  {
    return false;
  }
  const OpenImageIO::ImageSpec &spec = in->spec();
  m_width = spec.width;
  m_height = spec.height;
  m_channels = spec.nchannels;
  if(m_channels==3)
    m_format=GL_RGB;
  else if(m_channels==4)
    m_format=GL_RGBA;
  m_data.reset(new unsigned char[ m_width*m_height*m_channels]);
  in->read_image (OpenImageIO::TypeDesc::UINT8, &m_data[0]);
  in->close ();
  delete in;
  return true;
}


#endif // end USEOIIO


} // end of namespace
