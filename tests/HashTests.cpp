#include <gtest/gtest.h>
#include <ngl/NGLHash.h>
#include <unordered_map>
#include <unordered_set>

TEST(Hash,Vec2)
{
  ngl::Vec2 a(0.0f,0.1f);
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Vec2>{}(a)>0);
  // use an unordered_map of Vec2 to count
  std::unordered_map<ngl::Vec2,int,std::hash<ngl::Vec2>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Vec2,std::hash<ngl::Vec2>> set;
  set.insert(ngl::Vec2());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Vec3)
{
  ngl::Vec3 a(0.0f,1.0f,2.5f);
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Vec3>{}(a)>0);
  // use an unordered_map of Vec3 to count
  std::unordered_map<ngl::Vec3,int,std::hash<ngl::Vec3>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Vec3,std::hash<ngl::Vec3>> set;
  set.insert(ngl::Vec3());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Vec4)
{
  ngl::Vec4 a(0.0f,1.0f,2.5f,1.0f);
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Vec4>{}(a)>0);
  // use an unordered_map of Vec4 to count
  std::unordered_map<ngl::Vec4,int,std::hash<ngl::Vec4>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Vec4,std::hash<ngl::Vec4>> set;
  set.insert(ngl::Vec4());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Quaternion)
{
  ngl::Quaternion a(0.0f,1.0f,2.5f,1.0f);
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Quaternion>{}(a)>0);
  // use an unordered_map of Quaternion to count
  std::unordered_map<ngl::Quaternion,int,std::hash<ngl::Quaternion>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Quaternion,std::hash<ngl::Quaternion>> set;
  set.insert(ngl::Quaternion());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Mat2)
{
  ngl::Mat2 a;
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Mat2>{}(a)>0);
  // use an unordered_map of Quaternion to count
  std::unordered_map<ngl::Mat2,int,std::hash<ngl::Mat2>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Mat2,std::hash<ngl::Mat2>> set;
  set.insert(ngl::Mat2());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Mat3)
{
  ngl::Mat3 a;
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Mat3>{}(a)>0);
  // use an unordered_map of Quaternion to count
  std::unordered_map<ngl::Mat3,int,std::hash<ngl::Mat3>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Mat3,std::hash<ngl::Mat3>> set;
  set.insert(ngl::Mat3());
  EXPECT_TRUE(set.size()>0);
}

TEST(Hash,Mat4)
{
  ngl::Mat4 a;
  // see if we can hash 
  EXPECT_TRUE(std::hash<ngl::Mat4>{}(a)>0);
  // use an unordered_map of Quaternion to count
  std::unordered_map<ngl::Mat4,int,std::hash<ngl::Mat4>> map;
  map[a]=1;
  EXPECT_TRUE(map.size()>0);
  // Can we put something in a set?
  std::unordered_set<ngl::Mat4,std::hash<ngl::Mat4>> set;
  set.insert(ngl::Mat4());
  EXPECT_TRUE(set.size()>0);
}