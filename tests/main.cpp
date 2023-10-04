#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <array>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>
#include <string>
#include <ngl/Types.h>
class Environment : public ::testing::Environment
{
    public:
  Environment(bool _useOpenGL)
    : m_useOpenGL(_useOpenGL)
  {
  }
  virtual ~Environment() override
  {
  }
  // Override this to define how to set up the environment.
  virtual void SetUp() override;

  // Override this to define how to tear down the environment.
  virtual void TearDown() override;

    private:
  bool m_useOpenGL = true;
};

void Environment::SetUp()
{
  if(m_useOpenGL == true)
  {
    std::cerr << "Creating OpenGL Context\n";
    GLFWwindow *window;

    /* Initialize the library */
    auto init = glfwInit();
    ASSERT_TRUE(init == GLFW_TRUE) << "Failed to create init GLFW need an X server\n";

    // use GL 4.1 as it's the max mac can use.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1024, 720, "", nullptr, nullptr);
    ASSERT_TRUE(window != nullptr);
    if(!window)
    {
      glfwTerminate();
      std::exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // whilst we will do this in a test, best to make sure we have a valid context here
    // incase we run isolated tests on just GL elements
    ngl::NGLInit::initialize();
  }
}

void Environment::TearDown()
{
  std::cerr << "Teardown removing files\n";
  // remove the temp obj files
  std::array< std::string, 4 > files = {{"faceOnly.obj", "faceUV.obj", "faceVertNormal.obj", "test.obj"}};
  for(auto f : files)
    std::remove(f.c_str());
  if(m_useOpenGL == true)
  {
    std::cerr << "remove OpenGL Context\n";

    glfwTerminate();
  }
}

int main(int argc, char **argv)
{
  bool useOpenGL = true;
  testing::InitGoogleTest(&argc, argv);
  if(argc > 1)
  {
    if(std::string(argv[1]) == "-g")
      useOpenGL = false;
  }

  ::testing::AddGlobalTestEnvironment(new Environment(useOpenGL));
  if(useOpenGL == false)
  {
    std::cerr << "excluding tests\n";
    ::testing::GTEST_FLAG(filter) = "-ShaderLib.*:Shader*:VAOPrimitives.*:NGLInit*:VAOFactory*";
  }
  // should put this on an argument
  // testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();
  return RUN_ALL_TESTS();
  
}
