#include <ngl/Mat3.h>
#include <ngl/Vec3.h>
#include <ngl/NGLStream.h>
#include <hayai/hayai.hpp>
#include <hayai/hayai_main.hpp>

static ngl::Mat3 t1;
static ngl::Mat3 t2(1.0);
static ngl::Mat3 t3(2.0);



//void testCtor()
//{
//  ngl::Mat3(2.0);
//}


BENCHMARK(Mat3Tests, Mat3Add, 10, 100)
{
  t1=t2+t3;
}

BENCHMARK(Mat3Tests, Mat3Ctor, 10, 100)
{
  ngl::Mat3(2.0);
}

BENCHMARK(Mat3Tests, TestAssign, 10, 100)
{
    t1=t3;
}
BENCHMARK(Mat3Tests, TestCopyCtor, 10, 100)
{
    ngl::Mat3 t(t3);
}

