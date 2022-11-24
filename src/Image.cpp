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
#include "pystring.h"
#if defined(USEQIMAGE)
#include <QtGui/QImage>
#endif
#if defined(USEIMAGEMAGIC)
#include <ImageMagick-6/Magick++.h>
#endif
#if defined(USEOIIO)
#include <OpenImageIO/imageio.h>
#endif

#if defined(USEBUILTINIMAGE)
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../3rdparty/stb_image.h"
#include "../3rdparty/stb_image_write.h"
#endif

#include <iostream>

namespace ngl
{

#define IMAGE_DEBUG_ON 1

void Image::info()
{
#if defined(USEIMAGEMAGIC)
  NGLMessage::addMessage("Using Using Image Magick");
#endif
#if defined(USEOIIO)
  NGLMessage::addMessage("Using OpenImageIO");
#endif

#if defined(USEQIMAGE)
  NGLMessage::addMessage("Using QImage");

#endif

#if defined(USEBUILTINIMAGE)
  NGLMessage::addMessage("Using built in stb-image");
#endif

  NGLMessage::addMessage("Image Info END");
}

Image::Image(std::string_view _fname,bool _flipY)
{
  load(_fname,_flipY);
}

Image::Image(int _w, int _h, ImageModes _mode ) :m_width(_w),m_height(_h)
{
  if(_mode == ImageModes::RGBA)
  {
    m_channels=4;
    m_hasAlpha=true;
    m_format=GL_RGBA;
  }
  else
  {
    m_channels=3;
    m_hasAlpha=false;
    m_format=GL_RGB;
  }
  m_loaded=true;
  m_data=std::make_unique<unsigned char[]>(m_width*m_height*m_channels);

}

Image::Image(const Image &_i)
  : m_width(_i.m_width), m_height(_i.m_height), m_channels(_i.m_channels), m_format(_i.m_format), m_loaded(_i.m_loaded), m_hasAlpha(_i.m_hasAlpha)
{
  size_t size = m_width * m_height * m_channels;
  m_data.reset(new unsigned char[size]);
  memcpy(m_data.get(), _i.m_data.get(), size);
}

Vec4 Image::getColour(const GLuint _x, const GLuint _y) const noexcept
{
  // make sure were in the image range
  NGL_ASSERT(_x <= m_width && _y <= m_height);
  if(m_data != 0)
  {
    auto offset = _x * m_channels + ((_y)*m_width * m_channels);
    if(m_channels == 3)
    {
      return Vec4(m_data[offset], m_data[offset + 1], m_data[offset + 2]);
    }
    else
    {
      return Vec4(m_data[offset], m_data[offset + 1], m_data[offset + 2], m_data[offset + 3]);
    }
  }
  else
  {
    return Vec4(0, 0, 0, 0);
  }
}

Vec4 Image::getColour(const Real _uvX, const Real _uvY) const noexcept
{

  GLuint xx = static_cast< GLuint >(_uvX * (m_width - 1));
  GLuint yy = static_cast< GLuint >(_uvY * (m_height - 1));

  NGL_ASSERT(xx < m_width && yy < m_height);

  if(m_data != 0)
  {
    auto offset = xx * m_channels + (yy * m_width * m_channels);
    if(m_channels == 4)
    {
      return Vec4(m_data[offset], m_data[offset + 1], m_data[offset + 2], m_data[offset + 3]);
    }
    else
    {
      return Vec4(m_data[offset], m_data[offset + 1], m_data[offset + 2], 1.0);
    }
  }
  else
  {
    return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
  }
}
bool Image::save(std::string_view _fname,bool flipY) noexcept
{
 namespace ps=pystring;
 if((ps::endswith(std::string(_fname),".jpg") || ps::endswith(std::string(_fname),".jpeg")) &&
  m_channels == 4 )
 {
    ngl::NGLMessage::addWarning("Trying to save RGBA image as jpg which doesn't support it");
    

 }

#if defined(USEQIMAGE)
  QImage::Format qformat = QImage::Format::Format_RGB888;
  if(m_mode == ImageModes::RGBA)
  {
    qformat = QImage::Format::Format_RGBA8888;
  }
  QImage image(m_data.get(), m_width, m_height, qformat);
  image = image.mirrored(false, true);
  image.save(_fname.data());

#endif
#if defined(USEOIIO)
  using namespace OIIO;
  auto out = ImageOutput::create(_fname.data());
  ImageSpec spec(m_width, m_height, m_channels, TypeDesc::UINT8);
  out->open(_fname.data(), spec);
  if(flipY)
  {
    int scanlinesize = m_width * m_channels;
    // note this flips the image vertically on writing
    // (see http://www.openimageio.org/openimageio.pdf pg 20 for details)
    out->write_image(TypeDesc::UINT8, m_data.get() + (m_height - 1) * scanlinesize, AutoStride, -scanlinesize, AutoStride);
  }
  else
  {
    out->write_image(TypeDesc::UINT8, m_data.get() );
  }
  out->close();
#endif
#if defined(USEIMAGEMAGIC)
  Magick::Image output(m_width, m_height, m_channels == 3 ? "RGB" : "RGBA", Magick::CharPixel, m_data.get());

  // set the output image depth to 16 bit
  output.depth(16);
  // write the file
  output.write(_fname.data());
#endif

#if defined(USEBUILTINIMAGE)
  // TODO add check for extension and save what you can.
  stbi_write_png(_fname.data(), m_width, m_height, m_channels, m_data.get(), m_width * m_channels);
#endif
}


void Image::setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a ) noexcept
{
  size_t offset=(m_width * _y * m_channels) + (_x*m_channels);
  m_data[offset] = _r;
  m_data[offset+1] = _g;
  m_data[offset+2] = _b;
  if(m_channels == 4)
      m_data[offset+3] = _a;
}


