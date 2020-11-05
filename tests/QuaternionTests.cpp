#include <gtest/gtest.h>
#include <ngl/Util.h>
#include <ngl/Types.h>
#include <ngl/Mat4.h>
#include <ngl/Quaternion.h>
#include <sstream>
#include <ngl/NGLStream.h>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp> 
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

// use here https://www.vcalc.com/equation/?uuid=73f543b2-75f5-11e6-9770-bc764e2038f2 for verification

TEST(Quaternion,DefaultCtor)
{
  ngl::Quaternion test;

  EXPECT_FLOAT_EQ(test.getS(),1.0f);
  EXPECT_FLOAT_EQ(test.getX(),0.0f);
  EXPECT_FLOAT_EQ(test.getY(),0.0f);
  EXPECT_FLOAT_EQ(test.getZ(),0.0f);
  glm::quat glmTest(1,0,0,0);
  EXPECT_FLOAT_EQ(test.getS(),glmTest.w);
  EXPECT_FLOAT_EQ(test.getX(),glmTest.x);
  EXPECT_FLOAT_EQ(test.getY(),glmTest.y);
  EXPECT_FLOAT_EQ(test.getZ(),glmTest.z);


}

TEST(Quaternion,UserCtor)
{
  ngl::Quaternion test(0.2f,0.0f,1.0f,0.0f);
  EXPECT_FLOAT_EQ(test.getS(),0.2f);
  EXPECT_FLOAT_EQ(test.getX(),0.0f);
  EXPECT_FLOAT_EQ(test.getY(),1.0f);
  EXPECT_FLOAT_EQ(test.getZ(),0.0f);
  glm::quat glmTest(0.2f,0.0f,1.0f,0.0f);
  EXPECT_FLOAT_EQ(test.getS(),glmTest.w);
  EXPECT_FLOAT_EQ(test.getX(),glmTest.x);
  EXPECT_FLOAT_EQ(test.getY(),glmTest.y);
  EXPECT_FLOAT_EQ(test.getZ(),glmTest.z);
}

/*
// 0 0 1; 0 1 0; -1 0 0]
TEST(Quaternion,fromMat4)
{
  ngl::Mat4 tx(0.0f,0.0f,1.0f,0.0f,
               0.0f,1.0f,0.0f,0.0f,
               1.0f,0.0f,0.0f,0.0f,
               0.0f,0.0f,0.0f,1.0f);
  ngl::Quaternion test(tx);
  ASSERT_NEAR(test.getS(),0.7071f,0.001f);
  ASSERT_NEAR(test.getX(),0.0f,0.001f);
  ASSERT_NEAR(test.getY(),0.7071f,0.001f);
  ASSERT_NEAR(test.getZ(),0.0f,0.001f);

  glm::

}
*/
TEST(Quaternion,addition)
{
  ngl::Quaternion q1(0.5f,1.0f,0.0f,0.0f);
  ngl::Quaternion q2(0.2f,0.0f,1.0f,0.0f);
  auto res=q1+q2;
  EXPECT_FLOAT_EQ(res.getS(),0.7f);
  EXPECT_FLOAT_EQ(res.getX(),1.0f);
  EXPECT_FLOAT_EQ(res.getY(),1.0f);
  EXPECT_FLOAT_EQ(res.getZ(),0.0f);

  glm::quat gq1(0.5f,1.0f,0.0f,0.0f);
  glm::quat gq2(0.2f,0.0f,1.0f,0.0f);
  auto gres=gq1+gq2;
  EXPECT_NEAR(res.getS(),gres.w,0.001f);
  EXPECT_NEAR(res.getX(),gres.x,0.001f);
  EXPECT_NEAR(res.getY(),gres.y,0.001f);
  EXPECT_NEAR(res.getZ(),gres.z,0.001f);


}


