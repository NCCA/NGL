#include <glm/vec4.hpp>
#include <gtest/gtest.h>
#include <ngl/Mat4.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <ngl/Util.h>
#include <sstream>
#include <string>

std::string print(const ngl::Vec4 &_m)
{
  std::stringstream ret;
  ret << '(';
  for(size_t i = 0; i < 4; ++i)
    ret << _m.m_openGL[i] << ',';
  ret << "\b)\n";
  return ret.str();
}

TEST(Vec4, DefaultCtor)
{
  ngl::Vec4 test;
  ngl::Vec4 result(0.0f, 0.0f, 0.0f, 1.0);
  EXPECT_TRUE(test == result);
}

TEST(Vec4, SubScript)
{
  ngl::Vec4 test(1.0f, 2.0f, 3.0f, 4.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1], 2.0f);
  EXPECT_FLOAT_EQ(test[2], 3.0f);
  EXPECT_FLOAT_EQ(test[3], 4.0f);
}

TEST(Vec4,assign)
{
  auto v=ngl::Vec4();
  v=ngl::Vec4(1.0f,2.0f,3.0f,4.0f);
  EXPECT_FLOAT_EQ(v.m_x,1.0f);
  EXPECT_FLOAT_EQ(v.m_y,2.0f);
  EXPECT_FLOAT_EQ(v.m_z,3.0f);
  EXPECT_FLOAT_EQ(v.m_w,4.0f);
  v=ngl::Vec3(6.0f,7.0f,8.0f);
  EXPECT_FLOAT_EQ(v.m_x,6.0f);
  EXPECT_FLOAT_EQ(v.m_y,7.0f);
  EXPECT_FLOAT_EQ(v.m_z,8.0f);
  EXPECT_FLOAT_EQ(v.m_w,0.0f);
}

TEST(Vec4, FloatCtor)
{
  ngl::Vec4 test(1.0f, 2.0f, 3.0f, 4.0f);
  ngl::Vec4 result(1.0f, 2.0f, 3.0f, 4.0f);

  EXPECT_TRUE(test == result);
}

TEST(Vec4, CopyCtor)
{
  ngl::Vec4 test(1.0f, 2.0f, 3.0f, 5.0f);
  ngl::Vec4 copy(test);
  ngl::Vec4 result(1.0f, 2.0f, 3.0f, 5.0f);
  EXPECT_TRUE(copy == result);
}

TEST(Vec4, AssignOperator)
{
  ngl::Vec4 test(1.0f, 2.0f, 3.0f);
  ngl::Vec4 copy = test;
  ngl::Vec4 result(1.0f, 2.0f, 3.0f);
  EXPECT_TRUE(copy == result);
}

TEST(Vec4,negate)
{
  ngl::Vec4 a(1,2,3,1);
  a=-a;
  EXPECT_FLOAT_EQ(a.m_x,-1.0f);
  EXPECT_FLOAT_EQ(a.m_y,-2.0f);
  EXPECT_FLOAT_EQ(a.m_z,-3.0f);
  EXPECT_FLOAT_EQ(a.m_w,1.0f);
}

TEST(Vec4,notEqual)
{
  ngl::Vec4 a(1,2,3,1);
  ngl::Vec4 b(1,2,3,1);
  EXPECT_TRUE(a==b);
  b.m_x=0.0f;
  EXPECT_TRUE(a!=b);
}

TEST(Vec4,multVec4)
{
  ngl::Vec4 a(1,2,3,1);
  ngl::Vec4 b(2,2,2,1);
  a=a*b;
  EXPECT_FLOAT_EQ(a.m_x,2.0f);
  EXPECT_FLOAT_EQ(a.m_y,4.0f);
  EXPECT_FLOAT_EQ(a.m_z,6.0f);
  EXPECT_FLOAT_EQ(a.m_w,1.0f);
}

TEST(Vec4,angleBetween)
{
  ngl::Vec4 a(1,0,0,1);
  ngl::Vec4 b(0,1,0,1);

  EXPECT_FLOAT_EQ(a.angleBetween(b),90.0f);
  EXPECT_FLOAT_EQ(a.angleBetween(a),0.0f);
}

TEST(Vec4, VectorTest)
{
  std::vector< ngl::Vec4 > a(10);
  std::vector< ngl::Vec4 > b(10);
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
    EXPECT_FLOAT_EQ(a[i][3], b[i][3]);
    ASSERT_TRUE(a[i] == b[i]);
  }
}

TEST(Vec4, DotProduct)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f);
  ngl::Vec4 b(4.0f, 5.0f, 6.0f);
  ASSERT_FLOAT_EQ(a.dot(b), 32.0f);
}

TEST(Vec4, NULL)
{
  ngl::Vec4 test(1, 2, 4);
  test.null();
  ASSERT_TRUE(test == ngl::Vec4::zero());
}

