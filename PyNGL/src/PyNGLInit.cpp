#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "NGLInit.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitNGLInit(py::module & m)
  {
    py::class_<NGLInit, std::unique_ptr<NGLInit, py::nodelete>>(m, "NGLInit")
        .def_static("instance",&NGLInit::instance);
        ;

  }

}
