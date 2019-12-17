#include <gtest/gtest.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/AbstractVAO.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <array>
TEST(VAOPrimitives,instance)
{
  auto prim = ngl::VAOPrimitives::instance();
  EXPECT_TRUE(prim !=nullptr);
}

static std::array<const char *,11> meshes={{
 ngl::teapot,ngl::octahedron,ngl::dodecahedron,
  ngl::icosahedron,ngl::tetrahedron,ngl::football,ngl::cube,
  ngl::troll,ngl::bunny,ngl::dragon,ngl::buddah
}};

TEST(VAOPrimitives,getCreatedIDs)
{
  auto prim = ngl::VAOPrimitives::instance();
  for(auto m : meshes)
    EXPECT_TRUE(prim->getVAOFromName(m) !=nullptr);

}

TEST(VAOPrimitives,checkCreated)
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

TEST(VAOPrimitives,checkADD)
{
  std::array<ngl::Vec3,12> verts=
   {{
     ngl::Vec3(0,1,1),
     ngl::Vec3(0,0,-1),
     ngl::Vec3(-0.5,0,1),
     ngl::Vec3(0,1,1),
     ngl::Vec3(0,0,-1),
     ngl::Vec3(0.5,0,1),
     ngl::Vec3(0,1,1),
     ngl::Vec3(0,0,1.5),
     ngl::Vec3(-0.5,0,1),
     ngl::Vec3(0,1,1),
     ngl::Vec3(0,0,1.5),
     ngl::Vec3(0.5,0,1)
   }};
//   std::cout<<"sizeof(verts) "<<sizeof(verts)<<" sizeof(ngl::Vec3) "<<sizeof(ngl::Vec3)<<"\n";
//   std::cout<<"sizeof(verts) "<<sizeof(verts)<<" sizeof(ngl::Vec3) "<<sizeof(ngl::Vec3)<<"\n";
   // create a vao as a series of GL_TRIANGLES
   auto vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_TRIANGLES);
   vao->bind();
   // in this case we are going to set our data as the vertices above
   vao->setData(ngl::SimpleVAO::VertexData(verts.size()*sizeof(ngl::Vec3),verts[0].m_x));
   // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)
   vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
   // divide by 2 as we have both verts and normals
   vao->setNumIndices(verts.size());
  // now unbind
   vao->unbind();
   auto prim = ngl::VAOPrimitives::instance();
   prim->addToPrimitives("test",std::move(vao));
   EXPECT_TRUE(prim->getVAOFromName("test") !=nullptr);

   ngl::SimpleVAO *v=  reinterpret_cast<ngl::SimpleVAO *>(prim->getVAOFromName("test"));
   v->bind();
   EXPECT_TRUE(v->getBufferID(0) >0);
   v->unbind();

}

TEST(VAOPrimitives,createSphere)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",1.0,200);
  EXPECT_TRUE(prim->getVAOFromName("sphere") !=nullptr);
}

TEST(VAOPrimitives,createLineGrid)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createLineGrid("grid",100,100,1000);
  EXPECT_TRUE(prim->getVAOFromName("grid") !=nullptr);
}

TEST(VAOPrimitives,createTrianglePlane)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createTrianglePlane("plane",100,100,1000,1000,ngl::Vec3::up());
  EXPECT_TRUE(prim->getVAOFromName("plane") !=nullptr);
}

TEST(VAOPrimitives,createCylinder)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createCylinder("cylinder",1.0f,2.0f,100,100);
  EXPECT_TRUE(prim->getVAOFromName("cylinder") !=nullptr);
}

TEST(VAOPrimitives,createTorus)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createCylinder("torus",1.0f,2.0f,100,100);
  EXPECT_TRUE(prim->getVAOFromName("torus") !=nullptr);
}

TEST(VAOPrimitives,createCone)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createCone("cone",1.0f,2.0f,100,100);
  EXPECT_TRUE(prim->getVAOFromName("cone") !=nullptr);
}

TEST(VAOPrimitives,createCapsule)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->createCapsule("capsule",1.0f,2.0f,100);
  EXPECT_TRUE(prim->getVAOFromName("capsule") !=nullptr);
}


TEST(VAOPrimitives,clear)
{
  auto prim = ngl::VAOPrimitives::instance();
  prim->clear();
  for(auto m : meshes)
    EXPECT_FALSE(prim->getVAOFromName(m) !=nullptr);

}
