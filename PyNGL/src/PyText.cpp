#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Text.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitText(py::module & m)
  {
    py::class_<Text>(m, "Text")
        .def(py::init< const QFont &>())
        .def(py::init< const std::string &, int  >())
        .def("renderText", py::overload_cast<float,float,const std::string &  >(&Text::renderText , py::const_ ))
        .def("setScreenSize",&Text::setScreenSize)
        .def("setColour",py::overload_cast<float,float,float>(&Text::setColour))
        .def("setTransform",&Text::setTransform)
        ;

  }
}