TEST(Vec4, normalize)
{
  ngl::Vec4 test(22.3f, 0.5f, 10.0f);
  test.normalize();
  ngl::Vec4 result(0.912266f, 0.0204544f, 0.409088f);
  ASSERT_TRUE(test == result);
  auto zero=ngl::Vec4::zero();
  zero.normalize();
  ASSERT_TRUE(std::isnan(zero.m_x));
  ASSERT_TRUE(std::isnan(zero.m_y));
  ASSERT_TRUE(std::isnan(zero.m_z));

}

TEST(Vec4, Inner)
{
  ngl::Vec4 a(1.0, 2.0, 3.0);
  ngl::Vec4 b(3.0, 4.0, 5.0);
  ASSERT_FLOAT_EQ(a.inner(b), 26.0f);
}

TEST(Vec4, Outer)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
  ngl::Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
  ngl::Mat4 outer = a.outer(b);
  ngl::Mat4 result(5, 6, 7, 8, 10, 12, 14, 16, 15, 18, 21, 24, 20, 24, 28, 32);
  ASSERT_TRUE(outer == result);
}

TEST(Vec4, Length)
{
  ngl::Vec4 a(22, 1, 32);

  ASSERT_NEAR(a.length(), 38.845f, 0.001f);
}

TEST(Vec4, LengthSquared)
{
  ngl::Vec4 a(22, 1, 32);

  ASSERT_NEAR(a.lengthSquared(), 1509.0f, 0.001f);
}

TEST(Vec4, Cross2)
{
  ngl::Vec4 a = ngl::Vec4::up();
  ngl::Vec4 b = ngl::Vec4::left();
  ngl::Vec4 c;
  c.cross(a, b);
  ASSERT_TRUE(c == ngl::Vec4::in());
}

TEST(Vec4, Cross1)
{
  ngl::Vec4 a = ngl::Vec4::up();
  ngl::Vec4 b = ngl::Vec4::left();
  ngl::Vec4 c = a.cross(b);
  ASSERT_TRUE(c == ngl::Vec4::in());
}

TEST(Vec4, fromGLM)
{
  glm::vec4 f(0.4f, 0.2f, 0.1f, 1.0f);
  ngl::Vec4 r(f);
  EXPECT_FLOAT_EQ(r[0], f[0]);
  EXPECT_FLOAT_EQ(r[1], f[1]);
  EXPECT_FLOAT_EQ(r[2], f[2]);
  EXPECT_FLOAT_EQ(r[3], f[3]);
}

TEST(Vec4, toGLM)
{
  ngl::Vec4 f(0.4f, 0.2f, 0.1f, 1.0f);
  auto r = f.toGLM();
  EXPECT_FLOAT_EQ(r[0], f[0]);
  EXPECT_FLOAT_EQ(r[1], f[1]);
  EXPECT_FLOAT_EQ(r[2], f[2]);
  EXPECT_FLOAT_EQ(r[3], f[3]);
}

TEST(Vec4, setGLM)
{
  ngl::Vec4 f;
  f.set(glm::vec4(0.4f, 0.2f, 0.1f, 1.0f));
  EXPECT_FLOAT_EQ(0.4f, f[0]);
  EXPECT_FLOAT_EQ(0.2f, f[1]);
  EXPECT_FLOAT_EQ(0.1f, f[2]);
  EXPECT_FLOAT_EQ(1.0f, f[3]);
}

TEST(Vec4,setVec4)
{
  ngl::Vec4 f;
  f.set(ngl::Vec4(0.4f, 0.2f, 0.1f, 1.0f));
  EXPECT_FLOAT_EQ(0.4f, f[0]);
  EXPECT_FLOAT_EQ(0.2f, f[1]);
  EXPECT_FLOAT_EQ(0.1f, f[2]);
  EXPECT_FLOAT_EQ(1.0f, f[3]);
}


TEST(Vec4,setVec3)
{
  ngl::Vec4 f;
  f.set(ngl::Vec3(0.4f, 0.2f, 0.1f));
  EXPECT_FLOAT_EQ(0.4f, f[0]);
  EXPECT_FLOAT_EQ(0.2f, f[1]);
  EXPECT_FLOAT_EQ(0.1f, f[2]);
  EXPECT_FLOAT_EQ(1.0f, f[3]);
}




TEST(Vec4, add)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  ngl::Vec4 b(4.0f, 5.0f, 6.0f, 1.0f);
  auto c = a + b;
  EXPECT_FLOAT_EQ(c.m_x, 5.0f);
  EXPECT_FLOAT_EQ(c.m_y, 7.0f);
  EXPECT_FLOAT_EQ(c.m_z, 9.0f);
  EXPECT_FLOAT_EQ(c.m_w, 1.0f);
}

TEST(Vec4, addEqual)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
  ngl::Vec4 b(4.0f, 5.0f, 6.0f, 1.0f);
  a += b;
  EXPECT_FLOAT_EQ(a.m_x, 5.0f);
  EXPECT_FLOAT_EQ(a.m_y, 7.0f);
  EXPECT_FLOAT_EQ(a.m_z, 9.0f);
  EXPECT_FLOAT_EQ(a.m_w, 0.0f);
}

