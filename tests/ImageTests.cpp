#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Image.h>
#include <fmt/format.h>
#include "pystring.h"

namespace ps=pystring;

TEST(Image,DefaultCtor)
{
  ngl::Image img;
  ngl::Image::info();
}

// build in image lib only has limited support
#if defined(USEBUILTINIMAGE)
  std::vector<std::string_view> g_extensionsRGB={".png",".tga",".bmp",".jpg"};
  std::vector<std::string_view> g_extensionsRGBA={".png",".tga",".bmp"};

#else
  std::vector<std::string_view> g_extensionsRGB={".png",".tiff",".tga",".exr",".bmp"};
  std::vector<std::string_view> g_extensionsRGBA={".png",".tiff",".tga",".exr",".bmp"};

#endif

TEST(Image,createSimpleImageRGBA)
{
  int size=4;
  // Note JPG should only be RGB not RGBA
  ngl::Image img(size,size);
  
  for(int x=0; x<size; ++x)
  {
   img.setPixel(x,0,255,0,0,255); 
   img.setPixel(x,1,0,255,0,255); 
   img.setPixel(x,2,0,0,255,255); 
   img.setPixel(x,3,255,255,255,255); 
  }
  for(auto ext : g_extensionsRGBA)
    img.save(fmt::format("simpleRGBA{}",ext));
}


TEST(Image,createSimpleImageRGB)
{
  int size=4;
  ngl::Image img(size,size,ngl::Image::ImageModes::RGB);
  
  for(int x=0; x<size; ++x)
  {
   img.setPixel(x,0,255,0,0); 
   img.setPixel(x,1,0,255,0); 
   img.setPixel(x,2,0,0,255); 
   img.setPixel(x,3,255,255,255); 
  }
  for(auto ext : g_extensionsRGB)
  {
    img.save(fmt::format("simpleRGB{}",ext),true);
  }
}

TEST(Image,loadRGB)
{
  for(auto ext : g_extensionsRGB)
  {
    // jpg is lossy so these type of tests just don't work.
    // we can write out and test visually. This is why we don't use
    // jpg in CGI :-)
    if(ext == ".jpg")
      continue;
    ngl::Image img(fmt::format("files/simpleRGB{}",ext),false);
    EXPECT_EQ(img.width(),4);
    EXPECT_EQ(img.height(),4);
    // getPixel will return the raw data so test against this
    auto pixels=img.getPixels();
    // first row should be white check 
    EXPECT_EQ(pixels[0],255);
    EXPECT_EQ(pixels[1],255);
    EXPECT_EQ(pixels[2],255);
    // now blue which is 2nd row so offset width by 3 pixels
    EXPECT_EQ(pixels[(4*3)+0],0);
    EXPECT_EQ(pixels[(4*3)+1],0);
    EXPECT_EQ(pixels[(4*3)+2],255);
    // now green
    EXPECT_EQ(pixels[(8*3)+0],0);
    EXPECT_EQ(pixels[(8*3)+1],255);
    EXPECT_EQ(pixels[(8*3)+2],0);
    // now red
    EXPECT_EQ(pixels[(12*3)+0],255);
    EXPECT_EQ(pixels[(12*3)+1],0);
    EXPECT_EQ(pixels[(12*3)+2],0);
  }
}




TEST(Image,loadRGBA)
{
  for(auto ext : g_extensionsRGBA)
  {
    // jpg is lossy so these type of tests just don't work.
    // we can write out and test visually. This is why we don't use
    // jpg in CGI :-)
    if(ext == ".jpg")
      continue;
    ngl::Image img(fmt::format("files/simpleRGBA{}",ext),false);
    EXPECT_EQ(img.width(),4);
    EXPECT_EQ(img.height(),4);
    // getPixel will return the raw data so test against this
    auto pixels=img.getPixels();
    // first row should be white check 
    EXPECT_EQ(pixels[0],255);
    EXPECT_EQ(pixels[1],255);
    EXPECT_EQ(pixels[2],255);
    EXPECT_EQ(pixels[4],255);
    
    // now blue which is 2nd row so offset width by 3 pixels
    EXPECT_EQ(pixels[(4*4)+0],0);
    EXPECT_EQ(pixels[(4*4)+1],0);
    EXPECT_EQ(pixels[(4*4)+2],255);
    EXPECT_EQ(pixels[(4*4)+3],255);
    // now green
    EXPECT_EQ(pixels[(8*4)+0],0);
    EXPECT_EQ(pixels[(8*4)+1],255);
    EXPECT_EQ(pixels[(8*4)+2],0);
    EXPECT_EQ(pixels[(8*4)+3],255);
    // now red
    EXPECT_EQ(pixels[(12*4)+0],255);
    EXPECT_EQ(pixels[(12*4)+1],0);
    EXPECT_EQ(pixels[(12*4)+2],0);
    EXPECT_EQ(pixels[(12*4)+3],255);
  }
}