#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <ngl/Obj.h>
#include <memory>


const std::array<const char *,7> validfiles={
  {
   "files/Triangle1.obj",
   "files/TriangleVertNormal.obj",
   "files/TriangleVertsOnly.obj",
   "files/TriangleVertsUV.obj",
   "files/Triangle3UV.obj",
   "files/TriMessedFormat.obj",
   "files/CubeNegativeIndex.obj"
  }
};

const std::array<const char *,1> invalidfiles={
  {
    "files/BrokenFloats.obj"
  }
};

TEST(Obj,openForReading)
{
  for(auto s : validfiles)
  {
    std::ifstream f(s);
    EXPECT_TRUE(f.good());
  }
  for(auto s : invalidfiles)
  {
    std::ifstream f(s);
    EXPECT_TRUE(f.good());
  }
}

//TEST(Obj,loadBig)
//{
//  Obj a;
//  EXPECT_TRUE(a.load("files/sponza.obj"));
//}

TEST(Obj,defaultCtor)
{
  ngl::Obj a;
  EXPECT_EQ(a.getNumFaces() , 0);
  EXPECT_EQ(a.getNumNormals() , 0);
  EXPECT_EQ(a.getNumVerts() , 0);
  EXPECT_EQ(a.getNumTexCords(),0);
}

TEST(Obj,loadvalid)
{
  ngl::Obj a;
  for(auto f : validfiles)
  {
    EXPECT_TRUE(a.load(f,ngl::Obj::CalcBB::False));
    EXPECT_TRUE(a.isLoaded());
  }
}
TEST(Obj,loadinvalid)
{
  ngl::Obj a;
  for(auto f : invalidfiles)
  {
    EXPECT_FALSE(a.load(f,ngl::Obj::CalcBB::False));
    EXPECT_FALSE(a.isLoaded());
  }

}

TEST(Obj,loadFail)
{
  ngl::Obj a;
  EXPECT_FALSE(a.load("nothere.obj",ngl::Obj::CalcBB::False));
  EXPECT_FALSE(a.isLoaded());
}

TEST(Obj,parseVertex)
{
  ngl::Obj a;
  EXPECT_TRUE(a.load("files/Triangle1.obj",ngl::Obj::CalcBB::False));
  EXPECT_EQ(a.getNumVerts(),3);
}

TEST(Obj,parseNormal)
{
  ngl::Obj a;
  EXPECT_TRUE(a.load("files/Triangle1.obj",ngl::Obj::CalcBB::False));
  EXPECT_EQ(a.getNumNormals(),3);
}

TEST(Obj,parseUV)
{
  ngl::Obj a;
  EXPECT_TRUE(a.load("files/Triangle1.obj",ngl::Obj::CalcBB::False));
  EXPECT_EQ(a.getNumTexCords(),3);
}

TEST(Obj,parseUV3)
{
  ngl::Obj a;
  EXPECT_TRUE(a.load("files/Triangle3UV.obj",ngl::Obj::CalcBB::False));
  EXPECT_EQ(a.getNumTexCords(),3);
}

TEST(Obj,checkVerts)
{
  ngl::Obj a("files/Triangle1.obj");
  std::vector<ngl::Vec3> verts=a.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f, 0.00000f, 0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f, 4.0000f, 0.000000f));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f, 0.000000f, 0.000000f));

}

TEST(Obj,checkNorm)
{
  ngl::Obj a("files/Triangle1.obj");
  std::vector<ngl::Vec3> norm=a.getNormalList();
  ASSERT_TRUE(norm[0]==ngl::Vec3(0.000000f, 0.000000f, 1.000000f));
  ASSERT_TRUE(norm[1]==ngl::Vec3(0.000000f, 0.000000f, 1.000000f));
  ASSERT_TRUE(norm[2]==ngl::Vec3(0.000000f, 0.000000f, 1.000000f));

}

TEST(Obj,checkUV)
{
  ngl::Obj a("files/Triangle1.obj");
  std::vector<ngl::Vec3> uv=a.getUVList();
  ASSERT_TRUE(uv[0]==ngl::Vec3(1.000000f, 0.000000f, 0.000000f));
  ASSERT_TRUE(uv[1]==ngl::Vec3(0.500000f, 1.000000f, 0.000000f));
  ASSERT_TRUE(uv[2]==ngl::Vec3(0.004399f, 0.008916f, 0.000000f));
}




TEST(Obj,checkFaceVertOnly)
{
  ngl::Obj a("files/TriangleVertsOnly.obj");
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
}

