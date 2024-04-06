#include "BufferTextures.h"

namespace ngl
{

std::unordered_map< std::string, BufferTexture > BufferTextures::s_texturebuffers;

size_t BufferTextures::numBuffers() noexcept
{
  return s_texturebuffers.size();
}

void BufferTextures::clear() noexcept
{
  for(auto &t : s_texturebuffers)
  {
    glDeleteBuffers(1, &t.second.id);
  }
  s_texturebuffers.clear();
}

}// end namespace ngl