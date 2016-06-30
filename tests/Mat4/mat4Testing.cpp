#include <gtest/gtest.h>
#include <ngl/Mat4.h>
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(NGLMat4,DefaultCtor)
{
  ngl::Mat4 test;
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,null)
{
  ngl::Mat4 test;
  test.null();
  ngl::Mat4 result(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,identity)
{
  ngl::Mat4 test;
  test.identity();
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,FloatCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}


TEST(NGLMat4,CopyCtor)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy(test);
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(copy == result);
}

TEST(NGLMat4,AssignOperator)
{
  ngl::Mat4 test(2.0);
  ngl::Mat4 copy=test;
  ngl::Mat4 result(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1);
  EXPECT_TRUE(copy == result);
}

TEST(NGLMat4,setAtXY)
{
  ngl::Mat4 test;
  int value=0.0f;
  for(int y=0; y<4; ++y)
    for(int x=0; x<4; ++x)
        test.setAtXY(x,y,value++);
  ngl::Mat4 result(0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,translate)
{
  ngl::Mat4 test;
  test.translate(1.0f,2.0f,3.0f);
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,1,2,3,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,transpose)
{
  ngl::Mat4 test;
  test.translate(1.0f,2.0f,3.0f);
  test.transpose();
  ngl::Mat4 result(1,0,0,1,0,1,0,2,0,0,1,3,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,scale)
{
  ngl::Mat4 test;
  test.scale(1.0f,2.0f,3.0f);
  ngl::Mat4 result(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,rotateX)
{
  ngl::Mat4 test;
  test.rotateX(45.0f);
  ngl::Mat4 result(1,0,0,0,0,0.707107f,0.707107f,0,0,-0.707107f,0.707107f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,rotateY)
{
  ngl::Mat4 test;
  test.rotateY(25.0f);
  ngl::Mat4 result(0.906308f,0,-0.422618f,0,0,1,0,0,0.422618f,0,0.906308f,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,rotateZ)
{
  ngl::Mat4 test;
  test.rotateZ(-36.0f);
  ngl::Mat4 result(0.809017f,-0.587785f,0,0,0.587785f,0.809017f,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,determinant)
{
  // note value 5.0 is verified by wolfram alpha
  ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
  float det=test.determinant();
  EXPECT_FLOAT_EQ(det,5.0);
}

TEST(NGLMat4,inverse)
{
  // test verified from wolfram alpha
  // 1,0,0,0,0,0.4, -0.4, 0 ,0 , 0.1 , 0.4 0 ,0,0,0,1
  ngl::Mat4 test(1,0,0,0,0,2,2,0,0,-0.5,2,0,0,0,0,1);
  test=test.inverse();
  ngl::Mat4 result(1,0,0,0,0,0.4f,-0.4f,0,0,0.1f,0.4f,0,0,0,0,1);

  EXPECT_TRUE(test == result);
}



