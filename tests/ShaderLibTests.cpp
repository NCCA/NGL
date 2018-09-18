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
  EXPECT_FALSE(shader->loadShader("Test","files/vertErr.glsl","files/fragErr.glsl",ngl::ErrorExit::OFF));
}

TEST(ShaderLib,loadParts)
{

  auto shader = ngl::ShaderLib::instance();
  auto *shaderName="Test2";

  shader->createShaderProgram(shaderName,ngl::ErrorExit::OFF);
  constexpr auto Vertex="Test2Vert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX );
  shader->loadShaderSource(Vertex,"files/vert.glsl");
  EXPECT_TRUE(shader->compileShader(Vertex))<<"error compiling vert shader";

  constexpr auto Fragment="Test2Frag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT );
  shader->loadShaderSource(Fragment,"files/frag.glsl");
  EXPECT_TRUE(shader->compileShader(Fragment))<<"error compiling vert shader";
  shader->attachShaderToProgram(shaderName,Vertex);
  shader->attachShaderToProgram(shaderName,Fragment);


  EXPECT_TRUE(shader->linkProgramObject(shaderName));
  (*shader)[shaderName]->use();
  EXPECT_TRUE(shader->getCurrentShaderName()==shaderName);
}

TEST(ShaderLib,loadPartsFailVertex)
{

  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Test3",ngl::ErrorExit::OFF);
  constexpr auto Vertex="Test3Vert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX ,ngl::ErrorExit::OFF);
  shader->loadShaderSource(Vertex,"files/vertErr.glsl");
  EXPECT_FALSE(shader->compileShader(Vertex))<<"error compiling vert shader";


}

TEST(ShaderLib,loadPartsFailFragment)
{
  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Test4",ngl::ErrorExit::OFF);
  constexpr auto Fragment="Test4Frag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT ,ngl::ErrorExit::OFF);
  shader->loadShaderSource(Fragment,"files/fragErr.glsl");
  EXPECT_FALSE(shader->compileShader(Fragment))<<"error compiling vert shader";

}


TEST(ShaderLib,failLink)
{
  constexpr auto *shaderName="Test5";
  auto shader = ngl::ShaderLib::instance();
  shader->createShaderProgram(shaderName,ngl::ErrorExit::OFF);
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
  EXPECT_FALSE(shader->linkProgramObject(shaderName))<<"This should not link as in and out don't match";
}

TEST(ShaderLib,testSetUniform)
{
  auto shader = ngl::ShaderLib::instance();
  auto *shaderName="TestUniform";
  EXPECT_TRUE(shader->loadShader(shaderName,"files/testUniformVertex.glsl","files/testUniformFragment.glsl",ngl::ErrorExit::OFF))<<"shader loaded?";
  shader->use(shaderName);
  {
    shader->setUniform("testFloat",2.25f);
    float result;
    shader->getUniform("testFloat",result);
    EXPECT_FLOAT_EQ(result,2.25f)<<"Testing setting a single float";
  }
  {
    shader->setUniform("testVec2",0.5f,2.0f);
    float resultF1,resultF2;
    shader->getUniform("testVec2",resultF1,resultF2);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"Test setting two floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"Test setting two floats y";
    ngl::Vec2 resultVec2;
    shader->getUniform("testVec2",resultVec2);
    EXPECT_FLOAT_EQ(resultVec2.m_x,0.5f)<<"Test getting from ngl::Vec2 m_x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.0f)<<"Test getting from ngl::Vec2 m_y";;
  }
  {
    shader->setUniform("testVec3",0.5f,2.0f,-22.2f);
    ngl::Real resultF1,resultF2,resultF3;
    shader->getUniform("testVec3",resultF1,resultF2,resultF3);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF3,-22.2f)<<"test setting 3 floats x";
    ngl::Vec3 resultVec3;
    shader->getUniform("testVec3",resultVec3);
    EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f)<<"test getting ngl::Vec3 m_x";
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f)<<"test getting ngl::Vec3 m_y";
    EXPECT_FLOAT_EQ(resultVec3.m_z,-22.2f)<<"test getting ngl::Vec3 m_z";
  }
  {
    shader->setUniform("testVec4",0.5f,2.0f,-22.2f,1230.4f);
    ngl::Real resultF1,resultF2,resultF3,resultF4;
    shader->getUniform("testVec4",resultF1,resultF2,resultF3,resultF4);
    EXPECT_FLOAT_EQ(resultF1,0.5f);
    EXPECT_FLOAT_EQ(resultF2,2.0f);
    EXPECT_FLOAT_EQ(resultF3,-22.2f);
    EXPECT_FLOAT_EQ(resultF4,1230.4f);
    ngl::Vec4 resultVec4;
    shader->getUniform("testVec4",resultVec4);
    EXPECT_FLOAT_EQ(resultVec4.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,-22.2f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,1230.4f);
  }

}


TEST(ShaderLib,editShader)
{

  auto shader = ngl::ShaderLib::instance();
  auto *shaderName="Edit";

  shader->createShaderProgram(shaderName,ngl::ErrorExit::OFF);
  constexpr auto Vertex="EditVert";
  shader->attachShader( Vertex, ngl::ShaderType::VERTEX ,ngl::ErrorExit::OFF);
  shader->loadShaderSource(Vertex,"files/EditVert.glsl");
  EXPECT_TRUE(shader->editShader(Vertex,"@numLights","2"))<<"edit shader";
  EXPECT_TRUE(shader->compileShader(Vertex))<<"error compiling vert shader";
  constexpr auto Fragment="EditFrag";
  shader->attachShader( Fragment, ngl::ShaderType::FRAGMENT,ngl::ErrorExit::OFF );
  shader->loadShaderSource(Fragment,"files/EditFrag.glsl");
  EXPECT_TRUE(shader->editShader(Fragment,"@numLights","2"))<<"edit shader";
  EXPECT_TRUE(shader->compileShader(Fragment))<<"error compiling vert shader";
  shader->attachShaderToProgram(shaderName,Vertex);
  shader->attachShaderToProgram(shaderName,Fragment);
  EXPECT_TRUE(shader->linkProgramObject(shaderName));
  (*shader)[shaderName]->use();
  EXPECT_TRUE(shader->getCurrentShaderName()==shaderName);
  // Now re-edit
  EXPECT_TRUE(shader->editShader(Vertex,"@numLights","5"))<<"edit shader";
  EXPECT_TRUE(shader->editShader(Fragment,"@numLights","5"))<<"edit shader";
  EXPECT_TRUE(shader->compileShader(Vertex))<<"error compiling vert shader";
  EXPECT_TRUE(shader->compileShader(Fragment))<<"error compiling vert shader";
  EXPECT_TRUE(shader->linkProgramObject(shaderName));




}
