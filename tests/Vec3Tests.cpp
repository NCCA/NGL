#include <glm/vec3.hpp>
#include <gtest/gtest.h>
#include <ngl/Mat3.h>
#include <ngl/Types.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <sstream>
#include <string>
#include <vector>
std::string print(const ngl::Vec3 &_m)
{
  std::stringstream ret;
  ret << '(';
  for(size_t i = 0; i < 3; ++i)
    ret << _m.m_openGL[i] << ',';
  ret << "\b)\n";
  return ret.str();
}

TEST(Vec3, DefaultCtor)
{
  ngl::Vec3 test;
  ngl::Vec3 result(0.0f, 0.0f, 0.0f);
  EXPECT_TRUE(test == result);
}

TEST(Vec3, VectorTest)
{
  std::vector< ngl::Vec3 > a(10);
  std::vector< ngl::Vec3 > b(10);
  float i = 0.0f;
  for(auto &v : a)
  {
    v.set(i, i + 1, i + 2);
    ++i;
  }
  for(size_t i = 0; i < a.size(); ++i)
  {
    b[i] = a[i];
  }
  for(size_t i = 0; i < a.size(); ++i)
  {
    EXPECT_FLOAT_EQ(a[i][0], b[i][0]);
    EXPECT_FLOAT_EQ(a[i][1], b[i][1]);
    EXPECT_FLOAT_EQ(a[i][2], b[i][2]);
    ASSERT_TRUE(a[i] == b[i]);
  }
}

TEST(Vec3, DotProduct)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(4.0f, 5.0f, 6.0f);
  ASSERT_FLOAT_EQ(a.dot(b), 32.0f);
}

TEST(Vec3, NULL)
{
  ngl::Vec3 test(1, 2, 4);
  test.null();
  ASSERT_TRUE(test == ngl::Vec3::zero());
}

TEST(Vec3, normalize)
{
  ngl::Vec3 test(22.3f, 0.5f, 10.0f);
  test.normalize();
  ngl::Vec3 result(0.912266f, 0.0204544f, 0.409088f);
  ASSERT_TRUE(test == result);
  auto zero=ngl::Vec3::zero();
  zero.normalize();
  ASSERT_TRUE(std::isnan(zero.m_x));
  ASSERT_TRUE(std::isnan(zero.m_y));
  ASSERT_TRUE(std::isnan(zero.m_z));

}

TEST(Vec3, Inner)
{
  ngl::Vec3 a(1.0, 2.0, 3.0);
  ngl::Vec3 b(3.0, 4.0, 5.0);
  ASSERT_FLOAT_EQ(a.inner(b), 26.0f);
}

TEST(Vec3, Outer)
{
  ngl::Vec3 a(1.0, 2.0, 3.0);
  ngl::Vec3 b(3.0, 4.0, 5.0);
  ngl::Mat3 outer = a.outer(b);
  ngl::Mat3 result(3, 4, 5, 6, 8, 10, 9, 12, 15);
  ASSERT_TRUE(outer == result);
}

TEST(Vec3, Length)
{
  ngl::Vec3 a(22, 1, 32);

  ASSERT_NEAR(a.length(), 38.845f, 0.001f);
}

TEST(Vec3, LengthSquared)
{
  ngl::Vec3 a(22, 1, 32);

  ASSERT_NEAR(a.lengthSquared(), 1509.0f, 0.001f);
}

TEST(Vec3, Cross2)
{
  ngl::Vec3 a = ngl::Vec3::up();
  ngl::Vec3 b = ngl::Vec3::left();
  ngl::Vec3 c;
  c.cross(a, b);
  ASSERT_TRUE(c == ngl::Vec3::in());
}

TEST(Vec3, Cross1)
{
  ngl::Vec3 a = ngl::Vec3::up();
  ngl::Vec3 b = ngl::Vec3::left();
  ngl::Vec3 c = a.cross(b);
  ASSERT_TRUE(c == ngl::Vec3::in());
}

TEST(Vec3, SubScript)
{
  ngl::Vec3 test(1.0f, 2.0f, 3.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1], 2.0f);
  EXPECT_FLOAT_EQ(test[2], 3.0f);
}

TEST(Vec3, FloatCtor)
{
  ngl::Vec3 test(1.0f, 2.0f, 3.0f);
  ngl::Vec3 result(1.0f, 2.0f, 3.0f);

  EXPECT_TRUE(test == result);
}

