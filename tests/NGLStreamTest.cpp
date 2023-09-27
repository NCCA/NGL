#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec2.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Mat2.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <sstream>

#include <ngl/NGLStream.h>

TEST(NGLStream,Vec2)
{
    ngl::Vec2 test(1,2);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,2]");
    std::stringstream in("1 2");
    ngl::Vec2 result;
    in>>result;
    EXPECT_EQ(result,test);
}

TEST(NGLStream,Vec3)
{
    ngl::Vec3 test(1,2,3);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,2,3]");
    std::stringstream in("1 2 3");
    ngl::Vec3 result;
    in>>result;
    EXPECT_EQ(result,test);
}

TEST(NGLStream,Vec4)
{
    ngl::Vec4 test(1.0f,2.0f,3.0f,4.0f);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,2,3,4]");
    std::stringstream in("1 2 3 4");
    ngl::Vec4 result;
    in>>result;
    EXPECT_EQ(result,test);
}

TEST(NGLStream,Mat2)
{
    ngl::Mat2 test(1.0f,2.0f,3.0f,4.0f);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,2]\n[3,4]\n");
}

TEST(NGLStream,Mat3)
{
    ngl::Mat3 test(1,2,3,4,5,6,7,8,9);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,2,3]\n[4,5,6]\n[7,8,9]\n");
}

TEST(NGLStream,Mat4)
{
    ngl::Mat4 test(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
    std::cerr<<test<<'\n';
    std::stringstream out;
    out<<test;
    EXPECT_EQ(out.str(),"[1,5,9,13]\n[2,6,10,14]\n[3,7,11,15]\n[4,8,12,16]\n");
}
