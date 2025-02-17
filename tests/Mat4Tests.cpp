#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/mat4x4.hpp>
#include <gtest/gtest.h>
#include <ngl/Mat4.h>
#include <ngl/Quaternion.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <sstream>
#include <string>

std::string print(const ngl::Mat4 &_m)
{
  std::stringstream ret;
  ret << '(';
  for(size_t i = 0; i < 16; ++i)
    ret << _m.m_openGL[i] << ',';
  ret << "\b)\n";
  return ret.str();
}

TEST(Mat4, DefaultCtor)
{
  ngl::Mat4 test;
  ngl::Mat4 result(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, null)
{
  ngl::Mat4 test;
  test.null();
  ngl::Mat4 result(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, buildFromArray)
{
  float m[4][4]={{1.0f,2.0f,3.0f,4.0f},
                 {5.0f,6.0f,7.0f,8.0f},
                 {9.0f,10.0f,11.0f,12.0f},
                 {13.0f,14.0f,15.0f,16.0f}};
  ngl::Mat4 test(m);
  for(size_t i=0; i<16; ++i)
  {
    EXPECT_FLOAT_EQ(test.m_openGL[i],i+1);
  }
}

TEST(Mat4, identity)
{
  ngl::Mat4 test;
  test.identity();
  ngl::Mat4 result(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, FloatCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 result(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, CopyCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy(test);
  ngl::Mat4 result(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1);
  EXPECT_TRUE(copy == result);
}

TEST(Mat4, AssignOperator)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy = test;
  ngl::Mat4 result(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1);
  EXPECT_TRUE(copy == result);
}

TEST(Mat4, setAtXY)
{
  ngl::Mat4 test;
  float value = 0.0f;
  for(int y = 0; y < 4; ++y)
    for(int x = 0; x < 4; ++x)
      test.m_m[x][y] = value++;
  //#test.setAtXY(x, y, value++);
  ngl::Mat4 result(0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, translate)
{
  ngl::Mat4 test = ngl::Mat4::translate(1.0f, 2.0f, 3.0f);
  ngl::Mat4 result(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 3, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, transpose)
{
  ngl::Mat4 test = ngl::Mat4::translate(1.0f, 2.0f, 3.0f);
  test.transpose();
  ngl::Mat4 result(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, scale)
{
  ngl::Mat4 test = ngl::Mat4::scale(1.0f, 2.0f, 3.0f);
  ngl::Mat4 result(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, rotateX)
{
  for(float r = -360.0f; r < 360.0f; r += 1.0f)
  {
    ngl::Mat4 test = ngl::Mat4::rotateX(r);

    auto res = glm::rotate(glm::mat4(1.0f), glm::radians(r), glm::vec3(1, 0, 0));
    for(size_t i = 0; i < 16; ++i)
    {
      EXPECT_NEAR(glm::value_ptr(res)[i], test.m_openGL[i], 0.000001f);
    }
  }
}

TEST(Mat4, rotateY)
{
  for(float r = -360.0f; r < 360.0f; r += 1.0f)
  {
    ngl::Mat4 test = ngl::Mat4::rotateY(r);
    auto res = glm::rotate(glm::mat4(1.0f), glm::radians(r), glm::vec3(0, 1, 0));
    for(size_t i = 0; i < 16; ++i)
    {
      EXPECT_NEAR(glm::value_ptr(res)[i], test.m_openGL[i], 0.000001f);
    }
  }
}
TEST(Mat4, rotateZ)
{
  for(float r = -360.0f; r < 360.0f; r += 1.0f)
  {

    ngl::Mat4 test = ngl::Mat4::rotateZ(r);
    auto res = glm::rotate(glm::mat4(1.0f), glm::radians(r), glm::vec3(0, 0, 1));
    for(size_t i = 0; i < 16; ++i)
    {
      EXPECT_NEAR(glm::value_ptr(res)[i], test.m_openGL[i], 0.000001f);
    }
  }
}
TEST(Mat4, Mat4xMat4)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  ngl::Mat4 test = t2 * t1;
  ngl::Mat4 result(0.819152f, 0, -0.573577f, 0, 0.40558f, 0.707107f, 0.579228f, 0, 0.40558f, -0.707107f, 0.579228f, 0, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, Mat4xeuqals)
{
  ngl::Mat4 test = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  test *= t2;
  ngl::Mat4 result(0.819152f, 0.40558f, -0.40558f, 0, 0, 0.707107f, 0.707107f, 0, 0.573577f, -0.579228f, 0.579228f, 0, 0, 0, 0, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, Mat4xeuqals2)
{
  ngl::Mat4 test = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  test *= t2;
  ngl::Mat4 r = ngl::Mat4::rotateX(45.0f);
  EXPECT_TRUE(test == (r * t2));
}

TEST(Mat4, Mat4pluEqual)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  t1 += t2;
  ngl::Mat4 result(1.81915f, 0, -0.573577f, 0, 0, 1.70711f, 0.707107f, 0, 0.573577f, -0.707107f, 1.52626f, 0, 0, 0, 0, 2);

  EXPECT_TRUE(t1 == result);
}

TEST(Mat4, Mat4plus)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  ;
  ngl::Mat4 res;
  res = t1 + t2;
  ngl::Mat4 result(1.81915f, 0, -0.573577f, 0, 0, 1.70711f, 0.707107f, 0, 0.573577f, -0.707107f, 1.52626f, 0, 0, 0, 0, 2);

  EXPECT_TRUE(res == result);
}

TEST(Mat4, Mat4xReal)
{
  ngl::Mat4 test;
  float value = 0.0f;
  for(int y = 0; y < 4; ++y)
    for(int x = 0; x < 4; ++x)
      test.m_m[x][y] = value++;
  test = test * 4.2f;
  ngl::Mat4 result(0, 16.8f, 33.6f, 50.4f, 4.2f, 21, 37.8f, 54.6f, 8.4f, 25.2f, 42, 58.8f, 12.6f, 29.4f, 46.2f, 63);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, Mat4xEqualReal)
{
  ngl::Mat4 test;
  float value = 0.0f;
  for(int y = 0; y < 4; ++y)
    for(int x = 0; x < 4; ++x)
      test.m_m[x][y] = value++;
  // test.setAtXY(x, y, float(value++));
  test *= 4.2f;
  ngl::Mat4 result(0, 16.8f, 33.6f, 50.4f, 4.2f, 21, 37.8f, 54.6f, 8.4f, 25.2f, 42, 58.8f, 12.6f, 29.4f, 46.2f, 63);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, determinant)
{
  // note value 5.0 is verified by wolfram alpha
  ngl::Mat4 test(1, 0, 0, 0, 0, 2, 2, 0, 0, -0.5, 2, 0, 0, 0, 0, 1);
  float det = test.determinant();
  EXPECT_FLOAT_EQ(det, 5.0);
}

TEST(Mat4, inverse)
{
  // test verified from wolfram alpha
  // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
  ngl::Mat4 test(1, 0, 0, 0, 0, 2, 2, 0, 0, -0.5, 2, 0, 0, 0, 0, 1);
  test = test.inverse();
  ngl::Mat4 result(1, 0, 0, 0, 0, 0.4f, -0.4f, 0, 0, 0.1f, 0.4f, 0, 0, 0, 0, 1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, adjacent)
{
  ngl::Mat4 test(1, 0, 0, 0, 0, 2, 2, 0, 0, -0.5, 2, 0, 0, 0, 0, 1);
  test = test.adjacent();
  ngl::Mat4 result(5, 0, 0, 0, 0, 2, 0.5, 0, 0, -2, 2, 0, 0, 0, 0, 5);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, adjacentWithMat4)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Mat4 t2 = ngl::Mat4::rotateY(35.0f);
  ngl::Mat4 test = t1.adjacent(t2);
  ngl::Mat4 result(0.819152f, 0, -0.573577f, 0, 0, 1, 0, 0, 0.573577f, 0, 0.819152f, 0, 0, 0, 0, 1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, Vec4xMat4)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Vec4 test(2, 1, 2, 1);
  test = test * t1;
  ngl::Vec4 result(2, 2.12132f, 0.707107f, 1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4, Mat4xVec4)
{
  ngl::Mat4 t1 = ngl::Mat4::rotateX(45.0f);
  ngl::Vec4 test(2, 1, 2, 1);
  test = t1 * test;
  ngl::Vec4 result(2, -0.707107f, 2.12132f, 1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, fromGLM)
{
  glm::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
  ngl::Mat4 test(m);

  ngl::Mat4 result(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

  EXPECT_TRUE(test == result);
}

TEST(Mat4, toGLM)
{
  ngl::Mat4 test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
  auto result = test.toGLM();
  EXPECT_TRUE(test == result);
}


TEST(Mat4,asQuaternion)
{
  ngl::Mat4 test(1.0f); 
  auto q=test.asQuaternion();
  EXPECT_FLOAT_EQ(q.m_s,0.0f);
  EXPECT_FLOAT_EQ(q.m_x,0.0f);
  EXPECT_FLOAT_EQ(q.m_y,0.0f);
  EXPECT_FLOAT_EQ(q.m_z,1.0f);

  auto toQuat=ngl::Mat4::rotateX(90.0f);
  auto q2=toQuat.asQuaternion();
  EXPECT_FLOAT_EQ(q2.m_s,0.70710677f);
  EXPECT_FLOAT_EQ(q2.m_x,0.0f);
  EXPECT_FLOAT_EQ(q2.m_y,0.0f);
  EXPECT_FLOAT_EQ(q2.m_z,0.707107f);
  auto res=ngl::Quaternion(0.70710677f,0.0f,0.0f,0.70710677f);
  EXPECT_TRUE(q2==res);
}