TEST(Vec3, CopyCtor)
{
  ngl::Vec3 test(1.0f, 2.0f, 3.0f);
  ngl::Vec3 copy(test);
  ngl::Vec3 result(1.0f, 2.0f, 3.0f);
  EXPECT_TRUE(copy == result);
}

TEST(Vec3, AssignOperator)
{
  ngl::Vec3 test(1.0f, 2.0f, 3.0f);
  ngl::Vec3 copy = test;
  ngl::Vec3 result(1.0f, 2.0f, 3.0f);
  EXPECT_TRUE(copy == result);
  EXPECT_FLOAT_EQ(test[0], copy[0]);
  EXPECT_FLOAT_EQ(test[1], copy[1]);
  EXPECT_FLOAT_EQ(test[2], copy[2]);

}

TEST(Vec3, fromGLM)
{
  glm::vec3 f(0.4f, 0.2f, 0.1f);
  ngl::Vec3 r(f);
  EXPECT_FLOAT_EQ(r[0], f[0]);
  EXPECT_FLOAT_EQ(r[1], f[1]);
  EXPECT_FLOAT_EQ(r[2], f[2]);
}

TEST(Vec3, toGLM)
{
  ngl::Vec3 f(0.4f, 0.2f, 0.1f);
  auto r = f.toGLM();
  EXPECT_FLOAT_EQ(r[0], f[0]);
  EXPECT_FLOAT_EQ(r[1], f[1]);
  EXPECT_FLOAT_EQ(r[2], f[2]);
}

TEST(Vec3, setGLM)
{
  ngl::Vec3 f;
  f.set(glm::vec3(0.4f, 0.2f, 0.1f));
  EXPECT_FLOAT_EQ(0.4f, f[0]);
  EXPECT_FLOAT_EQ(0.2f, f[1]);
  EXPECT_FLOAT_EQ(0.1f, f[2]);
}

TEST(Vec3,set)
{
  ngl::Vec3 v;
  v.set(ngl::Vec3(1.0f, 2.0f, 3.0f));
  EXPECT_FLOAT_EQ(v[0], 1.0f);
  EXPECT_FLOAT_EQ(v[1], 2.0f);
  EXPECT_FLOAT_EQ(v[2], 3.0f);
  v.set(ngl::Vec4(2.0f,3.0f,4.0f));
  EXPECT_FLOAT_EQ(v[0], 2.0f);
  EXPECT_FLOAT_EQ(v[1], 3.0f);
  EXPECT_FLOAT_EQ(v[2], 4.0f);
}

TEST(Vec3,negate)
{
  ngl::Vec3 v(1.0f,2.0f,3.0f);
  v=-v;
  EXPECT_FLOAT_EQ(v[0], -1.0f);
  EXPECT_FLOAT_EQ(v[1], -2.0f);
  EXPECT_FLOAT_EQ(v[2], -3.0f);
}

TEST(Vec3,equality)
{
  ngl::Vec3 v(1.0f,2.0f,3.0f);
  ngl::Vec3 v1(1.0f,2.0f,3.0f);
  EXPECT_TRUE(v==v1);
  EXPECT_FALSE(v!=v1);
  v1.set(2.0f,3.0f,4.0f);
  EXPECT_FALSE(v==v1);
  EXPECT_TRUE(v!=v1);
}

TEST(Vec3,multVec3)
{
  ngl::Vec3 v(1.0f,2.0f,3.0f);
  ngl::Vec3 v1(2.0f,3.0f,4.0f);
  v=v*v1;
  EXPECT_FLOAT_EQ(v[0], 2.0f);
  EXPECT_FLOAT_EQ(v[1], 6.0f);
  EXPECT_FLOAT_EQ(v[2], 12.0f);
}

TEST(Vec3, add)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(4.0f, 5.0f, 6.0f);
  auto c = a + b;
  EXPECT_FLOAT_EQ(c.m_x, 5.0f);
  EXPECT_FLOAT_EQ(c.m_y, 7.0f);
  EXPECT_FLOAT_EQ(c.m_z, 9.0f);
}

TEST(Vec3, addEqual)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(4.0f, 5.0f, 6.0f);
  a += b;
  EXPECT_FLOAT_EQ(a.m_x, 5.0f);
  EXPECT_FLOAT_EQ(a.m_y, 7.0f);
  EXPECT_FLOAT_EQ(a.m_z, 9.0f);
}

