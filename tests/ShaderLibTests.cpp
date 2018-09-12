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

TEST(ShaderLib,useNull)
{
  auto shader = ngl::ShaderLib::instance();
  shader->use("Foo");
  EXPECT_TRUE(shader->getCurrentShaderName()=="NULL");
}


TEST(ShaderLib,loadErrorShader)
{
  auto shader = ngl::ShaderLib::instance();
  EXPECT_FALSE(shader->loadShader("Test","files/vertErr.glsl","files/fragErr.glsl","",false));
}

TEST(ShaderLib,loadParts)
{

  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Test2",false);
  constexpr auto Vertex="Test2Vert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX );
  shader->loadShaderSource(Vertex,"files/vert.glsl");
  EXPECT_TRUE(shader->compileShader(Vertex))<<"error compiling vert shader";

  constexpr auto Fragment="Test2Frag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT );
  shader->loadShaderSource(Fragment,"files/frag.glsl");
  EXPECT_TRUE(shader->compileShader(Fragment))<<"error compiling vert shader";
  EXPECT_TRUE(shader->linkProgramObject("Test2"));
  (*shader)["Test2"]->use();
  EXPECT_TRUE(shader->getCurrentShaderName()=="Test2");
}

TEST(ShaderLib,loadPartsFailVertex)
{

  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Test3",false);
  constexpr auto Vertex="Test3Vert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX ,false);
  shader->loadShaderSource(Vertex,"files/vertErr.glsl");
  EXPECT_FALSE(shader->compileShader(Vertex))<<"error compiling vert shader";


}

TEST(ShaderLib,loadPartsFailFragment)
{
  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Test4",false);
  constexpr auto Fragment="Test4Frag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT ,false);
  shader->loadShaderSource(Fragment,"files/fragErr.glsl");
  EXPECT_FALSE(shader->compileShader(Fragment))<<"error compiling vert shader";

}


TEST(ShaderLib,failLink)
{
  constexpr auto *shaderName="Test5";
  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram(shaderName,false);
  constexpr auto Vertex="Test5Vert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX );
  shader->loadShaderSource(Vertex,"files/vertLinkErr.glsl");
  EXPECT_TRUE(shader->compileShader(Vertex))<<"error compiling vert shader";

  constexpr auto Fragment="Test5Frag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT );
  shader->loadShaderSource(Fragment,"files/fragLinkErr.glsl");
  EXPECT_TRUE(shader->compileShader(Fragment))<<"error compiling vert shader";

  shader->attachShaderToProgram(shaderName,Vertex);
  shader->attachShaderToProgram(shaderName,Fragment);
  EXPECT_FALSE(shader->linkProgramObject(shaderName));
}

