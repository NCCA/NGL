#include <gtest/gtest.h>
#include <ngl/ShaderLib.h>
#include <glm/glm.hpp>
#include <ngl/NGLStream.h>
TEST(ShaderLib,StaticInit)
{
  // we have Colour, Text, Diffuse and Checker (but vert and frag) so 8 shaders in total
  EXPECT_TRUE(ngl::ShaderLib::getNumShaders() ==8);
}

TEST(ShaderLib,loadShader)
{
  EXPECT_TRUE(ngl::ShaderLib::loadShader("Test","files/vert.glsl","files/frag.glsl"));

  EXPECT_TRUE(ngl::ShaderLib::loadShader("TestGeo","files/vert.glsl","files/frag.glsl","files/geo.glsl"));


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
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testFloat",2.25f))<<"Setting a single float";
    float result;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testFloat",result))<<"Getting a single float";
    EXPECT_FLOAT_EQ(result,2.25f)<<"Testing setting a single float";
  }
 
  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec2",0.5f,2.0f));
    float resultF1,resultF2;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec2",resultF1,resultF2));
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"Test setting two floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"Test setting two floats y";
    ngl::Vec2 resultVec2;
    ngl::ShaderLib::getUniform("testVec2",resultVec2);
    EXPECT_FLOAT_EQ(resultVec2.m_x,0.5f)<<"Test getting from ngl::Vec2 m_x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.0f)<<"Test getting from ngl::Vec2 m_y";;

    glm::vec2 glmVec2(1.5f,2.5f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec2",glmVec2));
    ngl::ShaderLib::getUniform("testVec2",resultVec2);
    EXPECT_FLOAT_EQ(resultVec2.m_x,1.5f)<<"Test getting from ngl::Vec2 m_x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.5f)<<"Test getting from ngl::Vec2 m_y";;


  }
  /*
  {
    ngl::Vec2 vec2(0.5f,2.0f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec2",vec2));
    ngl::Vec2 resultVec2;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec2",resultVec2));
    EXPECT_FLOAT_EQ(resultVec2.m_x,0.5f)<<"Test setting two floats x";
    EXPECT_FLOAT_EQ(resultVec2.m_y,2.0f)<<"Test setting two floats y";
  }
  {
    ngl::Vec3 vec3(0.5f,2.0f,4.0f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec3",vec3));
    ngl::Vec3 resultVec3;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec3",resultVec3));
    EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec3.m_z,4.0f);

    glm::vec3 glmVec3(1.5f,2.5f,3.5f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec3",glmVec3));
    ngl::ShaderLib::getUniform("testVec3",resultVec3);
    EXPECT_FLOAT_EQ(resultVec3.m_x,1.5f);
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.5f);
    EXPECT_FLOAT_EQ(resultVec3.m_z,3.5f);
  }
  {
    ngl::Vec4 vec4(0.5f,2.0f,4.0f,5.0f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec4",vec4));
    ngl::Vec4 resultVec4;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec4",resultVec4));
    EXPECT_FLOAT_EQ(resultVec4.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,4.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,5.0f);

    glm::vec4 glmVec4(1.5f,2.5f,4.5f,5.5f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec4",glmVec4));
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec4",resultVec4));
    EXPECT_FLOAT_EQ(resultVec4.m_x,1.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,4.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,5.5f);

  }

  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec3",0.5f,2.0f,-22.2f));
    ngl::Real resultF1,resultF2,resultF3;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec3",resultF1,resultF2,resultF3));
    EXPECT_FLOAT_EQ(resultF1,0.5f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF2,2.0f)<<"test setting 3 floats x";
    EXPECT_FLOAT_EQ(resultF3,-22.2f)<<"test setting 3 floats x";
    ngl::Vec3 resultVec3;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec3",resultVec3));
    EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f)<<"test getting ngl::Vec3 m_x";
    EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f)<<"test getting ngl::Vec3 m_y";
    EXPECT_FLOAT_EQ(resultVec3.m_z,-22.2f)<<"test getting ngl::Vec3 m_z";
  }
  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testVec4",0.5f,2.0f,-22.2f,1230.4f));
    ngl::Real resultF1,resultF2,resultF3,resultF4;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec4",resultF1,resultF2,resultF3,resultF4));
    EXPECT_FLOAT_EQ(resultF1,0.5f);
    EXPECT_FLOAT_EQ(resultF2,2.0f);
    EXPECT_FLOAT_EQ(resultF3,-22.2f);
    EXPECT_FLOAT_EQ(resultF4,1230.4f);
    ngl::Vec4 resultVec4;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testVec4",resultVec4));
    EXPECT_FLOAT_EQ(resultVec4.m_x,0.5f);
    EXPECT_FLOAT_EQ(resultVec4.m_y,2.0f);
    EXPECT_FLOAT_EQ(resultVec4.m_z,-22.2f);
    EXPECT_FLOAT_EQ(resultVec4.m_w,1230.4f);
  }

  {
    // test arrays
    for(int i=0; i<3; ++i)
    {
      EXPECT_TRUE(ngl::ShaderLib::setUniform(fmt::format("testArray[{}]",i),0.5f,2.0f,-22.2f));
      ngl::Real resultF1,resultF2,resultF3;
      EXPECT_TRUE(ngl::ShaderLib::getUniform(fmt::format("testArray[{}]",i),resultF1,resultF2,resultF3));
      EXPECT_FLOAT_EQ(resultF1,0.5f)<<"test setting 3 floats x";
      EXPECT_FLOAT_EQ(resultF2,2.0f)<<"test setting 3 floats x";
      EXPECT_FLOAT_EQ(resultF3,-22.2f)<<"test setting 3 floats x";
      ngl::Vec3 resultVec3;
      EXPECT_TRUE(ngl::ShaderLib::getUniform(fmt::format("testArray[{}]",i),resultVec3));
      EXPECT_FLOAT_EQ(resultVec3.m_x,0.5f)<<"test getting ngl::Vec3 m_x";
      EXPECT_FLOAT_EQ(resultVec3.m_y,2.0f)<<"test getting ngl::Vec3 m_y";
      EXPECT_FLOAT_EQ(resultVec3.m_z,-22.2f)<<"test getting ngl::Vec3 m_z";
    }
  }

{
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testInt",2));
    int result;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testInt",result));
    EXPECT_EQ(result,2)<<"Testing setting a single int";
  }

  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testInt2",2,3));
    int a,b;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testInt2",a,b));
    EXPECT_EQ(a,2)<<"Testing setting a ivec2 int";
    EXPECT_EQ(b,3)<<"Testing setting a ivec2 int";
  }

 {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testInt3",2,3,4));
    int a,b,c;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testInt3",a,b,c));
    EXPECT_EQ(a,2)<<"Testing setting a ivec3 int";
    EXPECT_EQ(b,3)<<"Testing setting a ivec3 int";
    EXPECT_EQ(c,4)<<"Testing setting a ivec3 int";
  }


 {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testInt4",2,3,4,5));
    int a,b,c,d;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testInt4",a,b,c,d));
    EXPECT_EQ(a,2)<<"Testing setting a ivec4 int";
    EXPECT_EQ(b,3)<<"Testing setting a ivec4 int";
    EXPECT_EQ(c,4)<<"Testing setting a ivec4 int";
    EXPECT_EQ(d,5)<<"Testing setting a ivec4 int";
  }

  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat2",ngl::Mat2()));
    ngl::Mat2 result;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat2",result));
    EXPECT_TRUE(result==ngl::Mat2());
    
    // //float array[4]={1.0f,2.0f,3.0f,4.0f};
    std::vector<float> array={1.0f,2.0f,3.0f,4.0f};
    //EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat2",array));
    //EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat2",std::array<float,4>{1.0f,2.0f,3.0f,4.0f}));
   // ngl::ShaderLib::setUniform("testMat2",array);
    ngl::Mat2 result2(1.0f,2.0f,3.0f,4.0f);
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat2",result));
    EXPECT_TRUE(result==result2);

    glm::mat2 glmMat2(1.5f,2.5f,3.5f,4.5f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat2",glmMat2));
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat2",result));
    EXPECT_TRUE(result==ngl::Mat2(1.5f,2.5f,3.5f,4.5f));    
  }
  {
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat3",ngl::Mat3()));
    ngl::Mat3 result;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat3",result));
    EXPECT_TRUE(result==ngl::Mat3());

    // float array[9]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f};
    // EXPECT_TRUE(ngl::ShaderLib::setUniformMatrix3fv("testMat3",array));
    // ngl::Mat3 result2(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f);
    // EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat3",result));
    // EXPECT_TRUE(result==result2);

    glm::mat3 glmMat3(1.5f,2.5f,3.5f,4.5f,5.5f,6.5f,7.5f,8.5f,9.5f);
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat3",glmMat3));
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat3",result));
    EXPECT_TRUE(result==ngl::Mat3(1.5f,2.5f,3.5f,4.5f,5.5f,6.5f,7.5f,8.5f,9.5f));

  }
  {
    ngl::Mat4 testMat4;
    EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat4",testMat4));
    ngl::Mat4 result;
    EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat4",result));
    EXPECT_TRUE(result==ngl::Mat4());
    // float array[16]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
    // 10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f};
    // EXPECT_TRUE(ngl::ShaderLib::setUniformMatrix4fv("testMat4",array));
    // ngl::Mat4 result2(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
    // 10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f);
    // EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat4",result));
    // EXPECT_TRUE(result==result2);

    // glm::mat4 glmMat4(1.5f,2.5f,3.5f,4.5f,5.5f,6.5f,7.5f,8.5f,9.5f,
    // 10.5f,11.5f,12.5f,13.5f,14.5f,15.5f,16.5f);
    // EXPECT_TRUE(ngl::ShaderLib::setUniform("testMat4",glmMat4));
    // EXPECT_TRUE(ngl::ShaderLib::getUniform("testMat4",result));
    // EXPECT_TRUE(result==ngl::Mat4(1.5f,2.5f,3.5f,4.5f,5.5f,6.5f,7.5f,8.5f,9.5f,
    // 10.5f,11.5f,12.5f,13.5f,14.5f,15.5f,16.5f));
  }
  ngl::ShaderLib::printRegisteredUniforms(shaderName);*/
}

TEST(ShaderLib,testUniformBuffers)
{

  auto *shaderName="TestUniformBuffer";
  EXPECT_TRUE(ngl::ShaderLib::loadShader(shaderName,"files/testUniformBufferVertex.glsl","files/testUniformBufferFragment.glsl",ngl::ErrorExit::OFF))<<"shader loaded?";
  ngl::ShaderLib::use(shaderName);

  struct transform
  {
    ngl::Mat4 MVP;
    ngl::Mat4 normalMatrix;
    ngl::Mat4 M;
  };
  transform t;
  EXPECT_TRUE(ngl::ShaderLib::setUniformBuffer("TransformUBO", sizeof(transform), &t.MVP.m_00));
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
  EXPECT_TRUE(ngl::ShaderLib::linkProgramObject(shaderName))<<"First Link";
  ngl::ShaderLib::use(shaderName);
  EXPECT_TRUE(ngl::ShaderLib::getCurrentShaderName()==shaderName);

}