TEST(Quaternion,additionEqual)
{
  ngl::Quaternion q1(0.5f,1.0f,0.0f,0.0f);
  ngl::Quaternion q2(0.2f,0.0f,1.0f,0.0f);
  q1+=q2;
  EXPECT_FLOAT_EQ(q1.getS(),0.7f);
  EXPECT_FLOAT_EQ(q1.getX(),1.0f);
  EXPECT_FLOAT_EQ(q1.getY(),1.0f);
  EXPECT_FLOAT_EQ(q1.getZ(),0.0f);
  glm::quat gq1(0.5f,1.0f,0.0f,0.0f);
  glm::quat gq2(0.2f,0.0f,1.0f,0.0f);
  gq1+=gq2;
  EXPECT_NEAR(q1.getS(),gq1.w,0.001f);
  EXPECT_NEAR(q1.getX(),gq1.x,0.001f);
  EXPECT_NEAR(q1.getY(),gq1.y,0.001f);
  EXPECT_NEAR(q1.getZ(),gq1.z,0.001f);
}

TEST(Quaternion,subtract)
{
  ngl::Quaternion q1(0.5f,1.0f,1.0f,0.0f);
  ngl::Quaternion q2(0.2f,1.0f,1.0f,0.0f);
  auto res=q1-q2;
  EXPECT_FLOAT_EQ(res.getS(),0.3f);
  EXPECT_FLOAT_EQ(res.getX(),0.0f);
  EXPECT_FLOAT_EQ(res.getY(),0.0f);
  EXPECT_FLOAT_EQ(res.getZ(),0.0f);
  glm::quat gq1(0.5f,1.0f,1.0f,0.0f);
  glm::quat gq2(0.2f,1.0f,1.0f,0.0f);
  auto gres=gq1-gq2;
  EXPECT_NEAR(res.getS(),gres.w,0.001f);
  EXPECT_NEAR(res.getX(),gres.x,0.001f);
  EXPECT_NEAR(res.getY(),gres.y,0.001f);
  EXPECT_NEAR(res.getZ(),gres.z,0.001f);

}

TEST(Quaternion,subtractEqual)
{
  ngl::Quaternion q1(0.5f,1.0f,1.0f,0.0f);
  ngl::Quaternion q2(0.2f,1.0f,1.0f,0.0f);
  q1-=q2;
  EXPECT_FLOAT_EQ(q1.getS(),0.3f);
  EXPECT_FLOAT_EQ(q1.getX(),0.0f);
  EXPECT_FLOAT_EQ(q1.getY(),0.0f);
  EXPECT_FLOAT_EQ(q1.getZ(),0.0f);

  glm::quat gq1(0.5f,1.0f,1.0f,0.0f);
  glm::quat gq2(0.2f,1.0f,1.0f,0.0f);
  gq1-=gq2;
  EXPECT_NEAR(q1.getS(),gq1.w,0.001f);
  EXPECT_NEAR(q1.getX(),gq1.x,0.001f);
  EXPECT_NEAR(q1.getY(),gq1.y,0.001f);
  EXPECT_NEAR(q1.getZ(),gq1.z,0.001f);
}

// from https://www.wolframalpha.com/input/?i=quaternion+-Sin%5BPi%5D%2B3i%2B4j%2B3k+multiplied+by+-1j%2B3.9i%2B4-3k
// (-sin(π) + 3i + 4j + 3k) × (4 + 3.9i -1j -3k)
// 1.3 + 3 i + 36.7 j - 6.6 k

TEST(Quaternion,multiplyQuat)
{
  ngl::Quaternion q1(-sinf(ngl::PI),3.0f,4.0f,3.0f);
  ngl::Quaternion q2(4.0f,3.9f,-1.0f,-3.0f);
  auto res=q1*q2;
  EXPECT_FLOAT_EQ(res.getS(),1.3f);
  EXPECT_FLOAT_EQ(res.getX(),3.0f);
  EXPECT_FLOAT_EQ(res.getY(),36.7f);
  EXPECT_FLOAT_EQ(res.getZ(),-6.60f);

  glm::quat gq1(-sinf(ngl::PI),3.0f,4.0f,3.0f);
  glm::quat gq2(4.0f,3.9f,-1.0f,-3.0f);
  auto gres=gq1*gq2;

  EXPECT_NEAR(res.getS(),gres.w,0.001f);
  EXPECT_NEAR(res.getX(),gres.x,0.001f);
  EXPECT_NEAR(res.getY(),gres.y,0.001f);
  EXPECT_NEAR(res.getZ(),gres.z,0.001f);

}