TEST(Obj,checkFaceVertNormal)
{
  ngl::Obj a("files/TriangleVertNormal.obj");
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f 1//1 2//2 3//3  but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  ASSERT_EQ(face[0].m_norm[0],0);
  ASSERT_EQ(face[0].m_norm[1],1);
  ASSERT_EQ(face[0].m_norm[2],2);

}


TEST(Obj,checkFaceVertUV)
{
  ngl::Obj a("files/TriangleVertsUV.obj");
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f 1/1 2/2 3/3  but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  ASSERT_EQ(face[0].m_uv[0],0);
  ASSERT_EQ(face[0].m_uv[1],1);
  ASSERT_EQ(face[0].m_uv[2],2);

}

TEST(Obj,checkFaceVertOnlyNegativeIndex)
{
  ngl::Obj a("files/CubeNegativeIndex.obj");
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f -4 -3 -2 -1
  int idx=0;
  for(size_t i=0; i<face.size(); ++i)
  {
    ASSERT_EQ(face[i].m_vert[0],idx);
    ASSERT_EQ(face[i].m_vert[1],idx+1);
    ASSERT_EQ(face[i].m_vert[2],idx+2);
    ASSERT_EQ(face[i].m_vert[3],idx+3);
    idx+=4;
  }
}



TEST(Obj,checkFace)
{
  ngl::Obj a("files/Triangle1.obj");
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);

  ASSERT_EQ(face[0].m_norm[0],0);
  ASSERT_EQ(face[0].m_norm[1],1);
  ASSERT_EQ(face[0].m_norm[2],2);

  ASSERT_EQ(face[0].m_uv[0],0);
  ASSERT_EQ(face[0].m_uv[1],1);
  ASSERT_EQ(face[0].m_uv[2],2);
}

TEST(Obj,addVertex)
{
  ngl::Obj a;
  for(size_t i=0; i<20; ++i)
    a.addVertex({static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)});

  auto verts=a.getVertexList();
  for(size_t i=0; i<20; ++i)
  {
    EXPECT_TRUE(verts[i]==ngl::Vec3(static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)));
  }
}

TEST(Obj,addNormal)
{
  ngl::Obj a;
  for(size_t i=0; i<20; ++i)
    a.addNormal({static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)});

  auto norm=a.getNormalList();
  for(size_t i=0; i<20; ++i)
  {
    EXPECT_TRUE(norm[i]==ngl::Vec3(static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)));
  }
}


TEST(Obj,addUVVec3)
{
  ngl::Obj a;
  for(size_t i=0; i<20; ++i)
    a.addUV({static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)});

  auto uv=a.getUVList();
  for(size_t i=0; i<20; ++i)
  {
    EXPECT_TRUE(uv[i]==ngl::Vec3(static_cast<float>(i),static_cast<float>(i),static_cast<float>(i)));
  }
}

TEST(Obj,addUVVec2)
{
  ngl::Obj a;
  for(size_t i=0; i<20; ++i)
    a.addUV(ngl::Vec2(static_cast<float>(i),static_cast<float>(i)));

  auto uv=a.getUVList();
  for(size_t i=0; i<20; ++i)
  {
    EXPECT_TRUE(uv[i]==ngl::Vec3(static_cast<float>(i),static_cast<float>(i),0.0f));
  }
}

TEST(Obj,addFace)
{
  ngl::Obj a;
  ngl::Face f;
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  f.m_norm.push_back(0);
  f.m_norm.push_back(1);
  f.m_norm.push_back(2);
  f.m_uv.push_back(0);
  f.m_uv.push_back(1);
  f.m_uv.push_back(2);

  a.addFace(f);
  std::vector<ngl::Face> face=a.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);

  ASSERT_EQ(face[0].m_norm[0],0);
  ASSERT_EQ(face[0].m_norm[1],1);
  ASSERT_EQ(face[0].m_norm[2],2);

  ASSERT_EQ(face[0].m_uv[0],0);
  ASSERT_EQ(face[0].m_uv[1],1);
  ASSERT_EQ(face[0].m_uv[2],2);
}

