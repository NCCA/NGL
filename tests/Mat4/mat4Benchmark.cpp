#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <ngl/NGLStream.h>
#include <hayai/hayai.hpp>
#include <hayai/hayai_main.hpp>

static ngl::Mat4 t1;
static ngl::Mat4 t2(1.0);
static ngl::Mat4 t3(2.0);

void testAdd()
{
  t1=t2+t3;
}


BENCHMARK(Mat4Tests, Mat4Add, 10, 100)
{
    testAdd();
}

int main(int argc, char **argv)
{
    // Set up the main runner.
    ::hayai::MainRunner runner;
    // Parse the arguments.
    int result = runner.ParseArgs(argc, argv);
    if (result)
        return result;

    // Execute based on the selected mode.
    return runner.Run();
}
