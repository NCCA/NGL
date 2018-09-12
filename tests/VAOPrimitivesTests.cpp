#include <gtest/gtest.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/AbstractVAO.h>
#include <ngl/SimpleVAO.h>
#include <array>
TEST(VAOPrimitives,instance)
{
  auto prim = ngl::VAOPrimitives::instance();
  EXPECT_TRUE(prim !=nullptr);
}

static std::array<const char *,12> meshes={{
 ngl::teapot,ngl::octahedron,ngl::dodecahedron,ngl::icosahedron,
  ngl::icosahedron,ngl::tetrahedron,ngl::football,ngl::cube,
  ngl::troll,ngl::bunny,ngl::dragon,ngl::buddah
}};

TEST(VAOPrimities,getCreatedIDs)
{
  auto prim = ngl::VAOPrimitives::instance();
  for(auto m : meshes)
    EXPECT_TRUE(prim->getVAOFromName(m) !=nullptr);

}

TEST(VAOPrimities,checkCreated)
{
  auto prim = ngl::VAOPrimitives::instance();
  for(auto m : meshes)
  {
    ngl::SimpleVAO *vao=  reinterpret_cast<ngl::SimpleVAO *>(prim->getVAOFromName(m));
    vao->bind();
    EXPECT_TRUE(vao->getBufferID(0) >0);
    vao->unbind();
  }
}
