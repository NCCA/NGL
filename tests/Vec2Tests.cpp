#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec2.h>
#include <ngl/Mat3.h>
#include <string>
#include <sstream>
#include <vector>
#include <glm/vec2.hpp>
std::string print(const ngl::Vec2 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<2; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(Vec2,DefaultCtor)
{
  ngl::Vec2 test;
  ngl::Vec2 result(0.0f,0.0f);
  EXPECT_TRUE(test == result);
}

TEST(Vec2,VectorTest)
{
  std::vector<ngl::Vec2> a(10);
  std::vector<ngl::Vec2> b(10);
  float i=0.0f;
  for(auto &v : a)
  {
    v.set(i,i+1);
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
    ASSERT_TRUE(a[i]==b[i]);
  }

}

TEST(Vec2,DotProduct)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(4.0f,5.0f);
  ASSERT_FLOAT_EQ(a.dot(b),14.0f);
}

TEST(Vec2,NULL)
{
  ngl::Vec2 test(1,2);
  test.null();
  ASSERT_TRUE(test==ngl::Vec2::zero());
}

TEST(Vec2,normalize)
{
  ngl::Vec2 test(22.3f,0.5f);
  test.normalize();
  ngl::Vec2 result(0.9997f,0.0224f);
  ASSERT_TRUE(test==result);

}



TEST(Vec2,Length)
{
  ngl::Vec2 a(22,1);

  ASSERT_NEAR(a.length(),22.022f,0.01f);
}

TEST(Vec2,LengthSquared)
{
  ngl::Vec2 a(22,1);

  ASSERT_NEAR(a.lengthSquared(),485.0f,0.01f);
}


TEST(Vec2,SubScript)
{
  ngl::Vec2 test(1.0f,2.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1],2.0f);
}



TEST(Vec2,FloatCtor)
{
  ngl::Vec2 test(1.0f,2.0f);
  ngl::Vec2 result(1.0f,2.0f);
  EXPECT_TRUE(test == result);
}


TEST(Vec2,CopyCtor)
{
  ngl::Vec2 test(1.0f,2.0f);
  ngl::Vec2 copy(test);
  ngl::Vec2 result(1.0f,2.0f);
  EXPECT_TRUE(copy == result);
}

TEST(Vec2,AssignOperator)
{
  ngl::Vec2 test(1.0f,2.0f);
  ngl::Vec2 copy=test;
  ngl::Vec2 result(1.0f,2.0f);
  EXPECT_TRUE(copy == result);
  EXPECT_FLOAT_EQ(test[0], copy[0]);
  EXPECT_FLOAT_EQ(test[1], copy[1]);
}

TEST(Vec2,fromGLM)
{
  glm::vec2 f(0.4f,0.2f);
  ngl::Vec2 r(f);
  EXPECT_FLOAT_EQ(r[0],f[0]);
  EXPECT_FLOAT_EQ(r[1],f[1]);
}


TEST(Vec2,toGLM)
{
  ngl::Vec2 f(0.4f,0.2f);
  auto r=f.toGLM();
  EXPECT_FLOAT_EQ(r[0],f[0]);
  EXPECT_FLOAT_EQ(r[1],f[1]);

}

TEST(Vec2,setGLM)
{
  ngl::Vec2 f;
  f.set(glm::vec2(0.4f,0.2f));
  EXPECT_FLOAT_EQ(0.4f,f[0]);
  EXPECT_FLOAT_EQ(0.2f,f[1]);

}


TEST(Vec2,add)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,3.0f);
  auto c=a+b;
  EXPECT_FLOAT_EQ(c.m_x,3.0f);
  EXPECT_FLOAT_EQ(c.m_y,5.0f);
}


TEST(Vec2,addEqual)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,3.0f);
  a+=b;
  EXPECT_FLOAT_EQ(a.m_x,3.0f);
  EXPECT_FLOAT_EQ(a.m_y,5.0f);
}

TEST(Vec2,subtract)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,3.0f);
  auto c=a-b;
  EXPECT_FLOAT_EQ(c.m_x,-1.0f);
  EXPECT_FLOAT_EQ(c.m_y,-1.0f);
}


TEST(Vec2,subtractEqual)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,3.0f);
  a-=b;
  EXPECT_FLOAT_EQ(a.m_x,-1.0f);
  EXPECT_FLOAT_EQ(a.m_y,-1.0f);
}


TEST(Vec2,multiplyFloat)
{
  ngl::Vec2 a(1.0f,2.0f);
  auto c=a*2.0f;
  EXPECT_FLOAT_EQ(c.m_x,2.0f);
  EXPECT_FLOAT_EQ(c.m_y,4.0f);
}


TEST(Vec2,multiplyFloatEqual)
{
  ngl::Vec2 a(1.0f,2.0f);
  a*=2.0f;
  EXPECT_FLOAT_EQ(a.m_x,2.0f);
  EXPECT_FLOAT_EQ(a.m_y,4.0f);
}

TEST(Vec2,divideFloatEqual)
{
  ngl::Vec2 a(1.0f,2.0f);
  a/=2.0f;
  EXPECT_FLOAT_EQ(a.m_x,0.5f);
  EXPECT_FLOAT_EQ(a.m_y,1.0f);
}

TEST(Vec2,divideFloat)
{
  ngl::Vec2 a(1.0f,2.0f);
  auto b=a/2.0f;
  EXPECT_FLOAT_EQ(b.m_x,0.5f);
  EXPECT_FLOAT_EQ(b.m_y,1.0f);
}


TEST(Vec2,divideVec)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,2.0f);
  auto c=a/b;
  EXPECT_FLOAT_EQ(c.m_x,0.5f);
  EXPECT_FLOAT_EQ(c.m_y,1.0f);
}

TEST(Vec2,divideEqualVec)
{
  ngl::Vec2 a(1.0f,2.0f);
  ngl::Vec2 b(2.0f,2.0f);
  a/=b;
  EXPECT_FLOAT_EQ(a.m_x,0.5f);
  EXPECT_FLOAT_EQ(a.m_y,1.0f);
}
