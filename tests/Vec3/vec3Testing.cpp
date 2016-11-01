#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec3.h>
#include <string>
#include <sstream>


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string print(const ngl::Vec3 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<3; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(NGLVec3,DefaultCtor)
{
  ngl::Vec3 test;
  ngl::Vec3 result(0.0f,0.0f,0.0f);
  EXPECT_TRUE(test == result);
}


TEST(NGLVec3,FloatCtor)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 result(1.0f,2.0f,3.0f);
  std::cout<<print(test);
  std::cout<<print(result);

  EXPECT_TRUE(test == result);
}


TEST(NGLVec3,CopyCtor)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 copy(test);
  ngl::Vec3 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}

TEST(NGLVec3,AssignOperator)
{
  ngl::Vec3 test(1.0f,2.0f,3.0f);
  ngl::Vec3 copy=test;
  ngl::Vec3 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}
