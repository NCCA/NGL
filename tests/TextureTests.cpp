#include <gtest/gtest.h>
#include <ngl/Texture.h>

TEST(Texture,construct)
{
    auto t=ngl::Texture();
    EXPECT_TRUE(t.width()==0);
    EXPECT_TRUE(t.height()==0);
    EXPECT_TRUE(t.format()==GL_RGB);
    EXPECT_TRUE(t.getImage().width()==0);
    EXPECT_TRUE(t.getImage().height()==0);
}

TEST(Texture,loadRGB)
{
    auto t=ngl::Texture("files/simpleRGB.bmp");
    EXPECT_TRUE(t.width()==4);
    EXPECT_TRUE(t.height()==4);
    EXPECT_TRUE(t.format()==GL_RGB);
    EXPECT_TRUE(t.getImage().width()==4);
    EXPECT_TRUE(t.getImage().height()==4);

}

TEST(Texture,loadRGBA)
{
    auto t=ngl::Texture("files/simpleRGBA.bmp");
    EXPECT_TRUE(t.width()==4);
    EXPECT_TRUE(t.height()==4);
    EXPECT_TRUE(t.format()==GL_RGBA);
    EXPECT_TRUE(t.getImage().width()==4);
    EXPECT_TRUE(t.getImage().height()==4);

}
