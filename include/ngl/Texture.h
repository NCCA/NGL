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
#ifndef TEXTURE_H_
#define TEXTURE_H_
/// @file Texture.h
/// @brief a simple texture loader / GL texture object
#include "Image.h"
#include "Types.h"
#include <string_view>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @file Texture.h
/// @class Texture "include/ngl/Texture.h"
/// @brief simple texture object using QImage to load and convert to
/// OpenGL texturing, needs loads of work for multi texture support etc
/// as well as different texture types
/// @author Jonathan Macey
/// @version 2.0
/// @date 18/3/10 Added multi texture support
/// @todo make it more flexible for different types of texture operations
/// @todo write save method at some stage as well this could grab info from framebuffer and replace the frame
/// writer class
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Texture
{
    public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor using no parameters
  //----------------------------------------------------------------------------------------------------------------------
  Texture() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  destructor
  //----------------------------------------------------------------------------------------------------------------------
  ~Texture() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  make not copyable
  //----------------------------------------------------------------------------------------------------------------------
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor passing the file to load
  /// @param[in] &_fName the name of the file to load
  //----------------------------------------------------------------------------------------------------------------------
  Texture(std::string_view _fname);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load the image file into the texture class
  /// @param[in] _fName the name of the file to load
  /// imageMagick will determine if it can load the file
  /// @returns true on success else false if load fails
  //----------------------------------------------------------------------------------------------------------------------
  bool loadImage(std::string_view _fname);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to access the pixel data pointer
  /// @returns  reference to the pixel data
  //----------------------------------------------------------------------------------------------------------------------
  unsigned char *getPixels() const
  {
    return m_image.getPixels();
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the image as an OpenGL texture object
  /// @returns the texture object id
  //----------------------------------------------------------------------------------------------------------------------
  GLuint setTextureGL() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the texture object to be different texture in multitexture
  /// @param _id the texture id
  //----------------------------------------------------------------------------------------------------------------------
  void setMultiTexture(const GLint _id) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the width of the texture
  /// @return width of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint width() const noexcept
  {
    return m_width;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the height of the texture
  /// @return height of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint height() const noexcept
  {
    return m_height;
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the pixel format
  /// @return pixel format of the texture
  //----------------------------------------------------------------------------------------------------------------------
  GLuint format() const noexcept
  {
    return m_format;
  }

  const Image &getImage() const
  {
    return m_image;
  }

    protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the actual image data loaded packed in r,g,b,a format in contiguous memory
  /// stored in a smart_pointer for safety
  //----------------------------------------------------------------------------------------------------------------------
  Image m_image;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the size of the image in the X direction
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_width = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the size of the image in the Y direction
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_height = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief A pointer to the start of the image data
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_channels = 3;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the MultiTexture ID for the current texture Object
  //----------------------------------------------------------------------------------------------------------------------
  GLint m_multiTextureID = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the image format (i.e rgb or rgba)
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_format = GL_RGB;
};

} // namespace ngl
#endif
//----------------------------------------------------------------------------------------------------------------------