std::unique_ptr<ngl::Obj> buildObj()
{
  std::unique_ptr<ngl::Obj> a=std::make_unique<ngl::Obj>();

  a->addVertex({2.00000f,0.00000f,0.000000f});
  a->addVertex({0.0000f,4.0000f,0.000000});
  a->addVertex({-2.00000f,0.000000f,0.000000});
  a->addUV({1.000000f,0.000000f});
  a->addUV({0.500000f,1.000000f});
  a->addUV({0.004399f,0.008916f});
  a->addNormal({0.000000f,0.000000f,1.000000f});
  a->addNormal({0.000000f,0.000000f,1.000000f});
  a->addNormal({0.000000f,0.000000f,1.000000f});
  ngl::Face f;
  // f 1/1/1 2/2/1 3/3/1
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  f.m_uv.push_back(0);
  f.m_uv.push_back(1);
  f.m_uv.push_back(2);
  f.m_norm.push_back(0);
  f.m_norm.push_back(1);
  f.m_norm.push_back(2);
  a->addFace(f);

  return a;
}


TEST(Obj,buildObj)
{
  std::unique_ptr<ngl::Obj> a=buildObj();
  std::vector<ngl::Face> face=a->getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  ASSERT_EQ(face[0].m_norm[0],0);
  ASSERT_EQ(face[0].m_norm[1],1);
  ASSERT_EQ(face[0].m_norm[2],2);
  ASSERT_EQ(face[0].m_uv[0],0);
  ASSERT_EQ(face[0].m_uv[1],1);
  ASSERT_EQ(face[0].m_uv[2],2);
  auto verts=a->getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));
  auto norm=a->getNormalList();
  ASSERT_TRUE(norm[0]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[1]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[2]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  auto uv=a->getUVList();
  ASSERT_TRUE(uv[0]==ngl::Vec3(1.000000f,0.000000f,0.000000f));
  ASSERT_TRUE(uv[1]==ngl::Vec3(0.500000f,1.000000f,0.000000f));
  ASSERT_TRUE(uv[2]==ngl::Vec3(0.004399f,0.008916f,0.000000f));


}

TEST(Obj,saveVertsOnly)
{
  ngl::Obj a;

  a.addVertex({2.00000f,0.00000f,0.000000f});
  a.addVertex({0.0000f,4.0000f,0.000000});
  a.addVertex({-2.00000f,0.000000f,0.000000});
  ngl::Face f;
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  a.addFace(f);
  a.save("faceOnly.obj");

  ngl::Obj b("faceOnly.obj");
  std::vector<ngl::Face> face=b.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  auto verts=b.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));

}


TEST(Obj,saveVertsUV)
{
  ngl::Obj a;

  a.addVertex({2.00000f,0.00000f,0.000000f});
  a.addVertex({0.0000f,4.0000f,0.000000});
  a.addVertex({-2.00000f,0.000000f,0.000000});
  a.addUV(ngl::Vec2(1.000000f,0.000000f));
  a.addUV(ngl::Vec2(0.500000f,1.000000f));
  a.addUV(ngl::Vec2(0.004399f,0.008916f));

  ngl::Face f;
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  f.m_uv.push_back(0);
  f.m_uv.push_back(1);
  f.m_uv.push_back(2);
  a.addFace(f);
  a.save("faceUV.obj");

  ngl::Obj b("faceUV.obj");
  std::vector<ngl::Face> face=b.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  auto verts=b.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));
  auto uv=b.getUVList();
  ASSERT_TRUE(uv[0]==ngl::Vec3(1.000000f,0.000000f,0.000000f));
  ASSERT_TRUE(uv[1]==ngl::Vec3(0.500000f,1.000000f,0.000000f));
  ASSERT_TRUE(uv[2]==ngl::Vec3(0.004399f,0.008916f,0.000000f));


}

TEST(Obj,saveVertsNormal)
{
  ngl::Obj a;

  a.addVertex({2.00000f,0.00000f,0.000000f});
  a.addVertex({0.0000f,4.0000f,0.000000});
  a.addVertex({-2.00000f,0.000000f,0.000000});
  a.addNormal({0.000000f,0.000000f,1.000000f});
  a.addNormal({0.000000f,0.000000f,1.000000f});
  a.addNormal({0.000000f,0.000000f,1.000000f});


  ngl::Face f;
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  f.m_norm.push_back(0);
  f.m_norm.push_back(1);
  f.m_norm.push_back(2);
  a.addFace(f);
  a.save("faceVertNormal.obj");

  ngl::Obj b("faceVertNormal.obj");
  std::vector<ngl::Face> face=b.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  auto verts=b.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));
  ASSERT_EQ(face[0].m_vert[2],2);
  auto norm=b.getNormalList();
  ASSERT_TRUE(norm[0]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[1]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[2]==ngl::Vec3(0.000000f,0.000000f,1.000000f));


}


