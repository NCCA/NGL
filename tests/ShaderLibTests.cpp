#include <gtest/gtest.h>
#include <ngl/ShaderLib.h>


TEST(ShaderLib,StaticInit)
{
  // we have Colour, Text, Diffuse and Checker (but vert and frag) so 8 shaders in total
  EXPECT_TRUE(ngl::ShaderLib::getNumShaders() ==8);
}

TEST(ShaderLib,loadShader)
{
  EXPECT_TRUE(ngl::ShaderLib::loadShader("Test","files/vert.glsl","files/frag.glsl"));
}

TEST(ShaderLib,use)
{
  ngl::ShaderLib::use("Test");
  EXPECT_TRUE(ngl::ShaderLib::getCurrentShaderName()=="Test");
}

TEST(ShaderLib,useNull)
{
  ngl::ShaderLib::use("NotThere");
  EXPECT_TRUE(ngl::ShaderLib::getCurrentShaderName()=="NULL");
}


TEST(ShaderLib,loadErrorShader)
{
  EXPECT_FALSE(ngl::ShaderLib::loadShader("Test","files/vertErr.glsl","files/fragErr.glsl",ngl::ErrorExit::OFF));
}

TEST(ShaderLib,loadParts)
{

  auto *shaderName="Test2";

  ngl::ShaderLib::createShaderProgram(shaderName,ngl::ErrorExit::OFF);
  constexpr auto Vertex="Test2Vert";
  ngl::ShaderLib::attachShader( Vertex, ngl::ShaderType::VERTEX );
  ngl::ShaderLib::loadShaderSource(Vertex,"files/vert.glsl");
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Vertex))<<"error compiling vert shader";

  constexpr auto Fragment="Test2Frag";
  ngl::ShaderLib::attachShader( Fragment, ngl::ShaderType::FRAGMENT );
  ngl::ShaderLib::loadShaderSource(Fragment,"files/frag.glsl");
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Fragment))<<"error compiling vert shader";
  ngl::ShaderLib::attachShaderToProgram(shaderName,Vertex);
  ngl::ShaderLib::attachShaderToProgram(shaderName,Fragment);


  EXPECT_TRUE(ngl::ShaderLib::linkProgramObject(shaderName));
  ngl::ShaderLib::use(shaderName);
  EXPECT_TRUE(ngl::ShaderLib::getCurrentShaderName()==shaderName);
}

TEST(ShaderLib,loadPartsFailVertex)
{


  ngl::ShaderLib::createShaderProgram("Test3",ngl::ErrorExit::OFF);
  constexpr auto Vertex="Test3Vert";
  ngl::ShaderLib::attachShader( Vertex, ngl::ShaderType::VERTEX ,ngl::ErrorExit::OFF);
  ngl::ShaderLib::loadShaderSource(Vertex,"files/vertErr.glsl");
  EXPECT_FALSE(ngl::ShaderLib::compileShader(Vertex))<<"error compiling vert shader";


}

TEST(ShaderLib,loadPartsFailFragment)
{

  ngl::ShaderLib::createShaderProgram("Test4",ngl::ErrorExit::OFF);
  constexpr auto Fragment="Test4Frag";
  ngl::ShaderLib::attachShader( Fragment, ngl::ShaderType::FRAGMENT ,ngl::ErrorExit::OFF);
  ngl::ShaderLib::loadShaderSource(Fragment,"files/fragErr.glsl");
  EXPECT_FALSE(ngl::ShaderLib::compileShader(Fragment))<<"error compiling vert shader";

}


TEST(ShaderLib,failLink)
{
  constexpr auto *shaderName="Test5";

  ngl::ShaderLib::createShaderProgram(shaderName,ngl::ErrorExit::OFF);
  constexpr auto Vertex="Test5Vert";
  ngl::ShaderLib::attachShader( Vertex, ngl::ShaderType::VERTEX );
  ngl::ShaderLib::loadShaderSource(Vertex,"files/vertLinkErr.glsl");
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Vertex))<<"error compiling vert shader";
  constexpr auto Fragment="Test5Frag";
  ngl::ShaderLib::attachShader( Fragment, ngl::ShaderType::FRAGMENT );
  ngl::ShaderLib::loadShaderSource(Fragment,"files/fragLinkErr.glsl");
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Fragment))<<"error compiling vert shader";
  ngl::ShaderLib::attachShaderToProgram(shaderName,Vertex);
  ngl::ShaderLib::attachShaderToProgram(shaderName,Fragment);
  EXPECT_FALSE(ngl::ShaderLib::linkProgramObject(shaderName))<<"This should not link as in and out don't match";
}

