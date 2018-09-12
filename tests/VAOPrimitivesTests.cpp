#include <gtest/gtest.h>
#include <ngl/VAOPrimitives.h>

TEST(VAOPrimitives,instance)
{
  auto prim = ngl::VAOPrimitives::instance();
  EXPECT_TRUE(prim !=nullptr);
}
