#include <gtest/gtest.h>
#include <ngl/Mat3.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <string>
#include <sstream>
#include <ngl/NGLStream.h>
#include <ngl/Util.h>
#include <ngl/Mat4.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_inverse.hpp>

std::string print(const ngl::Mat3 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(auto m : _m.m_openGL)
    ret<<m<<',';
  ret<<"\b)\n";
  return ret.str();
}


TEST(Mat3,DefaultCtor)
{
  ngl::Mat3 test;
  ngl::Mat3 result(1,0,0,0,1,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,null)
{
  ngl::Mat3 test;
  test.null();
  ngl::Mat3 result(0,0,0,0,0,0,0,0,0);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,identity)
{
  ngl::Mat3 test;
  test.identity();
  ngl::Mat3 result(1,0,0,0,1,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,FloatCtor)
{
  ngl::Mat3 test(2.0);
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(test == result);
}


TEST(Mat3,CopyCtor)
{
  ngl::Mat3 test(2.0);
  ngl::Mat3 copy(test);
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(copy == result);
}

TEST(Mat3,AssignOperator)
{
  ngl::Mat3 test(2.0f);
  ngl::Mat3 copy=test;
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(copy == result);
}

TEST(Mat3,setAtXY)
{
  ngl::Mat3 test;
  float value=0.0f;
  for(int y=0; y<3; ++y)
    for(int x=0; x<3; ++x)
        test.setAtXY(x,y,value++);
  ngl::Mat3 result(0,3,6,1,4,7,2,5,8);
  EXPECT_TRUE(test == result);
}




TEST(Mat3,transpose)
{
  ngl::Mat3 test(1,2,3,4,5,6,7,8,9);
  test.transpose();
  ngl::Mat3 result(1,4,7,2,5,8,3,6,9);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,scale)
{
  ngl::Mat3 test;
  test.scale(1.0f,2.0f,3.0f);
  ngl::Mat3 result(1,0,0,0,2,0,0,0,3);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,rotateX)
{
  ngl::Mat3 test;
  test.rotateX(45.0f);
  ngl::Mat3 result(1.0f,0.0f,0.0f,0.0f,0.707107f,0.707107f,0.0f,-0.707107f,0.707107f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,rotateY)
{
  ngl::Mat3 test;
  test.rotateY(25.0f);
  ngl::Mat3 result(0.906308f,0.0f,-0.422618f,0.0f,1.0f,0.0f,0.422618f,0.0f,0.906308f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,rotateZ)
{
  ngl::Mat3 test;
  test.rotateZ(-36.0f);
  ngl::Mat3 result(0.809017f,-0.587785f,0.0f,0.587785f,0.809017f,0.0f,0.0f,0.0f,1.0f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,Mat3xMat3)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  ngl::Mat3 test=t1*t2;
  ngl::Mat3 result(0.819152f,0.0f,-0.573577f,0.40558f,0.707107f,0.579228f,0.40558f,-0.707107f,0.579228f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,Mat3xeuqals)
{
  ngl::Mat3 test;
  ngl::Mat3 t2;
  test.rotateX(45.0f);
  t2.rotateY(35.0f);
  test*=t2;
  ngl::Mat3 result(0.819152f,0.40558f,-0.40558f,0,0.707107f,0.707107f,0.573577f,-0.579228f,0.579228f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,Mat3xeuqals2)
{
  ngl::Mat3 test;
  ngl::Mat3 t2;
  test.rotateX(45.0f);
  t2.rotateY(35.0f);
  test*=t2;
  ngl::Mat3 r;
  r.rotateX(45.0f);
  EXPECT_TRUE(test == (t2*r));
}

TEST(Mat3,Mat3plusEqual)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  t1+=t2;
  ngl::Mat3 result(1.81915f,0,-0.573577f,0,1.70711f,0.707107f,0.573577f,-0.707107f,1.52626f);

  EXPECT_TRUE(t1 == result);
}

TEST(Mat3,Mat3plus)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  ngl::Mat3 res;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  res=t1+t2;
  ngl::Mat3 result(1.81915f,0,-0.573577f,0,1.70711f,0.707107f,0.573577f,-0.707107f,1.52626f);

  EXPECT_TRUE(res == result);
}

TEST(Mat3,Mat3xReal)
{
  ngl::Mat3 test;
  float value=0.0f;
  for(int y=0; y<3; ++y)
    for(int x=0; x<3; ++x)
        test.setAtXY(x,y,value++);
  test=test*4.2f;
  ngl::Mat3 result(0.0f,12.599999427795f,25.199998855591f,4.199999809265f,16.799999237061f,
                   29.399997711182f,8.399999618530f,21.000000000000f,33.599998474121f);

  EXPECT_TRUE(test == result);
}

TEST(Mat3,Mat3xEqualReal)
{
  ngl::Mat3 test;
  float value=0.0f;
  for(int y=0; y<3; ++y)
    for(int x=0; x<3; ++x)
        test.setAtXY(x,y,value++);
  test*=4.2f;
  ngl::Mat3 result(0.0f,12.599999427795f,25.199998855591f,4.199999809265f,
                   16.799999237061f,29.399997711182f,8.399999618530f,21.000000000000f,33.599998474121f);

  EXPECT_TRUE(test == result);
}




TEST(Mat3,determinant)
{
  // note value 5.0 is verified by wolfram alpha
  ngl::Mat3 test(1,0,0,0,2,2,0,-0.5,2);
  float det=test.determinant();
  EXPECT_FLOAT_EQ(det,5.0);
}

TEST(Mat3,inverse)
{
  // test verified with matlab
  // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
  ngl::Mat3 test(1,0,0,0,2,2,0,-0.5,2);
  test=test.inverse();
  ngl::Mat3 result(1.0f ,0.0f,0.0f,0.0f,0.4f ,0.1f,0.0f,-0.4f,0.4f);


  //std::cout<<test<<'\n'<<result;
  EXPECT_TRUE(test == result);
}


TEST(Mat3,Vec4xMat3)
{
  ngl::Mat3 t1;
  ngl::Vec3 test(2,1,2);
  t1.rotateX(45.0f);
  test=test*t1;
  ngl::Vec3 result(2,-0.707107f,2.12132f);
  EXPECT_TRUE(test == result);
}

TEST(Mat3,normalMatrix)
{
  ngl::Mat4 view=ngl::lookAt({2.0f,2.0f,2.0f},{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f});
  ngl::Mat4 model;
  model.scale(0.2f,1.0f,0.2f);
  ngl::Mat3 normalMatrix(view*model);
  normalMatrix.inverse().transpose();

  glm::mat4 glmview=glm::lookAt(glm::vec3(2.0f,2.0f,2.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
  glm::mat4 glmmodel=glm::scale(glm::mat4(1.0f),glm::vec3(0.2f,1.0f,0.2f));
  glm::mat3 glmNormalMatrix;
  glmNormalMatrix = glm::transpose(glm::inverse(glm::mat3(glmview*glmmodel)));

  EXPECT_TRUE(ngl::Mat4(glmview)==view);
  EXPECT_TRUE(ngl::Mat4(glmmodel)==model);
  EXPECT_TRUE(ngl::Mat3(glmNormalMatrix)==normalMatrix);
  EXPECT_TRUE(ngl::Mat3(glm::inverseTranspose(glm::mat3(glmview*glmmodel))) == normalMatrix);

}

