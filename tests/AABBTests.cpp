#include <gtest/gtest.h>
#include <ngl/AABB.h>
#include <ngl/BBox.h>

TEST(AABB, DefaultCtor)
{
  ngl::AABB test;
  auto v=test.getVertexP({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, 0.0f);
  EXPECT_FLOAT_EQ(v.m_y, 1.0f);
  EXPECT_FLOAT_EQ(v.m_z, 0.0f);
  
  v=test.getVertexN({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, 0.0f);
  EXPECT_FLOAT_EQ(v.m_y, 0.0f);
  EXPECT_FLOAT_EQ(v.m_z, 0.0f);
}

TEST(AABB, userCtor)
{
  ngl::AABB test(ngl::Vec4(0.0f,0.0f,0.0f),1.0f,1.0f,1.0f);
  auto v=test.getVertexP({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, 0.0f);
  EXPECT_FLOAT_EQ(v.m_y, 1.0f);
  EXPECT_FLOAT_EQ(v.m_z, 0.0f);
  
  v=test.getVertexN({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, 0.0f);
  EXPECT_FLOAT_EQ(v.m_y, 0.0f);
  EXPECT_FLOAT_EQ(v.m_z, 0.0f);
}

TEST(AABB, set)
{
  ngl::AABB test;
  test.set(ngl::Vec4(0.0f,0.0f,0.0f),-1.0f,-1.0f,-1.0f);
  auto v=test.getVertexP({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, -1.0f);
  EXPECT_FLOAT_EQ(v.m_y, 0.0f);
  EXPECT_FLOAT_EQ(v.m_z, -1.0f);
  
  v=test.getVertexN({0,1,0});
  EXPECT_FLOAT_EQ(v.m_x, -1.0f);
  EXPECT_FLOAT_EQ(v.m_y, -1.0f);
  EXPECT_FLOAT_EQ(v.m_z, -1.0f);
}