TEST(Quaternion,multiplyEqualQuat)
{
  ngl::Quaternion q1(-sinf(ngl::PI),3.0f,4.0f,3.0f);
  ngl::Quaternion q2(4.0f,3.9f,-1.0f,-3.0f);
  q1*=q2;
  EXPECT_FLOAT_EQ(q1.getS(),1.3f);
  EXPECT_FLOAT_EQ(q1.getX(),3.0f);
  EXPECT_FLOAT_EQ(q1.getY(),36.7f);
  EXPECT_FLOAT_EQ(q1.getZ(),-6.60f);

  glm::quat gq1(-sinf(ngl::PI),3.0f,4.0f,3.0f);
  glm::quat gq2(4.0f,3.9f,-1.0f,-3.0f);
  gq1*=gq2;
  EXPECT_NEAR(q1.getS(),gq1.w,0.001f);
  EXPECT_NEAR(q1.getX(),gq1.x,0.001f);
  EXPECT_NEAR(q1.getY(),gq1.y,0.001f);
  EXPECT_NEAR(q1.getZ(),gq1.z,0.001f);

}

TEST(Quaternion,magnitude)
{
  ngl::Quaternion q1(1.3f,3.0f,36.7f,-6.6f);
  EXPECT_FLOAT_EQ(q1.magnitude(),37.4318f);

  glm::quat gq1(1.3f,3.0f,36.7f,-6.6f);
  EXPECT_FLOAT_EQ(q1.magnitude(),glm::length(gq1));

}

TEST(Quaternion,normalize)
{
  ngl::Quaternion q1(1.3f,3.0f,36.7f,-6.6f);
  q1.normalise();
  //0.0347298 + 0.0801457i + 0.98045j - 0.176321k

  ASSERT_NEAR(q1.getS(),0.0347298f,0.001f);
  ASSERT_NEAR(q1.getX(),0.0801457f,0.001f);
  ASSERT_NEAR(q1.getY(),0.98045f,0.001f);
  ASSERT_NEAR(q1.getZ(),-0.176321f,0.001f);

  glm::quat gq1(1.3f,3.0f,36.7f,-6.6f);
  gq1=glm::normalize(gq1);

  ASSERT_NEAR(q1.getS(),gq1.w,0.001f);
  ASSERT_NEAR(q1.getX(),gq1.x,0.001f);
  ASSERT_NEAR(q1.getY(),gq1.y,0.001f);
  ASSERT_NEAR(q1.getZ(),gq1.z,0.001f);
}

TEST(Quaternion,conjugate)
{
  ngl::Quaternion q1(1.3f,3.0f,36.7f,-6.6f);
  q1=q1.conjugate();
  //1.3 - 3i - 36.7j + 6.6k
  ASSERT_NEAR(q1.getS(),1.3f,0.001f);
  ASSERT_NEAR(q1.getX(),-3.0f,0.001f);
  ASSERT_NEAR(q1.getY(),-36.7f,0.001f);
  ASSERT_NEAR(q1.getZ(),6.6f,0.001f);

  glm::quat gq1(1.3f,3.0f,36.7f,-6.6f);
  gq1=glm::conjugate(gq1);
  ASSERT_NEAR(q1.getS(),gq1.w,0.001f);
  ASSERT_NEAR(q1.getX(),gq1.x,0.001f);
  ASSERT_NEAR(q1.getY(),gq1.y,0.001f);
  ASSERT_NEAR(q1.getZ(),gq1.z,0.001f);
}

