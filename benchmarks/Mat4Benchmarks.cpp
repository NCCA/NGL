#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <ngl/NGLStream.h>
#include <hayai/hayai.hpp>
#include <hayai/hayai_main.hpp>

static ngl::Mat4 t1;
static ngl::Mat4 t2(1.0);
static ngl::Mat4 t3(2.0);


BENCHMARK(Mat4Tests, Mat4Add, 10, 100)
{
  t1=t2+t3;
}

BENCHMARK(Mat4Tests, Mat4Ctor, 10, 100)
{
  ngl::Mat4(2.0);
}

BENCHMARK(Mat4Tests, TestAssign, 10, 100)
{
    t1=t3;
}
BENCHMARK(Mat4Tests, TestCopyCtor, 10, 100)
{
    ngl::Mat4 t(t3);
}



