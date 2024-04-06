/*
Copyright (C) 2024 Jon Macey

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BUFFER_TEXTURE_H_
#define BUFFER_TEXTURE_H_
/// @file BufferTexture.h
/// @brief BufferTexture storage class
#include "Types.h"
#include <string>
#include <unordered_map>

namespace ngl
{

enum class GLTexBufferInternalFormat : GLenum
{
  R8 = GL_R8,
  R16 = GL_R16,
  R16F = GL_R16F,
  R32F = GL_R32F,
  R8I = GL_R8I,
  R16I = GL_R16I,
  R32I = GL_R32I,
  R8UI = GL_R8UI,
  R16UI = GL_R16UI,
  R32UI = GL_R32UI,
  RGB = GL_RG8,
  RB16 = GL_RG16,
  RG16F = GL_RG16F,
  RG32F = GL_RG32F,
  RG8I = GL_RG8I,
  RG16I = GL_RG16I,
  RG32I = GL_RG32I,
  RG8UI = GL_RG8UI,
  RG16UI = GL_RG16UI,
  RG32UI = GL_RG32UI,
  RGB32F = GL_RGB32F,
  RGB32I = GL_RGB32I,
  RGB32UI = GL_RGB32UI,
  RGBA8 = GL_RGBA8,
  RGBA16 = GL_RGBA16,
  RGBA16F = GL_RGBA16F,
  RGBA32F = GL_RGBA32F,
  RGB8I = GL_RGBA8I,
  RGBA16I = GL_RGBA16I,
  RGBA32I = GL_RGBA32I,
  RGBA8UI = GL_RGBA8UI,
  RGBA16UI = GL_RGBA16UI,
  RGBA32UI = GL_RGBA32UI
};

struct BufferTexture
{
  GLuint id;
  GLenum target;
  GLenum usage;
  GLTexBufferInternalFormat internalFormat;
  size_t size;
};

class BufferTextures
{
    public:
      static size_t numBuffers() noexcept;
      static void clear() noexcept;
    private:
  static std::unordered_map< std::string, BufferTexture > s_texturebuffers;
};
} // end namspace ngl
#endif