TEST(Vec4, subtract)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  ngl::Vec4 b(4.0f, 5.0f, 6.0f, 2.0f);
  auto c = a - b;
  EXPECT_FLOAT_EQ(c.m_x, -3.0f);
  EXPECT_FLOAT_EQ(c.m_y, -3.0f);
  EXPECT_FLOAT_EQ(c.m_z, -3.0f);
  EXPECT_FLOAT_EQ(c.m_w, 1.0f);
}

TEST(Vec4, subtractEqual)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
  ngl::Vec4 b(4.0f, 5.0f, 6.0f, 1.0f);
  a -= b;
  EXPECT_FLOAT_EQ(a.m_x, -3.0f);
  EXPECT_FLOAT_EQ(a.m_y, -3.0f);
  EXPECT_FLOAT_EQ(a.m_z, -3.0f);
  EXPECT_FLOAT_EQ(a.m_w, 0.0f);
}

TEST(Vec4, multiplyFloat)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  auto c = a * 2.0f;
  EXPECT_FLOAT_EQ(c.m_x, 2.0f);
  EXPECT_FLOAT_EQ(c.m_y, 4.0f);
  EXPECT_FLOAT_EQ(c.m_z, 6.0f);
  EXPECT_FLOAT_EQ(c.m_w, 1.0f);
}

TEST(Vec4, multiplyFloatEqual)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
  a *= 2.0f;
  EXPECT_FLOAT_EQ(a.m_x, 2.0f);
  EXPECT_FLOAT_EQ(a.m_y, 4.0f);
  EXPECT_FLOAT_EQ(a.m_z, 6.0f);
  EXPECT_FLOAT_EQ(a.m_w, 0.0f);
}

TEST(Vec4, divideFloatEqual)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  a /= 2.0f;
  EXPECT_FLOAT_EQ(a.m_x, 0.5f);
  EXPECT_FLOAT_EQ(a.m_y, 1.0f);
  EXPECT_FLOAT_EQ(a.m_z, 1.5f);
  EXPECT_FLOAT_EQ(a.m_w, 1.0f);
  a/=0.0f;
  EXPECT_TRUE(std::isinf(a.m_x));
  EXPECT_TRUE(std::isinf(a.m_y));
  EXPECT_TRUE(std::isinf(a.m_z));

}

TEST(Vec4, divideFloat)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  auto b = a / 2.0f;
  EXPECT_FLOAT_EQ(b.m_x, 0.5f);
  EXPECT_FLOAT_EQ(b.m_y, 1.0f);
  EXPECT_FLOAT_EQ(b.m_z, 1.5f);
  EXPECT_FLOAT_EQ(b.m_w, 1.0f);
  auto c=a/0.0f;
  EXPECT_TRUE(std::isinf(c.m_x));
  EXPECT_TRUE(std::isinf(c.m_y));
  EXPECT_TRUE(std::isinf(c.m_z));
}

TEST(Vec4, divideVec)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 1.0f);
  ngl::Vec4 b(2.0f, 2.0f, 2.0f, 1.0f);
  auto c = a / b;
  EXPECT_FLOAT_EQ(c.m_x, 0.5f);
  EXPECT_FLOAT_EQ(c.m_y, 1.0f);
  EXPECT_FLOAT_EQ(c.m_z, 1.5f);
  EXPECT_FLOAT_EQ(c.m_w, 1.0f);
}

TEST(Vec4, divideEqualVec)
{
  ngl::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
  ngl::Vec4 b(2.0f, 2.0f, 2.0f, 1.0f);
  a /= b;
  EXPECT_FLOAT_EQ(a.m_x, 0.5f);
  EXPECT_FLOAT_EQ(a.m_y, 1.0f);
  EXPECT_FLOAT_EQ(a.m_z, 1.5f);
  EXPECT_FLOAT_EQ(a.m_w, 0.0f);
  auto d=a/ngl::Vec4::zero();
  EXPECT_TRUE(std::isinf(d.m_x));
  EXPECT_TRUE(std::isinf(d.m_y));
  EXPECT_TRUE(std::isinf(d.m_z));

}

TEST(Vec4,clampMinMax)
{
  ngl::Vec4 a(-1.0f, 2.0f, 3.0f, 0.0f);
  a.clamp(0.0f,2.0f);
  EXPECT_FLOAT_EQ(a.m_x,0.0f);
  EXPECT_FLOAT_EQ(a.m_y,2.0f);
  EXPECT_FLOAT_EQ(a.m_z,2.0f);
  EXPECT_FLOAT_EQ(a.m_w,0.0f);
}

TEST(Vec4,clampPlusMinus)
{
  ngl::Vec4 a(-4.0f, 2.5f, 3.0f, 0.0f);
  a.clamp(2.0f);
  EXPECT_FLOAT_EQ(a.m_x,-2.0f);
  EXPECT_FLOAT_EQ(a.m_y,2.0f);
  EXPECT_FLOAT_EQ(a.m_z,2.0f);
  EXPECT_FLOAT_EQ(a.m_w,0.0f);
}