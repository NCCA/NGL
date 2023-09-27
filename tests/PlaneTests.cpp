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

TEST(Plane,userCtor)
{
  ngl::Plane test(ngl::Vec3(1.0f,0.0f,1.0f),ngl::Vec3(1.0f,0.0f,2.0f),ngl::Vec3(2.0f,0.0f,4.0f));
  auto p=test.getPoint();
  EXPECT_FLOAT_EQ(p.m_x, 1.0f);
  EXPECT_FLOAT_EQ(p.m_y, 0.0f);
  EXPECT_FLOAT_EQ(p.m_z, 2.0f);
  p=test.getNormal();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 1.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
}

TEST(Plane,points)
{
  ngl::Plane test;
  test.setPoints(ngl::Vec3(1.0f,0.0f,1.0f),ngl::Vec3(1.0f,0.0f,2.0f),ngl::Vec3(2.0f,0.0f,4.0f));
  auto p=test.getPoint();
  EXPECT_FLOAT_EQ(p.m_x, 1.0f);
  EXPECT_FLOAT_EQ(p.m_y, 0.0f);
  EXPECT_FLOAT_EQ(p.m_z, 2.0f);
  p=test.getNormal();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 1.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
}

TEST(Plane,normalPoint)
{
  ngl::Plane test;
  test.setNormalPoint(ngl::Vec3(0.0f,1.0f,0.0f),ngl::Vec3(0.5f,0.0f,0.5f));
  auto p=test.getPoint();
  EXPECT_FLOAT_EQ(p.m_x, 0.5f);
  EXPECT_FLOAT_EQ(p.m_y, 0.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.5f);
  p=test.getNormal();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 1.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
}

TEST(Plane,floats)
{
  ngl::Plane test;
  test.setFloats(0.0f,1.0f,0.0f,0.5f);
  auto p=test.getPoint();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 0.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
  p=test.getNormal();
  EXPECT_FLOAT_EQ(p.m_x, 0.0f);
  EXPECT_FLOAT_EQ(p.m_y, 1.0f);
  EXPECT_FLOAT_EQ(p.m_z, 0.0f);
}

TEST(Plane,distance)
{
  ngl::Plane test;
  test.setPoints(ngl::Vec3(-1.0f,0.0f,0.0f),ngl::Vec3(1.0f,0.0f,0.0f),ngl::Vec3(0.0f,0.0f,1.0f)) ;
  auto p=test.distance(ngl::Vec3(0.0f,0.5f,0.0f));
  EXPECT_FLOAT_EQ(p, -0.5f);
}