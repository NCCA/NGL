#include <gtest/gtest.h>
#include <ngl/Util.h>
#include <ngl/Types.h>
#include <ngl/Mat4.h>
#include <ngl/Quaternion.h>
#include <sstream>
#include <ngl/NGLStream.h>

// use here https://www.vcalc.com/equation/?uuid=73f543b2-75f5-11e6-9770-bc764e2038f2 for verification

TEST(Quaternion,DefaultCtor)
{
  ngl::Quaternion test;
  EXPECT_FLOAT_EQ(test.getS(),1.0f);
  EXPECT_FLOAT_EQ(test.getX(),0.0f);
  EXPECT_FLOAT_EQ(test.getY(),0.0f);
  EXPECT_FLOAT_EQ(test.getZ(),0.0f);
}

TEST(Quaternion,UserCtor)
{
  ngl::Quaternion test(0.2f,0.0f,1.0f,0.0f);
  EXPECT_FLOAT_EQ(test.getS(),0.2f);
  EXPECT_FLOAT_EQ(test.getX(),0.0f);
  EXPECT_FLOAT_EQ(test.getY(),1.0f);
  EXPECT_FLOAT_EQ(test.getZ(),0.0f);
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
  std::cout<<test;
  ASSERT_NEAR(test.getS(),0.7071f,0.001f);
  ASSERT_NEAR(test.getX(),0.0f,0.001f);
  ASSERT_NEAR(test.getY(),0.7071f,0.001f);
  ASSERT_NEAR(test.getZ(),0.0f,0.001f);
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
}

TEST(Quaternion,magnitude)
{
  ngl::Quaternion q1(1.3f,3.0f,36.7f,-6.6f);
  EXPECT_FLOAT_EQ(q1.magnitude(),37.4318f);
}

TEST(Quaternion,normalize)
{
  ngl::Quaternion q1(1.3f,3.0f,36.7f,-6.6f);
  q1.normalise();
  //0.0347298 + 0.0801457i + 0.98045j - 0.176321k

  ASSERT_NEAR(q1.getS(),0.0347298,0.001f);
  ASSERT_NEAR(q1.getX(),0.0801457f,0.001f);
  ASSERT_NEAR(q1.getY(),0.98045f,0.001f);
  ASSERT_NEAR(q1.getZ(),-0.176321f,0.001f);
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
}

TEST(Quaternion,inverse)
{

  ngl::Quaternion q1(1.3f,-3.0f,-36.7f,6.6f);
  q1=q1.inverse();
  ASSERT_NEAR(q1.getS(),0.000927816f,0.01f);
  ASSERT_NEAR(q1.getX(),0.00214111f,0.01f);
  ASSERT_NEAR(q1.getY(),0.026193f,0.01f);
  ASSERT_NEAR(q1.getZ(),0.00471045f,0.01f);
}


