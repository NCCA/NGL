#include <gtest/gtest.h>
#include <ngl/BufferTextures.h>

TEST(BufferTextures,construct)
{
  EXPECT_EQ(ngl::BufferTextures::numBuffers(),0);
}

