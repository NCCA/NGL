#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <gtest/gtest.h>
#include <ngl/Mat2.h>
#include <ngl/NGLStream.h>
#include <ngl/Vec2.h>
#include <sstream>
#include <string>

std::string print(const ngl::Mat2 &_m)
{
  std::stringstream ret;
  ret << '(';
  for(auto m : _m.m_openGL)
    ret << m << ',';
  ret << "\b)\n";
  return ret.str();
}

TEST(Mat2, DefaultCtor)
{
  ngl::Mat2 test;
  ngl::Mat2 result(1, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, null)
{
  ngl::Mat2 test;
  test.null();
  ngl::Mat2 result(0, 0, 0, 0);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, identity)
{
  ngl::Mat2 test;
  test.identity();
  ngl::Mat2 result(1, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, FloatCtor)
{
  ngl::Mat2 test(2.0);
  ngl::Mat2 result(2, 0, 0, 2);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, CopyCtor)
{
  ngl::Mat2 test(2.0);
  ngl::Mat2 copy(test);
  ngl::Mat2 result(2, 0, 0, 2);
  EXPECT_TRUE(copy == result);
}

TEST(Mat2, AssignOperator)
{
  ngl::Mat2 test(2.0f);
  ngl::Mat2 copy = test;
  ngl::Mat2 result(2, 0, 0, 2);
  EXPECT_TRUE(copy == result);
}

TEST(Mat2, setAtXY)
{
  ngl::Mat2 test;
  float value = 0.0f;
  for(int y = 0; y < 2; ++y)
    for(int x = 0; x < 2; ++x)
      test.m_m[x][y] = value++;

  ngl::Mat2 result(0, 2, 1, 3);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, transpose)
{
  ngl::Mat2 test(1, 2, 3, 4);
  test.transpose();
  ngl::Mat2 result(1, 3, 2, 4);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, scale)
{
  ngl::Mat2 test = ngl::Mat2::scale(1.0f, 2.0f);
  ngl::Mat2 result(1, 0, 0, 2);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, rotate)
{
  ngl::Mat2 test = ngl::Mat2::rotate(45.0f);
  ngl::Mat2 result(0.707107f, -0.707107f, 0.707107f, 0.707107f);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, Mat2xMat2)
{
  ngl::Mat2 t1(1, 2, 3, 4);
  ngl::Mat2 t2(5, 6, 7, 8);
  auto result = t1 * t2;
  EXPECT_TRUE(result == ngl::Mat2(19, 22, 43, 50));
}

TEST(Mat2, Mat2xeuqals)
{
  ngl::Mat2 t1(1, 2, 3, 4);
  ngl::Mat2 t2(5, 6, 7, 8);
  t1 *= t2;
  EXPECT_TRUE(t1 == ngl::Mat2(19, 22, 43, 50));
}

TEST(Mat2, Mat2plusEqual)
{
  ngl::Mat2 t1(1, 2, 3, 4);
  ngl::Mat2 t2(5, 6, 7, 8);
  t1 += t2;
  EXPECT_TRUE(t1 == ngl::Mat2(6, 8, 10, 12));
}

TEST(Mat2, Mat2plus)
{
  ngl::Mat2 t1(1, 2, 3, 4);
  ngl::Mat2 t2(5, 6, 7, 8);
  ngl::Mat2 res = t1 + t2;
  EXPECT_TRUE(res == ngl::Mat2(6, 8, 10, 12));
}

TEST(Mat2, Mat2xReal)
{
  ngl::Mat2 test;
  float value = 0.0f;
  for(int y = 0; y < 2; ++y)
    for(int x = 0; x < 2; ++x)
      test.m_m[x][y] = value++;
  test = test * 4.2f;
  auto result = ngl::Mat2(0.0f, 8.399999618530f, 4.199999809265f, 12.599999427795f);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, Mat2xEqualReal)
{
  ngl::Mat2 test;
  float value = 0.0f;
  for(int y = 0; y < 2; ++y)
    for(int x = 0; x < 2; ++x)
      test.m_m[x][y] = value++;
  test *= 4.2f;
  auto result = ngl::Mat2(0.0f, 8.399999618530f, 4.199999809265f, 12.599999427795f);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, Vec2xMat2)
{
  ngl::Mat2 t1(1, 2, 3, 4);
  ngl::Vec2 test(1, 2);
  test = t1 * test;
  ngl::Vec2 result(5, 11);
  EXPECT_TRUE(test == result);
}

TEST(Mat2, glm)
{
  glm::mat2 g1(1, 2, 3, 4);
  ngl::Mat2 n1(g1);
  EXPECT_TRUE(g1[0][0] == n1.m_00);
  EXPECT_TRUE(g1[0][1] == n1.m_01);
  EXPECT_TRUE(g1[1][0] == n1.m_10);
  EXPECT_TRUE(g1[1][1] == n1.m_11);
  auto g2=n1.toGLM();
  EXPECT_TRUE(g1==g2);
}