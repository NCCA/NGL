#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/NCCAPointBake.h>
#include <ngl/Obj.h>

TEST(PointBake,defaultctor)
{
    auto pb=ngl::NCCAPointBake();
    EXPECT_EQ(pb.getNumFrames(),-1);
    EXPECT_EQ(pb.getNumVerts(),0);
    EXPECT_EQ(pb.getStartFrame(),0);
    EXPECT_EQ(pb.getEndFrame(),0);
}

TEST(PointBake,filector)
{
    auto pb=ngl::NCCAPointBake("files/Tri.xml");
    EXPECT_EQ(pb.getNumFrames(),2);
    EXPECT_EQ(pb.getNumVerts(),3);
    EXPECT_EQ(pb.getStartFrame(),1);
    EXPECT_EQ(pb.getEndFrame(),3);
}


TEST(PointBake,addMesh)
{
    auto pb=ngl::NCCAPointBake("files/Tri.xml");
    auto mesh=ngl::Obj();
    EXPECT_TRUE(mesh.load("files/Triangle1.obj",ngl::Obj::CalcBB::False));
    EXPECT_TRUE(pb.attachMesh(&mesh));
}

TEST(PointBake,meshAt)
{
    auto pb=ngl::NCCAPointBake("files/Tri.xml");
    auto verts=pb.getRawDataPointerAtFrame(0);
    EXPECT_TRUE(verts.size()==3);
    EXPECT_TRUE(verts[0]==ngl::Vec3(2.0f,0.0f,0.0f));
    EXPECT_TRUE(verts[1]==ngl::Vec3(0.0f,4.0f,0.0f));
    EXPECT_TRUE(verts[2]==ngl::Vec3(-2.0f,0.0f,0.0f));

    verts=pb.getRawDataPointerAtFrame(1);
    EXPECT_TRUE(verts[0]==ngl::Vec3(3.0f,0.0f,0.0f));
    EXPECT_TRUE(verts[1]==ngl::Vec3(0.0f,5.0f,0.0f));
    EXPECT_TRUE(verts[2]==ngl::Vec3(-3.0f,0.0f,0.0f));

    verts=pb.getRawDataPointerAtFrame(2);
    EXPECT_TRUE(verts[0]==ngl::Vec3(4.0f,0.0f,0.0f));
    EXPECT_TRUE(verts[1]==ngl::Vec3(0.0f,6.0f,0.0f));
    EXPECT_TRUE(verts[2]==ngl::Vec3(-4.0f,0.0f,0.0f));

}

