#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <string>
#include <sstream>


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string print(const ngl::Vec4 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<4; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(NGLVec4,DefaultCtor)
{
  ngl::Vec4 test;
  ngl::Vec4 result(0.0f,0.0f,0.0f,1.0);
  EXPECT_TRUE(test == result);
}

TEST(NGLVec4,SubScript)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f,4.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1],2.0f);
  EXPECT_FLOAT_EQ(test[2], 3.0f);
  EXPECT_FLOAT_EQ(test[3], 4.0f);

}



TEST(NGLVec4,FloatCtor)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f);
  ngl::Vec4 result(1.0f,2.0f,3.0f);

  EXPECT_TRUE(test == result);
}


TEST(NGLVec4,CopyCtor)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f);
  ngl::Vec4 copy(test);
  ngl::Vec4 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}

TEST(NGLVec4,AssignOperator)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f);
  ngl::Vec4 copy=test;
  ngl::Vec4 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}
