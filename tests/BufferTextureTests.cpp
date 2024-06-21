#include <gtest/gtest.h>
#include <ngl/BufferTextures.h>

TEST(BufferTextures,construct)
{
  ngl::BufferTextures::clear();
  EXPECT_EQ(ngl::BufferTextures::numBuffers(),0);
}

TEST(BufferTextures,add)
{
ngl::BufferTextures::clear();

}