#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <string>
#include <sstream>
#include <glm/mat4x4.hpp>

std::string print(const ngl::Mat4 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<16; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(Mat4,DefaultCtor)
{
  ngl::Mat4 test;
  ngl::Mat4 result(1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,null)
{
  ngl::Mat4 test;
  test.null();
  ngl::Mat4 result(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,identity)
{
  ngl::Mat4 test;
  test.identity();
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,FloatCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}


TEST(Mat4,CopyCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy(test);
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(copy == result);
}

TEST(Mat4,AssignOperator)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy=test;
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(copy == result);
}

TEST(Mat4,setAtXY)
{
  ngl::Mat4 test;
  int value=0.0f;
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
        test.setAtXY(x,y,value++);
  ngl::Mat4 result(0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15);
  EXPECT_TRUE(test == result);
}


TEST(Mat4,translate)
{
  ngl::Mat4 test;
  test.translate(1.0f,2.0f,3.0f);
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,1,2,3,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,transpose)
{
  ngl::Mat4 test;
  test.translate(1.0f,2.0f,3.0f);
  test.transpose();
  ngl::Mat4 result(1,0,0,1,0,1,0,2,0,0,1,3,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,scale)
{
  ngl::Mat4 test;
  test.scale(1.0f,2.0f,3.0f);
  ngl::Mat4 result(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,rotateX)
{
  ngl::Mat4 test;
  test.rotateX(45.0f);
  ngl::Mat4 result(1,0,0,0,0,0.707107f,0.707107f,0,0,-0.707107f,0.707107f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,rotateY)
{
  ngl::Mat4 test;
  test.rotateY(25.0f);
  ngl::Mat4 result(0.906308f,0,-0.422618f,0,0,1,0,0,0.422618f,0,0.906308f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,rotateZ)
{
  ngl::Mat4 test;
  test.rotateZ(-36.0f);
  ngl::Mat4 result(0.809017f,-0.587785f,0,0,0.587785f,0.809017f,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,Mat4xMat4)
{
  ngl::Mat4 t1;
  ngl::Mat4 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  ngl::Mat4 test=t2*t1;
  ngl::Mat4 result(0.819152f,0,-0.573577f,0,0.40558f,0.707107f,0.579228f,0,0.40558f,-0.707107f,0.579228f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,Mat4xeuqals)
{
  ngl::Mat4 test;
  ngl::Mat4 t2;
  test.rotateX(45.0f);
  t2.rotateY(35.0f);
  test*=t2;
  ngl::Mat4 result(0.819152f,0.40558f,-0.40558f,0,0,0.707107f,0.707107f,0,0.573577f,-0.579228f,0.579228f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,Mat4xeuqals2)
{
  ngl::Mat4 test;
  ngl::Mat4 t2;
  test.rotateX(45.0f);
  t2.rotateY(35.0f);
  test*=t2;
  ngl::Mat4 r;
  r.rotateX(45.0f);
  EXPECT_TRUE(test == (r*t2));
}

TEST(Mat4,Mat4pluEqual)
{
  ngl::Mat4 t1;
  ngl::Mat4 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  t1+=t2;
  ngl::Mat4 result(1.81915f,0,-0.573577f,0,0,1.70711f,0.707107f,0,0.573577f,-0.707107f,1.52626f,0,0,0,0,2);

  EXPECT_TRUE(t1 == result);
}

TEST(Mat4,Mat4plus)
{
  ngl::Mat4 t1;
  ngl::Mat4 t2;
  ngl::Mat4 res;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  res=t1+t2;
  ngl::Mat4 result(1.81915f,0,-0.573577f,0,0,1.70711f,0.707107f,0,0.573577f,-0.707107f,1.52626f,0,0,0,0,2);

  EXPECT_TRUE(res == result);
}

TEST(Mat4,Mat4xReal)
{
  ngl::Mat4 test;
  int value=0.0f;
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
        test.setAtXY(x,y,value++);
  test=test*4.2f;
  ngl::Mat4 result(0,16.8f,33.6f,50.4f,4.2f,21,37.8f,54.6f,8.4f,25.2f,42,58.8f,12.6f,29.4f,46.2f,63);

  EXPECT_TRUE(test == result);
}

TEST(Mat4,Mat4xEqualReal)
{
  ngl::Mat4 test;
  int value=0.0f;
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
        test.setAtXY(x,y,float(value++));
  test*=4.2f;
  ngl::Mat4 result(0,16.8f,33.6f,50.4f,4.2f,21,37.8f,54.6f,8.4f,25.2f,42,58.8f,12.6f,29.4f,46.2f,63);

  EXPECT_TRUE(test == result);
}




TEST(Mat4,determinant)
{
  // note value 5.0 is verified by wolfram alpha
  ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
  float det=test.determinant();
  EXPECT_FLOAT_EQ(det,5.0);
}

TEST(Mat4,inverse)
{
  // test verified from wolfram alpha
  // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
  ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
  test=test.inverse();
  ngl::Mat4 result(1,0,0,0,0,0.4f,-0.4f,0,0,0.1f,0.4f,0,0,0,0,1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4,adjacent)
{
  ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
  test=test.adjacent();
  ngl::Mat4 result(5,0,0,0,0,2,0.5,0,0,-2,2,0,0,0,0,5);

  EXPECT_TRUE(test == result);
}

TEST(Mat4,adjacentWithMat4)
{
  ngl::Mat4 t1;
  ngl::Mat4 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  ngl::Mat4 test=t1.adjacent(t2);
  ngl::Mat4 result(0.819152f,0,-0.573577f,0,0,1,0,0,0.573577f,0,0.819152f,0,0,0,0,1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4,Vec4xMat4)
{
  ngl::Mat4 t1;
  ngl::Vec4 test(2,1,2,1);
  t1.rotateX(45.0f);
  test=test*t1;
//  ngl::Vec4 result(2,-0.707107f,2.12132f,1);
  ngl::Vec4 result(2,2.12132f,0.707107f,1);
  EXPECT_TRUE(test == result);
}

TEST(Mat4,Mat4xVec4)
{
  ngl::Mat4 t1;
  ngl::Vec4 test(2,1,2,1);
  t1.rotateX(45.0f);
  test=t1*test;
//  ngl::Vec4 result(2,2.12132f,0.707107f,1);
  ngl::Vec4 result(2,-0.707107f,2.12132f,1);

  EXPECT_TRUE(test == result);
}

TEST(Mat4,fromGLM)
{
  glm::mat4 m(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f);
  ngl::Mat4 test(m);

  ngl::Mat4 result(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f);

  EXPECT_TRUE(test == result);
}


TEST(Mat4,toGLM)
{
  ngl::Mat4 test(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f);
  auto result = test.toGLM();
  EXPECT_TRUE(test == result);

}





/* after thinking about it this is not a valid test!
class EulerTestRot : public ::testing::TestWithParam<ngl::Real> {
  // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
};


TEST_P(EulerTestRot,EulerRot)
{
  ngl::Mat4 euler;
  ngl::Mat4 rot;
  auto degrees=GetParam();
  euler.euler(degrees,1,0,0);
  rot.rotateX(degrees);
  EXPECT_TRUE(euler == rot)<<"Euler gives\n"<<print(euler)<<"rotateX gives\n"<<print(rot)<<'\n';

  euler.euler(degrees,0,1,0);
  rot.rotateY(degrees);
  EXPECT_TRUE(euler == rot)<<"Euler gives\n"<<print(euler)<<"rotateY gives\n"<<print(rot)<<'\n';


  euler.euler(degrees,0,0,1);
  rot.rotateZ(degrees);
  EXPECT_TRUE(euler == rot)<<"Euler gives\n"<<print(euler)<<"rotateZ gives\n"<<print(rot)<<'\n';


}

INSTANTIATE_TEST_CASE_P(Mat4EulerRot,
                        EulerTestRot,
                        ::testing::Values(0.0f,45.0f,90.0f,180.0f,270.0f,360.0f));
                        */


