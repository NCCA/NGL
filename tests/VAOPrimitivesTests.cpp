#include <gtest/gtest.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/AbstractVAO.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <array>


static std::array<const char *,11> meshes={{
 ngl::teapot,ngl::octahedron,ngl::dodecahedron,
  ngl::icosahedron,ngl::tetrahedron,ngl::football,ngl::cube,
  ngl::troll,ngl::bunny,ngl::dragon,ngl::buddah
}};

TEST(VAOPrimitives,getCreatedIDs)
{

  for(auto m : meshes)
    EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName(m) !=nullptr);

}

TEST(VAOPrimitives,checkCreated)
{

  for(auto m : meshes)
  {
    ngl::SimpleVAO *vao=  reinterpret_cast<ngl::SimpleVAO *>(ngl::VAOPrimitives::getVAOFromName(m));
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
 
   ngl::VAOPrimitives::addToPrimitives("test",std::move(vao));
   EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("test") !=nullptr);

   ngl::SimpleVAO *v=  reinterpret_cast<ngl::SimpleVAO *>(ngl::VAOPrimitives::getVAOFromName("test"));
   v->bind();
   EXPECT_TRUE(v->getBufferID(0) >0);
   v->unbind();

}

TEST(VAOPrimitives,createSphere)
{

  ngl::VAOPrimitives::createSphere("sphere",1.0,200);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("sphere") !=nullptr);
}

TEST(VAOPrimitives,createLineGrid)
{

  ngl::VAOPrimitives::createLineGrid("grid",100,100,1000);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("grid") !=nullptr);
}

TEST(VAOPrimitives,createTrianglePlane)
{

  ngl::VAOPrimitives::createTrianglePlane("plane",100,100,1000,1000,ngl::Vec3::up());
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("plane") !=nullptr);
}

TEST(VAOPrimitives,createCylinder)
{

  ngl::VAOPrimitives::createCylinder("cylinder",1.0f,2.0f,100,100);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("cylinder") !=nullptr);
}

TEST(VAOPrimitives,createTorus)
{

  ngl::VAOPrimitives::createCylinder("torus",1.0f,2.0f,100,100);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("torus") !=nullptr);
}

TEST(VAOPrimitives,createCone)
{

  ngl::VAOPrimitives::createCone("cone",1.0f,2.0f,100,100);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("cone") !=nullptr);
}

TEST(VAOPrimitives,createCapsule)
{

  ngl::VAOPrimitives::createCapsule("capsule",1.0f,2.0f,100);
  EXPECT_TRUE(ngl::VAOPrimitives::getVAOFromName("capsule") !=nullptr);
}


TEST(VAOPrimitives,clear)
{

  ngl::VAOPrimitives::clear();
  for(auto m : meshes)
    EXPECT_FALSE(ngl::VAOPrimitives::getVAOFromName(m) !=nullptr);

}
