#include <gtest/gtest.h>
#include <ngl/Mat3.h>
#include <ngl/Vec3.h>
#include <string>
#include <sstream>
#include <ngl/NGLStream.h>


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string print(const ngl::Mat3 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(auto m : _m.m_openGL)
    ret<<m<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(NGLMat3,DefaultCtor)
{
  ngl::Mat3 test;
  ngl::Mat3 result(1,0,0,0,1,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,null)
{
  ngl::Mat3 test;
  test.null();
  ngl::Mat3 result(0,0,0,0,0,0,0,0,0);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,identity)
{
  ngl::Mat3 test;
  test.identity();
  ngl::Mat3 result(1,0,0,0,1,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,FloatCtor)
{
  ngl::Mat3 test(2.0);
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(test == result);
}


TEST(NGLMat3,CopyCtor)
{
  ngl::Mat3 test(2.0);
  ngl::Mat3 copy(test);
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(copy == result);
}

TEST(NGLMat3,AssignOperator)
{
  ngl::Mat3 test(2.0f);
  ngl::Mat3 copy=test;
  ngl::Mat3 result(2,0,0,0,2,0,0,0,2);
  EXPECT_TRUE(copy == result);
}

TEST(NGLMat3,setAtXY)
{
  ngl::Mat3 test;
  int value=0.0f;
  for(int y=0; y<3; ++y)
    for(int x=0; x<3; ++x)
        test.setAtXY(x,y,value++);
  ngl::Mat3 result(0,3,6,1,4,7,2,5,8);
  EXPECT_TRUE(test == result);
}


//TEST(NGLMat3,translate)
//{
//  ngl::Mat3 test;
//  test.translate(1.0f,2.0f,3.0f);
//  ngl::Mat3 result(1,0,0,0,0,1,0,0,0,0,1,0,1,2,3,1);
//  EXPECT_TRUE(test == result);
//}

//TEST(NGLMat3,transpose)
//{
//  ngl::Mat3 test;
//  test.translate(1.0f,2.0f,3.0f);
//  test.transpose();
//  ngl::Mat3 result(1,0,0,1,0,1,0,2,0,0,1,3,0,0,0,1);
//  EXPECT_TRUE(test == result);
//}

TEST(NGLMat3,scale)
{
  ngl::Mat3 test;
  test.scale(1.0f,2.0f,3.0f);
  ngl::Mat3 result(1,0,0,0,2,0,0,0,3);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,rotateX)
{
  ngl::Mat3 test;
  test.rotateX(45.0f);
  ngl::Mat3 result(1,0,0,0,0.707107,0.707107,0,-0.707107,0.707107);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,rotateY)
{
  ngl::Mat3 test;
  test.rotateY(25.0f);
  ngl::Mat3 result(0.906308,0,-0.422618,0,1,0,0.422618,0,0.906308);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,rotateZ)
{
  ngl::Mat3 test;
  test.rotateZ(-36.0f);
  ngl::Mat3 result(0.809017,-0.587785,0,0.587785,0.809017,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,Mat3xMat3)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  ngl::Mat3 test=t1*t2;
  ngl::Mat3 result(0.819152f,0,-0.573577f,0.40558f,0.707107f,0.579228f,0.40558f,-0.707107f,0.579228f);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,Mat3xeuqals)
{
  ngl::Mat3 test;
  ngl::Mat3 t2;
  test.rotateX(45.0f);
  t2.rotateY(35.0f);
  test*=t2;
  ngl::Mat3 result(0.819152f,0.40558f,-0.40558f,0,0.707107f,0.707107f,0.573577f,-0.579228f,0.579228f);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,Mat3xeuqals2)
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

TEST(NGLMat3,Mat3pluEqual)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  t1+=t2;
  ngl::Mat3 result(1.81915f,0,-0.573577f,0,1.70711f,0.707107f,0.573577f,-0.707107f,1.52626f);

  EXPECT_TRUE(t1 == result);
}

TEST(NGLMat3,Mat3plus)
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

TEST(NGLMat3,Mat3xReal)
{
  ngl::Mat3 test;
  int value=0.0f;
  for(int y=0; y<3; ++y)
    for(int x=0; x<3; ++x)
        test.setAtXY(x,y,value++);
  test=test*4.2f;
  ngl::Mat3 result(0,12.599999427795,25.199998855591,4.199999809265,16.799999237061,29.399997711182,8.399999618530,21.000000000000,33.599998474121);

  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,Mat3xEqualReal)
{
  ngl::Mat3 test;
  int value=0.0f;
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
        test.setAtXY(x,y,value++);
  test*=4.2f;
  ngl::Mat3 result(0,16.8,33.6,50.4,21,37.8,54.6,25.2,42);

  EXPECT_TRUE(test == result);
}




TEST(NGLMat3,determinant)
{
  // note value 5.0 is verified by wolfram alpha
  ngl::Mat3 test(1,0,0,0,2,2,0,-0.5,2);
  float det=test.determinant();
  EXPECT_FLOAT_EQ(det,5.0);
}

TEST(NGLMat3,inverse)
{
  // test verified with matlab
  // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
  ngl::Mat3 test(1,0,0,0,2,2,0,-0.5,2);
  test=test.inverse();
  ngl::Mat3 result(1.0f ,0.0f,0.0f,0.0f,0.4f ,0.1f,0.0f,-0.4f,0.4f);


  std::cout<<test<<'\n'<<result;
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,adjacent)
{
  ngl::Mat3 test(1,0,0,0,2,2,0,-0.5,2);
  //test=test.Adjacent();
  ngl::Mat3 result(5,0,0,0,2,0.5,0,-2,2);

  EXPECT_TRUE(false);//test == result);
}

TEST(NGLMat3,adjacentWithMat3)
{
  ngl::Mat3 t1;
  ngl::Mat3 t2;
  t1.rotateX(45.0f);
  t2.rotateY(35.0f);
  //ngl::Mat3 test=t1.Adjacent(t2);
  //ngl::Mat3 result(0.819152f,0,-0.573577f,0,0,1,0,0,0.573577f,0,0.819152f,0,0,0,0,1);

  EXPECT_TRUE(false); //test == result);
}

TEST(NGLMat3,Vec4xMat3)
{
  ngl::Mat3 t1;
  ngl::Vec3 test(2,1,2);
  t1.rotateX(45.0f);
  test=test*t1;
  ngl::Vec3 result(2,-0.707107f,2.12132f);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat3,Mat3xVec4)
{
  ngl::Mat3 t1;
  ngl::Vec3 test(2,1,2);
  t1.rotateX(45.0f);
  test=t1*test;
  ngl::Vec3 result(2,2.12132f,0.707107f);
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
  ngl::Mat3 euler;
  ngl::Mat3 rot;
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

INSTANTIATE_TEST_CASE_P(Mat3EulerRot,
                        EulerTestRot,
                        ::testing::Values(0.0f,45.0f,90.0f,180.0f,270.0f,360.0f));
                        */


