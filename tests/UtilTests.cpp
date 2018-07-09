#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Util.h>
#include <ngl/Mat4.h>
#include <string>
#include <sstream>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern std::string print(const ngl::Mat4 &_m);

TEST(Util,perspective)
{
  float fov=45.0f;
  float near=0.02f;
  float far=10.0f;
  float aspect= 1024.0f / 720.0f;
  auto perspNGL=ngl::perspective(fov,aspect,near,far);
  // not conversion to radians
  auto perspGLM=glm::perspective(ngl::radians(fov),aspect,near,far);
  EXPECT_TRUE(ngl::Mat4(perspGLM)==perspNGL);
 // std::cout<<print(perspNGL)<<'\n'<<print(ngl::Mat4(perspGLM))<<'\n';
}

TEST(Util,perspectiveFov)
{
  float fov=45.0f;
  float near=0.02f;
  float far=10.0f;
  float aspect= 1024.0f / 720.0f;
  float width=1024;
  float height=720;
  auto perspNGL=ngl::perspectiveFov(fov,width,height,near,far);
  // not conversion to radians
  auto perspGLM=glm::perspectiveFov(ngl::radians(fov),width,height,near,far);
  EXPECT_TRUE(ngl::Mat4(perspGLM)==perspNGL);
 // std::cout<<print(perspNGL)<<'\n'<<print(ngl::Mat4(perspGLM))<<'\n';
}



TEST(Util,infinitePerspective)
{
  float fov=45.0f;
  float near=0.02f;
  float aspect= 1024.0f / 720.0f;
  auto perspNGL=ngl::infinitePerspective(fov,aspect,near);
  // not conversion to radians
  auto perspGLM=glm::infinitePerspective(ngl::radians(fov),aspect,near);
  EXPECT_TRUE(ngl::Mat4(perspGLM)==perspNGL);
 // std::cout<<print(perspNGL)<<'\n'<<print(ngl::Mat4(perspGLM))<<'\n';
}

TEST(Util,_rad)
{
  float fov=45.0f;
  float near=0.02f;
  float far=10.0f;
  float aspect= 1024.0f / 720.0f;
  auto perspNGL=ngl::perspective(fov,aspect,near,far);
  // not conversion to radians
  float r=45.0_rad;
  auto perspGLM=glm::perspective(r,aspect,near,far);
  EXPECT_TRUE(ngl::Mat4(perspGLM)==perspNGL);
 // std::cout<<print(perspNGL)<<'\n'<<print(ngl::Mat4(perspGLM))<<'\n';
}


TEST(Util,ortho)
{
  auto orthNGL= ngl::ortho(-1.0f, 1.0f, -1.0f,1.0f,1.0f,-1.0f) ;
  auto orthGLM= glm::ortho(-1.0f, 1.0f, -1.0f,1.0f,1.0f,-1.0f) ;
  EXPECT_TRUE(ngl::Mat4(orthGLM)==orthNGL);
}

TEST(Util,ortho2d)
{
  auto orthNGL= ngl::ortho(-1.0f, 1.0f, -1.0f,1.0f) ;
  auto orthGLM= glm::ortho(-1.0f, 1.0f, -1.0f,1.0f) ;
  EXPECT_TRUE(ngl::Mat4(orthGLM)==orthNGL);
}

TEST(Util,lookAt)
{

  auto lookNGL=ngl::lookAt({2.0f,2.0f,2.0f},{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f});
  auto lookGLM=glm::lookAt(glm::vec3(2.0f,2.0f,2.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
  EXPECT_TRUE(ngl::Mat4(lookGLM)==lookNGL);
}

TEST(Util,frustum)
{
  auto orthNGL=ngl::frustum(-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f) ;
  auto orthGLM=glm::frustum(-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f) ;
  EXPECT_TRUE(ngl::Mat4(orthGLM)==orthNGL);
}

TEST(Util,radians)
{
  auto result=ngl::radians(45.0f);
  EXPECT_FLOAT_EQ(result,0.7853981633974483);
  EXPECT_FLOAT_EQ(result,45.0_rad);
}

TEST(Util,degrees)
{
  auto result=ngl::degrees(0.7853981633974483f);
  EXPECT_FLOAT_EQ(result,45.0f);
  EXPECT_FLOAT_EQ(0.7853981633974483_deg,45.0f);
}



TEST(Util,calcNormal1)
{
  auto result= ngl::calcNormal( ngl::Vec3(-1.0f,-1.0f,0.0f),ngl::Vec3(0.0f,0.0f,0.0f) ,ngl::Vec3(1.0f,-1.0f,0.0f));
  EXPECT_EQ(result,ngl::Vec3(0.0f,0.0f,1.0f));

}

TEST(Util,calcNormal2)
{
  auto result= ngl::calcNormal( ngl::Vec4(-1.0f,-1.0f,0.0f,0.0f),ngl::Vec4(0.0f,0.0f,0.0f,0.0f) ,ngl::Vec4(1.0f,-1.0f,0.0f,0.0f));
  EXPECT_EQ(result,ngl::Vec3(0.0f,0.0f,1.0f));
}