void Image::saveFrameBufferToFile(std::string_view _fname, int _x, int _y, int _width, int _height, ImageModes _mode)
{
  GLenum format = GL_RGB;
  int size = 3;
  if(_mode == ImageModes::RGBA)
  {
    size = 4;
    format = GL_RGBA;
  }
  int realWidth = _width - _x;
  int realHeight = _height - _y;
  NGL_ASSERT(_x < _width && _y < _height);
  std::unique_ptr< unsigned char[] > data(new unsigned char[realWidth * realHeight * size]);
  glReadPixels(_x, _y, realWidth, realHeight, format, GL_UNSIGNED_BYTE, data.get());
#if defined(USEQIMAGE)
  QImage::Format qformat = QImage::Format::Format_RGB888;
  if(_mode == ImageModes::RGBA)
  {
    qformat = QImage::Format::Format_RGBA8888;
  }
  QImage image(data.get(), realWidth, realHeight, qformat);
  image = image.mirrored(false, true);
  image.save(_fname.data());

#endif
#if defined(USEOIIO)
  using namespace OIIO;
  auto out = ImageOutput::create(_fname.data());
  ImageSpec spec(realWidth, realHeight, size, TypeDesc::UINT8);
  int scanlinesize = realWidth * size;
  out->open(_fname.data(), spec);
  // note this flips the image vertically on writing
  // (see http://www.openimageio.org/openimageio.pdf pg 20 for details)
  out->write_image(TypeDesc::UINT8, data.get() + (realHeight - 1) * scanlinesize, AutoStride, -scanlinesize, AutoStride);
  out->close();
#endif
#if defined(USEIMAGEMAGIC)
  Magick::Image output(realWidth, realHeight, size == 3 ? "RGB" : "RGBA", Magick::CharPixel, data.get());

  // set the output image depth to 16 bit
  output.depth(16);
  // write the file
  output.write(_fname.data());
#endif

#if defined(USEBUILTINIMAGE)

  stbi_write_png(_fname.data(), _width, _height, size, data.get(), _width * size);
  // Magick::Image output(realWidth, realHeight, size == 3 ? "RGB" : "RGBA", Magick::CharPixel, data.get());

  // // set the output image depth to 16 bit
  // output.depth(16);
  // // write the file
  // output.write(_fname.c_str());
#endif
}

#if defined(USEQIMAGE)

//----------------------------------------------------------------------------------------------------------------------
// Qt Image loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load(std::string_view _fName) noexcept
{
#ifdef IMAGE_DEBUG_ON
  NGLMessage::addMessage("loading with QImage");
#endif
  QImage image;
  bool loaded = image.load(_fName.data());
  if(loaded == false)
  {
    NGLMessage::addError(fmt::format("error loading image {0} ", _fName.data()));
  }
  if(loaded == true)
  {
    image = image.mirrored();
    m_width = static_cast< GLuint >(image.width());
    m_height = static_cast< GLuint >(image.height());
    m_hasAlpha = image.hasAlphaChannel();
    if(m_hasAlpha == true)
    {
      m_channels = 4;
      m_format = GL_RGBA;
    }
    else
    {
      m_channels = 3;
      m_format = GL_RGB;
    }

    m_data.reset(new unsigned char[m_width * m_height * m_channels]);
    unsigned int index = 0;
    QRgb colour;
    for(unsigned int y = 0; y < m_height; ++y)
    {
      for(unsigned int x = 0; x < m_width; ++x)
      {
        colour = image.pixel(x, y);

        m_data[index++] = static_cast< unsigned char >(qRed(colour));
        m_data[index++] = static_cast< unsigned char >(qGreen(colour));
        m_data[index++] = static_cast< unsigned char >(qBlue(colour));
        if(m_hasAlpha)
        {
          m_data[index++] = static_cast< unsigned char >(qAlpha(colour));
        }
      }
    }
#ifdef IMAGE_DEBUG_ON

    NGLMessage::addMessage(fmt::format("size {0} x {1} channels {2}", m_width, m_height, m_channels), Colours::WHITE, TimeFormat::TIME);
#endif

    return true;
  }

  else
    return false;
}

