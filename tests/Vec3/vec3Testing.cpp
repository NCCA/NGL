#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec3.h>
#include <ngl/Mat3.h>
#include <string>
#include <sstream>
#include <vector>
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string print(const ngl::Vec3 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<3; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(NGLVec3,DefaultCtor)
{
  ngl::Vec3 test;
  ngl::Vec3 result(0.0f,0.0f,0.0f);
  EXPECT_TRUE(test == result);
}

TEST(NGLVec3,VectorTest)
{
  std::vector<ngl::Vec3> a(10);
  std::vector<ngl::Vec3> b(10);
  float i=0.0f;
  for(auto &v : a)
  {
    v.set(i,i+1,i+2);
  ++i;
  }
  for(size_t i=0; i<a.size(); ++i)
  {
    b[i]=a[i];
  }
  for(size_t i=0; i<a.size(); ++i)
  {
    EXPECT_FLOAT_EQ(a[i][0], b[i][0]);
    EXPECT_FLOAT_EQ(a[i][1],b[i][1]);
    EXPECT_FLOAT_EQ(a[i][2], b[i][2]);
    ASSERT_TRUE(a[i]==b[i]);
  }

}

TEST(NGLVec3,DotProduct)
{
  ngl::Vec3 a(1.0f,2.0f,3.0f);
  ngl::Vec3 b(4.0f,5.0f,6.0f);
  ASSERT_FLOAT_EQ(a.dot(b),32.0f);
}

TEST(NGLVec3,NULL)
{
  ngl::Vec3 test(1,2,4);
  test.null();
  ASSERT_TRUE(test==ngl::Vec3::zero());
}

TEST(NGLVec3,normalize)
{
  ngl::Vec3 test(22.3f,0.5f,10.0f);
  test.normalize();
  ngl::Vec3 result(0.912266f,0.0204544f,0.409088f);
  ASSERT_TRUE(test==result);

}


TEST(NGLVec3,Inner)
{
  ngl::Vec3 a(1.0,2.0,3.0);
  ngl::Vec3 b(3.0,4.0,5.0);
  ASSERT_FLOAT_EQ(a.inner(b),26.0f);
}

TEST(NGLVec3,Outer)
{
  ngl::Vec3 a(1.0,2.0,3.0);
  ngl::Vec3 b(3.0,4.0,5.0);
  ngl::Mat3 outer=a.outer(b);
  ngl::Mat3 result(3,4,5,6,8,10,9,12,15);
  ASSERT_TRUE(outer==result);
}

TEST(NGLVec3,Length)
{
  ngl::Vec3 a(22,1,32);

  ASSERT_NEAR(a.length(),38.845f,0.001f);
}

TEST(NGLVec3,LengthSquared)
{
  ngl::Vec3 a(22,1,32);

  ASSERT_NEAR(a.lengthSquared(),1509.0f,0.001f);
}

TEST(NGLVec3,Cross2)
{
  ngl::Vec3 a=ngl::Vec3::up();
  ngl::Vec3 b=ngl::Vec3::left();
  ngl::Vec3 c;
  c.cross(a,b);
  ASSERT_TRUE(c==ngl::Vec3::in());
}

TEST(NGLVec3,Cross1)
{
  ngl::Vec3 a=ngl::Vec3::up();
  ngl::Vec3 b=ngl::Vec3::left();
  ngl::Vec3 c=a.cross(b);
  ASSERT_TRUE(c==ngl::Vec3::in());
}

TEST(NGLVec3,SubScript)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1],2.0f);
  EXPECT_FLOAT_EQ(test[2], 3.0f);

}



TEST(NGLVec3,FloatCtor)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 result(1.0f,2.0f,3.0f);

  EXPECT_TRUE(test == result);
}


TEST(NGLVec3,CopyCtor)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 copy(test);
  ngl::Vec3 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}

TEST(NGLVec3,AssignOperator)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 copy=test;
  ngl::Vec3 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
  EXPECT_FLOAT_EQ(test[0], copy[0]);
  EXPECT_FLOAT_EQ(test[1], copy[1]);
  EXPECT_FLOAT_EQ(test[2], copy[2]);

}