TEST(Vec3, subtract)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(4.0f, 5.0f, 6.0f);
  auto c = a - b;
  EXPECT_FLOAT_EQ(c.m_x, -3.0f);
  EXPECT_FLOAT_EQ(c.m_y, -3.0f);
  EXPECT_FLOAT_EQ(c.m_z, -3.0f);
}

TEST(Vec3, subtractEqual)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(4.0f, 5.0f, 6.0f);
  a -= b;
  EXPECT_FLOAT_EQ(a.m_x, -3.0f);
  EXPECT_FLOAT_EQ(a.m_y, -3.0f);
  EXPECT_FLOAT_EQ(a.m_z, -3.0f);
}

TEST(Vec3, multiplyFloat)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  auto c = a * 2.0f;
  EXPECT_FLOAT_EQ(c.m_x, 2.0f);
  EXPECT_FLOAT_EQ(c.m_y, 4.0f);
  EXPECT_FLOAT_EQ(c.m_z, 6.0f);
}

TEST(Vec3, multiplyFloatEqual)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  a *= 2.0f;
  EXPECT_FLOAT_EQ(a.m_x, 2.0f);
  EXPECT_FLOAT_EQ(a.m_y, 4.0f);
  EXPECT_FLOAT_EQ(a.m_z, 6.0f);
}

TEST(Vec3, divideFloatEqual)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  a /= 2.0f;
  EXPECT_FLOAT_EQ(a.m_x, 0.5f);
  EXPECT_FLOAT_EQ(a.m_y, 1.0f);
  EXPECT_FLOAT_EQ(a.m_z, 1.5f);
  a/=0.0f;
  EXPECT_TRUE(std::isinf(a.m_x));
  EXPECT_TRUE(std::isinf(a.m_y));
  EXPECT_TRUE(std::isinf(a.m_z));
  

}

TEST(Vec3, divideFloat)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  auto b = a / 2.0f;
  EXPECT_FLOAT_EQ(b.m_x, 0.5f);
  EXPECT_FLOAT_EQ(b.m_y, 1.0f);
  EXPECT_FLOAT_EQ(b.m_z, 1.5f);
  auto c=a/0.0f;
  EXPECT_TRUE(std::isinf(c.m_x));
  EXPECT_TRUE(std::isinf(c.m_y));
  EXPECT_TRUE(std::isinf(c.m_z));
}

TEST(Vec3, divideVec)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(2.0f, 2.0f, 2.0f);
  auto c = a / b;
  EXPECT_FLOAT_EQ(c.m_x, 0.5f);
  EXPECT_FLOAT_EQ(c.m_y, 1.0f);
  EXPECT_FLOAT_EQ(c.m_z, 1.5f);
  ngl::Vec3 d=a/ngl::Vec3::zero();
  EXPECT_TRUE(std::isinf(d.m_x));
  EXPECT_TRUE(std::isinf(d.m_y));
  EXPECT_TRUE(std::isinf(d.m_z));
}

TEST(Vec3, divideEqualVec)
{
  ngl::Vec3 a(1.0f, 2.0f, 3.0f);
  ngl::Vec3 b(2.0f, 2.0f, 2.0f);
  a /= b;
  EXPECT_FLOAT_EQ(a.m_x, 0.5f);
  EXPECT_FLOAT_EQ(a.m_y, 1.0f);
  EXPECT_FLOAT_EQ(a.m_z, 1.5f);
}

TEST(Vec3,reflect)
{
  ngl::Vec3 v(0.5f,0.5f,0.0f);
  ngl::Vec3 n(0.0f,1.0f,0.0f);
  ngl::Vec3 r=v.reflect(n);
  EXPECT_FLOAT_EQ(r.m_x,0.5f);
  EXPECT_FLOAT_EQ(r.m_y,-0.5f);  
  EXPECT_FLOAT_EQ(r.m_z,0.0f);
}


TEST(Vec3,clampMinMax)
{
  ngl::Vec3 a(-1.0f, 2.0f, 3.0f);
  a.clamp(0.0f,2.0f);
  EXPECT_FLOAT_EQ(a.m_x,0.0f);
  EXPECT_FLOAT_EQ(a.m_y,2.0f);
  EXPECT_FLOAT_EQ(a.m_z,2.0f);
}

TEST(Vec3,clampPlusMinus)
{
  ngl::Vec3 a(-4.0f, 2.5f, 3.0f);
  a.clamp(2.0f);
  EXPECT_FLOAT_EQ(a.m_x,-2.0f);
  EXPECT_FLOAT_EQ(a.m_y,2.0f);
  EXPECT_FLOAT_EQ(a.m_z,2.0f);
}