TEST(ShaderLib,testSetUniform)
{

  auto *shaderName="TestUniform";
  EXPECT_TRUE(ngl::ShaderLib::loadShader(shaderName,"files/testUniformVertex.glsl","files/testUniformFragment.glsl",ngl::ErrorExit::OFF))<<"shader loaded?";
  ngl::ShaderLib::use(shaderName);
  {
    ngl::ShaderLib::setUniform("testFloat",2.25f);
    float result;
    ngl::ShaderLib::getUniform("testFloat",result);
    EXPECT_FLOAT_EQ(result,2.25f)<<"Testing setting a single float";
  }
  {
    ngl::ShaderLib::setUniform("testVec2",0.5f,2.0f);
    float resultF1,resultF2;
    ngl::ShaderLib::getUniform("testVec2",resultF1,resultF2);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"Test setting two floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"Test setting two floats y";
    ngl::Vec2 resultVec2;
    ngl::ShaderLib::getUniform("testVec2",resultVec2);
    EXPECT_FLOAT_EQ(resultVec2.m_x,0.5f)<<"Test getting from ngl::Vec2 m_x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.0f)<<"Test getting from ngl::Vec2 m_y";;
  }
  {
    ngl::ShaderLib::setUniform("testVec3",0.5f,2.0f,-22.2f);
    ngl::Real resultF1,resultF2,resultF3;
    ngl::ShaderLib::getUniform("testVec3",resultF1,resultF2,resultF3);
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF3,-22.2f)<<"test setting 3 floats x";
    ngl::Vec3 resultVec3;
    ngl::ShaderLib::getUniform("testVec3",resultVec3);
    EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f)<<"test getting ngl::Vec3 m_x";
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f)<<"test getting ngl::Vec3 m_y";
    EXPECT_FLOAT_EQ(resultVec3.m_z,-22.2f)<<"test getting ngl::Vec3 m_z";
  }
  {
    ngl::ShaderLib::setUniform("testVec4",0.5f,2.0f,-22.2f,1230.4f);
    ngl::Real resultF1,resultF2,resultF3,resultF4;
    ngl::ShaderLib::getUniform("testVec4",resultF1,resultF2,resultF3,resultF4);
    EXPECT_FLOAT_EQ(resultF1,0.5f);
    EXPECT_FLOAT_EQ(resultF2,2.0f);
    EXPECT_FLOAT_EQ(resultF3,-22.2f);
    EXPECT_FLOAT_EQ(resultF4,1230.4f);
    ngl::Vec4 resultVec4;
    ngl::ShaderLib::getUniform("testVec4",resultVec4);
    EXPECT_FLOAT_EQ(resultVec4.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,-22.2f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,1230.4f);
  }
  {
    ngl::ShaderLib::setUniform("testMat2",ngl::Mat2());
    ngl::Mat2 result;
    ngl::ShaderLib::getUniform("testMat2",result);
    EXPECT_TRUE(result==ngl::Mat2());
  }
  {
    ngl::ShaderLib::setUniform("testMat3",ngl::Mat3());
    ngl::Mat3 result;
    ngl::ShaderLib::getUniform("testMat3",result);
    EXPECT_TRUE(result==ngl::Mat3());
  }
  {
    ngl::ShaderLib::setUniform("testMat4",ngl::Mat4());
    ngl::Mat4 result;
    ngl::ShaderLib::getUniform("testMat4",result);
    EXPECT_TRUE(result==ngl::Mat4());
  }

}


TEST(ShaderLib,editShader)
{


  auto *shaderName="Edit";

  ngl::ShaderLib::createShaderProgram(shaderName,ngl::ErrorExit::OFF);
  constexpr auto Vertex="EditVert";
  ngl::ShaderLib::attachShader( Vertex, ngl::ShaderType::VERTEX ,ngl::ErrorExit::OFF);
  ngl::ShaderLib::loadShaderSource(Vertex,"files/EditVert.glsl");
  EXPECT_TRUE(ngl::ShaderLib::editShader(Vertex,"@breakMe","1.0"))<<"edit shader set breakMe ";
  EXPECT_TRUE(ngl::ShaderLib::editShader(Vertex,"@numLights","2"))<<"edit shader";
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Vertex))<<"error compiling vert shader";
  constexpr auto Fragment="EditFrag";
  ngl::ShaderLib::attachShader( Fragment, ngl::ShaderType::FRAGMENT,ngl::ErrorExit::OFF );
  ngl::ShaderLib::loadShaderSource(Fragment,"files/EditFrag.glsl");
  EXPECT_TRUE(ngl::ShaderLib::editShader(Fragment,"@numLights","2"))<<"edit shader";
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Fragment))<<"error compiling vert shader";
  ngl::ShaderLib::attachShaderToProgram(shaderName,Vertex);
  ngl::ShaderLib::attachShaderToProgram(shaderName,Fragment);
  EXPECT_TRUE(ngl::ShaderLib::linkProgramObject(shaderName))<<"First Link";
  ngl::ShaderLib::use(shaderName);
  EXPECT_TRUE(ngl::ShaderLib::getCurrentShaderName()==shaderName);
  // Now re-edit
  ngl::ShaderLib::resetEdits(Vertex);
  ngl::ShaderLib::resetEdits(Fragment);
  EXPECT_TRUE(ngl::ShaderLib::editShader(Vertex,"@numLights","5"))<<"edit shader 2nd";
  EXPECT_TRUE(ngl::ShaderLib::editShader(Vertex,"@breakMe","1.0"))<<"edit shader set breakMe 2nd";
  EXPECT_TRUE(ngl::ShaderLib::editShader(Fragment,"@numLights","5"))<<"edit shader";
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Vertex))<<"error compiling vert shader";
  EXPECT_TRUE(ngl::ShaderLib::compileShader(Fragment))<<"error compiling vert shader";
  EXPECT_TRUE(ngl::ShaderLib::linkProgramObject(shaderName));
}
