#include <gtest/gtest.h>
#include <ngl/ShaderLib.h>


TEST(ShaderLib,instance)
{
  auto shader = ngl::ShaderLib::instance();
  EXPECT_TRUE(shader !=nullptr);
}
