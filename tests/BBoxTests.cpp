#include <gtest/gtest.h>
#include <ngl/BBox.h>


TEST(BBox, DefaultCtor)
{
  ngl::BBox test;
  EXPECT_FLOAT_EQ(test.width(),2.0f);
  EXPECT_FLOAT_EQ(test.height(),2.0f);
  EXPECT_FLOAT_EQ(test.depth(),2.0f);
  EXPECT_FLOAT_EQ(test.minX(),-1.0f);
  EXPECT_FLOAT_EQ(test.minY(),-1.0f);
  EXPECT_FLOAT_EQ(test.minZ(),-1.0f);
  EXPECT_FLOAT_EQ(test.maxX(),1.0f);
  EXPECT_FLOAT_EQ(test.maxY(),1.0f);
  EXPECT_FLOAT_EQ(test.maxZ(),1.0f);
  EXPECT_TRUE(test.center()==ngl::Vec3(0.0f,0.0f,0.0f));
}

TEST(BBox, CopyCtor)
{
  ngl::BBox d(true);
  auto test(d);
  EXPECT_FLOAT_EQ(test.width(),2.0f);
  EXPECT_FLOAT_EQ(test.height(),2.0f);
  EXPECT_FLOAT_EQ(test.depth(),2.0f);
  EXPECT_FLOAT_EQ(test.minX(),-1.0f);
  EXPECT_FLOAT_EQ(test.minY(),-1.0f);
  EXPECT_FLOAT_EQ(test.minZ(),-1.0f);
  EXPECT_FLOAT_EQ(test.maxX(),1.0f);
  EXPECT_FLOAT_EQ(test.maxY(),1.0f);
  EXPECT_FLOAT_EQ(test.maxZ(),1.0f);
  EXPECT_TRUE(test.center()==ngl::Vec3(0.0f,0.0f,0.0f));
}

TEST(BBox, AssignOperator)
{
  ngl::BBox d(true);
  auto test=d;
  EXPECT_FLOAT_EQ(test.width(),2.0f);
  EXPECT_FLOAT_EQ(test.height(),2.0f);
  EXPECT_FLOAT_EQ(test.depth(),2.0f);
  EXPECT_FLOAT_EQ(test.minX(),-1.0f);
  EXPECT_FLOAT_EQ(test.minY(),-1.0f);
  EXPECT_FLOAT_EQ(test.minZ(),-1.0f);
  EXPECT_FLOAT_EQ(test.maxX(),1.0f);
  EXPECT_FLOAT_EQ(test.maxY(),1.0f);
  EXPECT_FLOAT_EQ(test.maxZ(),1.0f);
  EXPECT_TRUE(test.center()==ngl::Vec3(0.0f,0.0f,0.0f));
}

TEST(BBox, ConstructFromExtents)
{
  ngl::BBox test(-5,5,-2,2,-3.2,2.4,true);
  EXPECT_FLOAT_EQ(test.minX(),-5.0f);
  EXPECT_FLOAT_EQ(test.maxX(),5.0f);
  EXPECT_FLOAT_EQ(test.minY(),-2.0f);
  EXPECT_FLOAT_EQ(test.maxY(),2.0f);
  EXPECT_FLOAT_EQ(test.minZ(),-3.2f);
  EXPECT_FLOAT_EQ(test.maxZ(),2.4f);
  EXPECT_TRUE(test.center()==ngl::Vec3(0.0f,0.0f,0.0f));

  EXPECT_FLOAT_EQ(test.width(),10.0f);
  EXPECT_FLOAT_EQ(test.height(),4.0f);
  EXPECT_FLOAT_EQ(test.depth(),5.6f);

}

TEST(BBox, setExtents)
{
  ngl::BBox test(true);
  test.setExtents(-5,5,-2,2,-3.2,2.4);
  EXPECT_FLOAT_EQ(test.minX(),-5.0f);
  EXPECT_FLOAT_EQ(test.maxX(),5.0f);
  EXPECT_FLOAT_EQ(test.minY(),-2.0f);
  EXPECT_FLOAT_EQ(test.maxY(),2.0f);
  EXPECT_FLOAT_EQ(test.minZ(),-3.2f);
  EXPECT_FLOAT_EQ(test.maxZ(),2.4f);
  EXPECT_TRUE(test.center()==ngl::Vec3(0.0f,0.0f,0.0f));

  EXPECT_FLOAT_EQ(test.width(),10.0f);
  EXPECT_FLOAT_EQ(test.height(),4.0f);
  EXPECT_FLOAT_EQ(test.depth(),5.6f);
}

TEST(BBox, setters)
{
  ngl::BBox test(true);
  test.width(5,true);
  test.height(25,true);
  test.depth(15,true);
  EXPECT_FLOAT_EQ(test.width(),5.0f);
  EXPECT_FLOAT_EQ(test.height(),25.0f);
  EXPECT_FLOAT_EQ(test.depth(),15.0f);

  EXPECT_FLOAT_EQ(test.minX(),-2.5f);
  EXPECT_FLOAT_EQ(test.maxX(),2.5f);
  EXPECT_FLOAT_EQ(test.minY(),-12.5f);
  EXPECT_FLOAT_EQ(test.maxY(),12.5f);
  EXPECT_FLOAT_EQ(test.minZ(),-7.5f);
  EXPECT_FLOAT_EQ(test.maxZ(),7.5f);
}

TEST(BBox,getVerts)
{
    ngl::BBox test;
    //auto verts=test.getVertexArray();
}