TEST(Obj,saveObj)
{
  std::unique_ptr<ngl::Obj> a=buildObj();
  a->save("test.obj");

  ngl::Obj b("test.obj");

  std::vector<ngl::Face> face=b.getFaceList();
  // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);
  ASSERT_EQ(face[0].m_vert[2],2);
  ASSERT_EQ(face[0].m_norm[0],0);
  ASSERT_EQ(face[0].m_norm[1],1);
  ASSERT_EQ(face[0].m_norm[2],2);
  ASSERT_EQ(face[0].m_uv[0],0);
  ASSERT_EQ(face[0].m_uv[1],1);
  ASSERT_EQ(face[0].m_uv[2],2);
  auto verts=b.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));
  auto norm=b.getNormalList();
  ASSERT_TRUE(norm[0]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[1]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  ASSERT_TRUE(norm[2]==ngl::Vec3(0.000000f,0.000000f,1.000000f));
  auto uv=b.getUVList();
  ASSERT_TRUE(uv[0]==ngl::Vec3(1.000000f,0.000000f,0.000000f));
  ASSERT_TRUE(uv[1]==ngl::Vec3(0.500000f,1.000000f,0.000000f));
  ASSERT_TRUE(uv[2]==ngl::Vec3(0.004399f,0.008916f,0.000000f));
}


TEST(Obj,copyctor)
{
  ngl::Obj a;

  a.addVertex({2.00000f,0.00000f,0.000000f});
  a.addVertex({0.0000f,4.0000f,0.000000});
  a.addVertex({-2.00000f,0.000000f,0.000000});
  a.addUV(ngl::Vec2(1.000000f,0.000000f));
  a.addUV(ngl::Vec2(0.500000f,1.000000f));
  a.addUV(ngl::Vec2(0.004399f,0.008916f));

  ngl::Face f;
  f.m_vert.push_back(0);
  f.m_vert.push_back(1);
  f.m_vert.push_back(2);
  f.m_uv.push_back(0);
  f.m_uv.push_back(1);
  f.m_uv.push_back(2);
  a.addFace(f);
  ngl::Obj b(a);
  std::vector<ngl::Face> face=b.getFaceList();
   // face is f 1/1/1 2/2/2 3/3/3 but we index from 0
  ASSERT_EQ(face[0].m_vert[0],0);
  ASSERT_EQ(face[0].m_vert[1],1);

  auto verts=b.getVertexList();
  ASSERT_TRUE(verts[0]==ngl::Vec3(2.00000f,0.00000f,0.000000f));
  ASSERT_TRUE(verts[1]==ngl::Vec3(0.0000f,4.0000f,0.000000));
  ASSERT_TRUE(verts[2]==ngl::Vec3(-2.00000f,0.000000f,0.000000));
  ASSERT_EQ(face[0].m_vert[2],2);
  auto uv=b.getUVList();
  ASSERT_TRUE(uv[0]==ngl::Vec3(1.000000f,0.000000f,0.000000f));
  ASSERT_TRUE(uv[1]==ngl::Vec3(0.500000f,1.000000f,0.000000f));
  ASSERT_TRUE(uv[2]==ngl::Vec3(0.004399f,0.008916f,0.000000f));

}


TEST(Obj,passbyref)
{
  ngl::Obj a;
  for(size_t v=0; v<10; ++v)
    a.addVertex({0,0,0});
  size_t count=0;
  auto countVerts=[&count](const  ngl::Obj &_o)
  {
    auto data=_o.getVertexList();
    for([[maybe_unused]] auto f : data)
    {
      ++count;
    }
  };

  countVerts(a);
  EXPECT_EQ(count,10);
}


TEST(Obj,isTriangular)
{
  {
    ngl::Obj a;
    a.addVertex({2.00000f,0.00000f,0.000000f});
    a.addVertex({0.0000f,4.0000f,0.000000});
    a.addVertex({-2.00000f,0.000000f,0.000000});
    ngl::Face f;
    f.m_vert.push_back(0);
    f.m_vert.push_back(1);
    f.m_vert.push_back(2);
    a.addFace(f);
    EXPECT_TRUE(a.isTriangular());
  }

  {
    ngl::Obj a;
    a.addVertex({2.00000f,0.00000f,0.000000f});
    a.addVertex({0.0000f,4.0000f,0.000000});
    a.addVertex({-2.00000f,0.000000f,0.000000});
    ngl::Face f;
    f.m_vert.push_back(0);
    f.m_vert.push_back(1);
    f.m_vert.push_back(2);
    f.m_vert.push_back(0);
    a.addFace(f);
    EXPECT_FALSE(a.isTriangular());
  }


}