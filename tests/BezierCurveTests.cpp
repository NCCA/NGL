#include <gtest/gtest.h>
#include <ngl/BezierCurve.h>
#include <ngl/NGLStream.h>

TEST(BezierCurve, DefaultCtor)
{
  ngl::BezierCurve test;
  EXPECT_EQ(test.getKnots().size(),0);
  EXPECT_EQ(test.getControlPoints().size(),0);
}



TEST(BezierCurve, createFromCP)
{
  ngl::BezierCurve test;
  test.addPoint(ngl::Vec3(-5.0f, 0.0f, -5.0f));
  test.addPoint(ngl::Vec3(-2.0f, 2.0f, 1.0f));
  test.addPoint(ngl::Vec3(3.0f, -3.0f, -3.0f));
  test.addPoint(ngl::Vec3(2.0f, -6.0f, 2.0f));
  test.setLOD(200.0f);
  test.createKnots();
  EXPECT_EQ(test.getKnots().size(),9);
  EXPECT_EQ(test.getControlPoints().size(),4);
  auto cp=test.getControlPoints();
  EXPECT_TRUE(cp[0]==ngl::Vec3(-5.0f, 0.0f, -5.0f));
  EXPECT_TRUE(cp[1]==ngl::Vec3(-2.0f, 2.0f, 1.0f));
  EXPECT_TRUE(cp[2]==ngl::Vec3(3.0f, -3.0f, -3.0f));
  EXPECT_TRUE(cp[3]==ngl::Vec3(2.0f, -6.0f, 2.0f));
}

TEST(BezierCurve, createFromCPXYZ)
{
  ngl::BezierCurve test;
  test.addPoint(-5.0f, 0.0f, -5.0f);
  test.addPoint(-2.0f, 2.0f, 1.0f);
  test.addPoint(3.0f, -3.0f, -3.0f);
  test.addPoint(2.0f, -6.0f, 2.0f);
  test.setLOD(200.0f);
  test.createKnots();
  EXPECT_EQ(test.getKnots().size(),9);
  EXPECT_EQ(test.getControlPoints().size(),4);
  auto cp=test.getControlPoints();
  EXPECT_TRUE(cp[0]==ngl::Vec3(-5.0f, 0.0f, -5.0f));
  EXPECT_TRUE(cp[1]==ngl::Vec3(-2.0f, 2.0f, 1.0f));
  EXPECT_TRUE(cp[2]==ngl::Vec3(3.0f, -3.0f, -3.0f));
  EXPECT_TRUE(cp[3]==ngl::Vec3(2.0f, -6.0f, 2.0f));
}

TEST(BezierCurve,getPointOnCurve)
{
  ngl::BezierCurve test;
  test.addPoint(ngl::Vec3(-5.0f, 0.0f, 0.0f));
  test.addPoint(ngl::Vec3(0.0f, 2.0f, 0.0f));
  test.addPoint(ngl::Vec3(5.0f, 0.0f, 0.0f));
  test.createKnots();
  EXPECT_EQ(test.getKnots().size(),7);
  EXPECT_EQ(test.getControlPoints().size(),3);
  // we know our curve should go through start and end points so test.
  EXPECT_TRUE(test.getPointOnCurve(0)==ngl::Vec3(-5.0f, 0.0f, 0.0f));

  EXPECT_TRUE(test.getPointOnCurve(1)==ngl::Vec3(5.0f, 0.0f, 0.0f));
}

TEST(BezierCurve,fromVec3AndKnots)
{
std::vector<ngl::Vec3> cp={
  ngl::Vec3(-5.0f, 0.0f, 0.0f),
  ngl::Vec3(0.0f, 2.0f, 0.0f),
  ngl::Vec3(5.0f, 0.0f, 0.0f)};

  std::vector<ngl::Real> knots={0,0,0,1,1,1,1};
  ngl::BezierCurve test(cp,knots);
  EXPECT_EQ(test.getKnots().size(),7);
  EXPECT_EQ(test.getControlPoints().size(),3);
  EXPECT_TRUE(test.getPointOnCurve(0)==ngl::Vec3(-5.0f, 0.0f, 0.0f));
  EXPECT_TRUE(test.getPointOnCurve(1)==ngl::Vec3(5.0f, 0.0f, 0.0f));  
 
  
}

TEST(BezierCurve,fromVec3)
{
std::vector<ngl::Vec3> cp={
  ngl::Vec3(-5.0f, 0.0f, 0.0f),
  ngl::Vec3(0.0f, 2.0f, 0.0f),
  ngl::Vec3(5.0f, 0.0f, 0.0f)};

  ngl::BezierCurve test(cp);
  EXPECT_EQ(test.getKnots().size(),7);
  EXPECT_EQ(test.getControlPoints().size(),3);
  EXPECT_TRUE(test.getPointOnCurve(0)==ngl::Vec3(-5.0f, 0.0f, 0.0f));
  EXPECT_TRUE(test.getPointOnCurve(1)==ngl::Vec3(5.0f, 0.0f, 0.0f));  
  auto calculatedKnots=test.getKnots();
  std::vector<ngl::Real> knots={0,0,0,1,1,1,1};
  EXPECT_TRUE(calculatedKnots==knots);


  
}


