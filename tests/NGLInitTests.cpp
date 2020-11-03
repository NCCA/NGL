#include <gtest/gtest.h>
#include <ngl/NGLInit.h>
#include <ngl/Types.h>


TEST(NGLInit,construct)
{
  int major,minor;
  glGetIntegerv(GL_MAJOR_VERSION,&major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  EXPECT_TRUE(major >=3);
  EXPECT_TRUE(minor >=1);
}
