#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <ngl/Random.h>
#include <string>
#include <sstream>
#include <glm/vec4.hpp>


// so testing randomness is a weird thing, however we can test for ranges
// in these cases I will use a different seed each time which may also help to show up issues
// in all cases I will just see if I get the range I need.


TEST(Random,vec2)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::getRandomVec2();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
}


TEST(Random,vec3)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::getRandomVec3();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
    EXPECT_TRUE(v.m_z>=-1.0f && v.m_z<=1.0f);
}


TEST(Random,point)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::getRandomPoint(20,20,20);
    EXPECT_TRUE(v.m_x>=-20.0f && v.m_x<=20.0f);
    EXPECT_TRUE(v.m_y>=-20.0f && v.m_y<=20.0f);
    EXPECT_TRUE(v.m_z>=-20.0f && v.m_z<=20.0f);
}

TEST(Random,vec4)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::getRandomVec4();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
    EXPECT_TRUE(v.m_z>=-1.0f && v.m_z<=1.0f);
    EXPECT_TRUE(v.m_w>=-1.0f && v.m_w<=1.0f);
}


TEST(Random,randomNumberDefault)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::randomNumber();
    EXPECT_TRUE(v>=-1.0f && v<=1.0f);
}

TEST(Random,randomNumberParam)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::randomNumber(2000.0);
    EXPECT_TRUE(v>=-2000.0f && v<=2000.0f);
}

TEST(Random,randomPositiveNumberDefault)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::randomPositiveNumber();
    EXPECT_TRUE(v>=0.0f && v<=1.0f);
}

TEST(Random,randomPositiveNumberParam)
{
    ngl::Random::setSeed();
    auto v=ngl::Random::randomPositiveNumber(2000.0);
    EXPECT_TRUE(v>=0.0f && v<=2000.0f);
}



TEST(Random,addIntGenerator)
{
    ngl::Random::setSeed();
    auto dist=std::uniform_int_distribution<int>(-100,100);
    ngl::Random::addIntGenerator("test",dist);
    auto test=ngl::Random::getIntFromGeneratorName("test");
    EXPECT_TRUE(test>=-100 && test <=100);
}


TEST(Random,addFloatGenerator)
{
    ngl::Random::setSeed();
    auto dist=std::uniform_real_distribution<float>(0.0f,5.0f);
    ngl::Random::addFloatGenerator("test",dist);
    auto test=ngl::Random::getFloatFromGeneratorName("test");
    EXPECT_TRUE(test>=0.0f && test <=5.0f);
}