#endif // end of QImage loading routines

#if defined(USEIMAGEMAGIC)

//----------------------------------------------------------------------------------------------------------------------
// Image Magick Image loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load(std::string_view _fname) noexcept
{
#ifdef IMAGE_DEBUG_ON
  NGLMessage::addMessage("loading with ImageMagick");
#endif
  Magick::Image image;
  Magick::Blob blob;

  try
  {
    image.read(_fname.data());
    // need to flip image as OpenGL uses textures starting the other way round.
    image.flip();
    image.write(&blob, "RGBA");
  }
  catch(Magick::Error &Error)
  {
    NGLMessage::addError(fmt::form("Error loading image {0} {1}", _fname.data(), Error.what()));
    return false;
  }
  m_width = image.columns();
  m_height = image.rows();
  m_channels = 4;
  m_format = GL_RGBA;
  m_data.reset(new unsigned char[m_width * m_height * m_channels]);
  // simple memcpy of the blob data to our internal data, not worrying about RGB/RGBA
  // here (as OpenGL doesn't really either).
  memcpy(m_data.get(), blob.data(), blob.length());
  return true;
}
#endif // end of image magick loading routines

#if defined(USEOIIO)

//----------------------------------------------------------------------------------------------------------------------
// Open Image I/O loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load(std::string_view _fname,bool _flipY) noexcept
{
  using namespace OIIO;

#ifdef IMAGE_DEBUG_ON
  NGLMessage::addMessage("loading with OpenImageIO");
  ;
#endif

  auto in = ImageInput::open(_fname.data());
  if(!in)
  {
    NGLMessage::addError(fmt::format("problem opening file {}", _fname));
    NGLMessage::addError(OIIO::geterror());
    return false;
  }
  auto spec = in->spec();
  m_width = spec.width;
  m_height = spec.height;
  m_channels = spec.nchannels;

  if(m_channels == 3)
    m_format = GL_RGB;
  else if(m_channels == 4)
    m_format = GL_RGBA;
  else if(m_channels == 1)
  {
    NGLMessage::addWarning("loading as greyscale");
    m_format = GL_RED;
  }
  m_data.reset(new unsigned char[m_width * m_height * m_channels]);
  // this will read an flip the pixel for OpenGL
  if(_flipY)
  {
  int scanlinesize = spec.width * spec.nchannels * sizeof(m_data[0]);
  in->read_image(TypeDesc::UINT8,
                 (char *)m_data.get() + (m_height - 1) * scanlinesize, // offset to last
                 AutoStride,                                           // default x stride
                 -scanlinesize,                                        // special y stride
                 AutoStride);                                          // default z stride
  }
  else
  {
    in->read_image (TypeDesc::UINT8, &m_data[0]);
  }
  in->close();
  return true;
}

#endif // end USEOIIO

#ifdef USEBUILTINIMAGE

// #define STB_IMAGE_IMPLEMENTATION
// #include "../3rdparty/stb_image.h"
bool Image::load(std::string_view _fname) noexcept
{
  const char *fname = _fname.data();
  int w, h, ch;
  stbi_set_flip_vertically_on_load(true);

  unsigned char *img = stbi_load(fname, &w, &h, &ch, 0);
#ifdef IMAGE_DEBUG_ON
  NGLMessage::addMessage("loading with Internal Image Libs");
#endif
  if(img != NULL)
  {
    NGLMessage::addMessage(fmt::format("loaded {} Width {} Height {} Channels {}", fname, w, h, ch));
    m_width = w;
    m_height = h;
    m_channels = ch;
    if(m_channels == 3)
      m_format = GL_RGB;
    else if(m_channels == 4)
      m_format = GL_RGBA;
    m_data.reset(new unsigned char[m_width * m_height * m_channels]);
    memcpy(m_data.get(), img, m_width * m_height * m_channels);
  }
  else
  {
    NGLMessage::addError("Image load failed this version only supports PNG,JPEG,GIF,TGA,BMP ");
    NGLMessage::addError("Have generated a Red Checkerboard pattern instead.");
    m_width = 1024;
    m_height = 1024;
    m_channels = 3;
    m_format = GL_RGB;
    m_data.reset(new unsigned char[m_width * m_height * m_channels]);
    size_t index = 0;
    constexpr float checkSize = 20;
    for(size_t y = 0; y < m_height; ++y)
    {
      for(size_t x = 0; x < m_width; ++x)
      {
        // index=(y * m_width) + x ;
        if(fmod(floor(checkSize * x / m_width) + floor(checkSize * y / m_height), 2.0f) < 1.0f)
        {
          m_data[index] = 255;
          m_data[index + 1] = 0;
          m_data[index + 2] = 0;
          index += 3;
        }
        else
        {
          m_data[index] = 255;
          m_data[index + 1] = 255;
          m_data[index + 2] = 255;
          index += 3;
        }
      }
    }
  }

  return true;
}
#endif
} // namespace ngl
