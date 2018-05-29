#include <gtest/gtest.h>
#include <array>
#include <string>

class Environment : public  ::testing::Environment
{
 public:
  virtual ~Environment() {}
  // Override this to define how to set up the environment.
  virtual void SetUp()
  {
  }
  // Override this to define how to tear down the environment.
  virtual void TearDown()
  {
    std::cerr<<"Teardown removing files\n";
    // remove the temp obj files
    std::array<std::string,4>files={{"faceOnly.obj","faceUV.obj","faceVertNormal.obj","test.obj"}};
    for(auto f : files)
      std::remove(f.c_str());
  }
};

int main(int argc, char **argv)
{
  ::testing::AddGlobalTestEnvironment(new Environment);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