TEST(Quaternion,inverse)
{
  ngl::Quaternion q1(1.3f,-3.0f,-36.7f,6.6f);
  q1=q1.inverse();
  ASSERT_NEAR(q1.getS(),0.000927816f,0.01f);
  ASSERT_NEAR(q1.getX(),0.00214111f,0.01f);
  ASSERT_NEAR(q1.getY(),0.026193f,0.01f);
  ASSERT_NEAR(q1.getZ(),0.00471045f,0.01f);

  glm::quat gq1(1.3f,-3.0f,-36.7f,6.6f);
  gq1=glm::inverse(gq1);
  ASSERT_NEAR(q1.getS(),gq1.w,0.001f);
  ASSERT_NEAR(q1.getX(),gq1.x,0.001f);
  ASSERT_NEAR(q1.getY(),gq1.y,0.001f);
  ASSERT_NEAR(q1.getZ(),gq1.z,0.001f);

}


TEST(Quaternion,fromEuler)
{
  ngl::Quaternion q;
  q.fromEulerAngles(45.0f,22.0f,12.0f);

  glm::quat gq(glm::vec3(glm::radians(45.0f),glm::radians(22.0f),glm::radians(12.0f)));
  ASSERT_NEAR(q.getS(),gq.w,0.001f);
  ASSERT_NEAR(q.getX(),gq.x,0.001f);
  ASSERT_NEAR(q.getY(),gq.y,0.001f);
  ASSERT_NEAR(q.getZ(),gq.z,0.001f);
}

TEST(Quaternion,fromAxisAngle)
{
  ngl::Quaternion q;
  q.fromAxisAngle({1,0,0},45.0f);

  glm::quat gq=glm::angleAxis(glm::radians(45.0f),glm::vec3(1,0,0));
  ASSERT_NEAR(q.getS(),gq.w,0.001f);
  ASSERT_NEAR(q.getX(),gq.x,0.001f);
  ASSERT_NEAR(q.getY(),gq.y,0.001f);
  ASSERT_NEAR(q.getZ(),gq.z,0.001f);
}


TEST(Quaternion,toAxisAngle)
{
  ngl::Quaternion q;
  q.fromAxisAngle({1,0,0},45.0f);
  ngl::Vec3 axis;
  float angle;
  q.toAxisAngle(axis,angle);

  ASSERT_FLOAT_EQ(angle,45.0f);
  ASSERT_TRUE(axis == ngl::Vec3(1,0,0));
}

TEST(Quaternion,toMat4)
{
  ngl::Quaternion q;
  q.fromEulerAngles(45.0f,22.0f,12.0f);
  auto m1=q.toMat4();

  glm::quat gq(glm::vec3(glm::radians(45.0f),glm::radians(22.0f),glm::radians(12.0f)));
  auto m2=glm::toMat4(gq);
  for(size_t i=0; i<16; ++i)
  {
    EXPECT_NEAR(glm::value_ptr(m2)[i],m1.m_openGL[i],0.000001f);
  }
}


TEST(Quaternion,SLERP)
{
  ngl::Quaternion start(ngl::Vec3(45.0f,90.0f,80.0f));
  ngl::Quaternion end(ngl::Vec3(-300.0f,270.0f,360.0f));
  start.normalise();
  end.normalise();
  glm::quat gstart(glm::vec3(45.0f,90.0f,80.0f));
  glm::quat gend(glm::vec3(-300.0f,270.0f,360.0f));

  // for(float i=0.0f; i<=1.0f; i+=0.1f)
  // {
    float i=1.0f;
    auto s1=ngl::Quaternion::slerp(start,end,i);
    glm::quat s2=glm::slerp(gstart,gend,i);
    ASSERT_NEAR(s1.m_s,s2.w,0.001f);
    ASSERT_NEAR(s1.m_x,s2.x,0.001f);
    ASSERT_NEAR(s1.m_y,s2.y,0.001f);
    ASSERT_NEAR(s1.m_z,s2.z,0.001f);
    
  //}



}