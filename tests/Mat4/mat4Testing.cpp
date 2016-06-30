#include <gtest/gtest.h>
#include <ngl/Mat4.h>
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(NGLMat4,TestCtor)
{
  ngl::Mat4 test;
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,TestNull)
{
  ngl::Mat4 test;
  test.null();
  ngl::Mat4 result(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  EXPECT_TRUE(test == result);
}

TEST(NGLMat4,TestIdentity)
{
  ngl::Mat4 test;
  test.identity();
  ngl::Mat4 result(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
  EXPECT_TRUE(test == result);
}
