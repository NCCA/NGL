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
#ifndef IMAGE_H_
#define IMAGE_H_
/// @file Image.h
/// @brief A generic Image loader / wrapper for different Image libs
/// this allows us to load an image to be used (for example) in the Texture class
/// as there are many different ways to do this this class has compile time options
/// to choose the image loading library to use At present support is going to be
/// QImage (for Qt builds) ImageMagic, OpenImageIO DevIL
/// Image data will be stored in either RGB or RGBA contiguos unsigned char data
#include "Types.h"
#include "Vec4.h"
#include <memory>
#include <string_view>
namespace ngl
{

class NGL_DLLEXPORT Image
{
  public:
  enum class ImageModes : char
    {
      RGB,
      RGBA
    };
    /// @brief default ctor
    Image() = default;
    /// @brief create empty image defaulting to RGBA and black
    Image(int _w, int _h, ImageModes _mode=ImageModes::RGBA );
    /// @brief ctor passing in filename
    /// @param _fname the name of the file to load.

    Image(std::string_view _fname,bool flipY=true);

    /// @brief copy ctor (does a deep copy so could be expensive)
    /// @param _i image to copy

    Image(const Image &_i);

    /// @brief dtor as we use a smart pointer the data will release automatically

    ~Image() = default;

    /// @brief load the image data, this will clear the previous data and attempt to load the new image data
    /// @param _fname name of the file to load
    /// @param _flipY flip the texture in the Y for OpenGL
    // this means 0,0 is bottom left of image
    /// @returns true is loaded ok, else false

    bool load(std::string_view _fname,bool _flipY=true) noexcept;
    /// @brief  save to file using current internal lib
    /// @param _fname name of file to save
    /// @param _flipY flip the texture in the Y for OpenGL
    // this means 0,0 is bottom left of image
    /// @return  true if file could be saved.
    bool save(std::string_view _fname,bool _flipY=true) const noexcept;


    /// @brief raw access to unsigned char pixel data
    /// @returns a pointer to the first image pixel element.

    unsigned char *getPixels() const noexcept
    {
      return m_data.get();
    }

    /// @brief save the FrameBuffer to file using current built in I/O
    /// @param _fname the name / path of the file to save
    /// @brief _x the x position into the framebuffer This location is the lower left corner of a rectangular block of pixels
    /// @brief _y the y position into the framebuffer This location is the lower left corner of a rectangular block of pixels
    /// @brief _width of the rectangle
    /// @brief _height the height of the rectangle
    /// @brief _mode RGB or RGBA image

    
    static void saveFrameBufferToFile(std::string_view _fname, int _x, int _y, int _width, int _height, ImageModes _mode = ImageModes::RGB);

    /// @brief Get the width of the texture
    /// @return width of the texture

    GLuint width() const noexcept
    {
      return m_width;
    }

    /// @brief Get the height of the texture
    /// @return height of the texture

    GLuint height() const noexcept
    {
      return m_height;
    }

    /// @brief Get the pixel format
    /// @return pixel format of the texture

    GLuint format() const noexcept
    {
      return m_format;
    }

    /// @brief gets the number of channels
    /// @return usually 3 (RGB) or 4 (RGBA) but can handle others depending on libl

    GLuint channels() const noexcept
    {
      return m_channels;
    }

    /// @brief set the colour value at position
    /// @param[in] _x the x position in the image
    /// @param[in] _y the y position in the image
    /// @param[in] _r the red pixel value
    /// @param[in] _g the green pixel value
    /// @param[in] _b the blue pixel value
    /// @param[in] _a the alpha pixel value
    void setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255) noexcept;

    /// @brief get the colour value from X,Y co-ordinates (image absolute 0,0 = top Left)
    /// @param[in] _x the x position in the image
    /// @param[in] _y the y position in the image

    Vec4 getColour(const GLuint _x, const GLuint _y) const noexcept;

    /// @brief get the colour value from X,Y co-ordinates in texture space
    /// @param[in] _uvX the x position in the image
    /// @param[in] _uvY the y position in the image

    Vec4 getColour(const Real _uvX, const Real _uvY) const noexcept;

    /// @brief print out info for the internal library being used.
    static void info();

private:
  /// @brief the actual image data loaded packed in r,g,b,(a) format in contiguous memory
  /// stored in a smart_pointer for safety

  std::unique_ptr< unsigned char[] > m_data;

  /// @brief the size of the image in the X direction

  GLuint m_width = 0;

  /// @brief the size of the image in the Y direction

  GLuint m_height = 0;

  /// @brief bits per pixel (RGB / RGBA)

  GLuint m_channels = 3;

  /// @brief image format, use GL types for this as we are going to use this class mainly for OpenGL

  GLuint m_format = GL_RGB;

  /// @brief loaded flag

  bool m_loaded = false;

  /// @brief do we have an alpha channel

  bool m_hasAlpha = false;
};

} // namespace ngl

#endif
