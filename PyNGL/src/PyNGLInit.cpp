#include "PyBindIncludes.h"

#include "NGLInit.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitNGLInit(py::module & m)
  {
    py::class_<NGLInit, std::unique_ptr<NGLInit, py::nodelete>>(m, "NGLInit")
        .def_static("initialize",&NGLInit::initialize);
  }

}
