#include "BufferTextures.h"

namespace ngl
{

std::unordered_map< std::string, BufferTexture > BufferTextures::s_texturebuffers;

size_t BufferTextures::numBuffers() noexcept
{
  return s_texturebuffers.size();
}

}