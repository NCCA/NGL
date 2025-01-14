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
#include <iostream>

#include "Image.h"
#include "NGLassert.h"
#include "pystring.h"

enum class ImageLibrary : char { QImage, OIIO, BuiltIn };

#if defined(USEQIMAGE)
  const ImageLibrary g_imageLib = ImageLibrary::QImage;
  #include <QtGui/QImage>
#elif defined(USEOIIO)
  const ImageLibrary g_imageLib = ImageLibrary::OIIO;
  #include <OpenImageIO/imageio.h>
#elif defined(USEBUILTINIMAGE)
  const ImageLibrary g_imageLib = ImageLibrary::BuiltIn;
  #define STB_IMAGE_IMPLEMENTATION
  #define STB_IMAGE_WRITE_IMPLEMENTATION

  #include "../3rdparty/stb_image.h"
  #include "../3rdparty/stb_image_write.h"
#endif



namespace ngl
{

void Image::info()
{
if constexpr (g_imageLib == ImageLibrary::QImage)
{
  NGLMessage::addMessage("Using QImage");
}
else if constexpr (g_imageLib == ImageLibrary::OIIO)
{
  NGLMessage::addMessage("Using OpenImageIO");
}
else if constexpr (g_imageLib == ImageLibrary::BuiltIn)
{
  NGLMessage::addMessage("Using built in stb-image");
}
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
  NGL_ASSERT(_x <= m_width && _y <= m_height)
  if(m_data != nullptr)
  {
    auto offset = _x * m_channels + (_y*m_width * m_channels);
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

  auto xx = static_cast< GLuint >(_uvX * (m_width - 1));
  auto yy = static_cast< GLuint >(_uvY * (m_height - 1));

  NGL_ASSERT(xx < m_width && yy < m_height)

  if(m_data != nullptr)
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
bool Image::save(std::string_view _fname,bool _flipY) const noexcept
{
 bool isSaved=false;
 namespace ps=pystring;
 if((ps::endswith(std::string(_fname),".jpg") || ps::endswith(std::string(_fname),".jpeg")) &&
  m_channels == 4 )
 {
    ngl::NGLMessage::addWarning("Trying to save RGBA image as jpg which doesn't support it");
 }

#if defined(USEQIMAGE)
  QImage image(m_data.get(), m_width, m_height, m_channels==4 ? QImage::Format::Format_RGBA8888 : QImage::Format::Format_RGB888);
  image = image.mirrored(false, _flipY);
  image.save(_fname.data());

#endif
#if defined(USEOIIO)
  using namespace OIIO;
  auto out = ImageOutput::create(_fname.data());
  ImageSpec spec(m_width, m_height, m_channels, TypeDesc::UINT8);
  isSaved=out->open(_fname.data(), spec);
  if(_flipY)
  {
    int scanlinesize = m_width * m_channels;
    // note this flips the image vertically on writing
    // (see http://www.openimageio.org/openimageio.pdf pg 20 for details)
    isSaved=out->write_image(TypeDesc::UINT8, m_data.get() + (m_height - 1) * scanlinesize, AutoStride, -scanlinesize, AutoStride);
  }
  else
  {
    isSaved=out->write_image(TypeDesc::UINT8, m_data.get() );
  }
  out->close();
#endif

#if defined(USEBUILTINIMAGE)
  stbi_flip_vertically_on_write(int(_flipY));
  if(ps::endswith(std::string(_fname.data()),".png"))
    isSaved=stbi_write_png(_fname.data(), m_width, m_height, m_channels, m_data.get(), m_width * m_channels);
  else if(ps::endswith(std::string(_fname.data()),".tga"))
    isSaved=stbi_write_tga(_fname.data(), m_width, m_height, m_channels, m_data.get());
  else if(ps::endswith(std::string(_fname.data()),".bmp"))
    isSaved=stbi_write_bmp(_fname.data(), m_width, m_height, m_channels, m_data.get());
  else if(ps::endswith(std::string(_fname.data()),".jpg"))
    isSaved=stbi_write_jpg(_fname.data(), m_width, m_height, m_channels, m_data.get(),100);
  

#endif
return isSaved;
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
  NGL_ASSERT(_x < _width && _y < _height)
  auto data = std::make_unique<unsigned char []>(realWidth * realHeight * size);
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


#if defined(USEBUILTINIMAGE)

  stbi_write_png(_fname.data(), _width, _height, size, data.get(), _width * size);
#endif
}

#if defined(USEQIMAGE)

//----------------------------------------------------------------------------------------------------------------------
// Qt Image loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load(std::string_view _fName,bool _flipY) noexcept
{

  QImage image;
  bool loaded = image.load(_fName.data());
  image = image.mirrored(false, _flipY);

  if(loaded == false)
  {
    NGLMessage::addError(fmt::format("error loading image {0} ", _fName.data()));
  }
  if(loaded == true)
  {
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

    return true;
  }

  else
    return false;
}

#endif // end of QImage loading routines

#if defined(USEOIIO)

//----------------------------------------------------------------------------------------------------------------------
// Open Image I/O loading routines
//----------------------------------------------------------------------------------------------------------------------
bool Image::load(std::string_view _fname,bool _flipY) noexcept
{
  using namespace OIIO;


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
  in->read_image(0,0,0,-1,TypeDesc::UINT8,
                 (char *)m_data.get() + (m_height - 1) * scanlinesize, // offset to last
                 AutoStride,                                           // default x stride
                 -scanlinesize,                                        // special y stride
                 AutoStride);                                          // default z stride
  }
  else
  {
    in->read_image (0,0,0,-1,TypeDesc::UINT8, &m_data[0]);
  }
  in->close();
  return true;
}

#endif // end USEOIIO

#ifdef USEBUILTINIMAGE

bool Image::load(std::string_view _fname,bool _flipY) noexcept
{
  const char *fname = _fname.data();
  int w;
  int h;
  int ch;
  stbi_set_flip_vertically_on_load(_flipY);

  if(const unsigned char *img = stbi_load(fname, &w, &h, &ch, 0); img != nullptr)
  {
    NGLMessage::addMessage(fmt::format("loaded {} Width {} Height {} Channels {}", fname, w, h, ch));
    m_width = w;
    m_height = h;
    m_channels = ch;
    if(m_channels == 3)
    {
        m_format = GL_RGB;
    }
    else if(m_channels == 4)
    {
        m_format = GL_RGBA;
    }
    m_data=std::make_unique< unsigned char []>(m_width * m_height * m_channels);
    memcpy(m_data.get(), img, m_width * m_height * m_channels);
    return true;
  }
  else if(img == nullptr)
  {
    NGLMessage::addError("Image load failed this version only supports PNG,JPEG,GIF,TGA,BMP ");
    NGLMessage::addError("Have generated a Red Checkerboard pattern instead.");
    m_width = 1024;
    m_height = 1024;
    m_channels = 3;
    m_format = GL_RGB;
    m_data= std::make_unique<unsigned char []>(m_width * m_height * m_channels);
    size_t index = 0;
    constexpr float checkSize = 20;
    for(GLuint y = 0; y < m_height; ++y)
    {
      for(GLuint x = 0; x < m_width; ++x)
      {
        if(fmod(floor(checkSize * x / static_cast<float>(m_width)) + floor(checkSize * y / static_cast<float>(m_height)), 2.0f) < 1.0f)
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
    return true;

  }
  else
  {
    return false;
  }
  
}
#endif
} // namespace ngl
