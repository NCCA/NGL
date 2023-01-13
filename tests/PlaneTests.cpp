#include <gtest/gtest.h>
#include <ngl/Plane.h>

TEST(Plane, DefaultCtor)
{
  ngl::Plane test;
  auto p=test.getPoint();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 0.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
  p=test.getNormal();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 1.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
  
}

