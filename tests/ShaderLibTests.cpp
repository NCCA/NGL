#include <gtest/gtest.h>
#include <ngl/ShaderLib.h>


TEST(ShaderLib,instance)
{
  auto shader = ngl::ShaderLib::instance();
  EXPECT_TRUE(shader !=nullptr);
  // we have Colour, Text, Diffuse and Checker (but vert and frag) so 8 shaders in total
  EXPECT_TRUE(shader->getNumShaders() ==8);
}

TEST(ShaderLib,loadShader)
{
  auto shader = ngl::ShaderLib::instance();
  EXPECT_TRUE(shader->loadShader("Test","files/vert.glsl","files/frag.glsl"));
}

TEST(ShaderLib,use)
{
  auto shader = ngl::ShaderLib::instance();
  shader->use("Test");
  EXPECT_TRUE(shader->getCurrentShaderName()=="Test");
}

TEST(ShaderLib,loadErrorShader)
{
  auto shader = ngl::ShaderLib::instance();
//  shader->loadShader("Test","files/vertErr.glsl","files/fragErr.glsl");

}
