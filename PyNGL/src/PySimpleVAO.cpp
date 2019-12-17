#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>
#include "Vec3.h"
#include "SimpleVAO.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitSimpleVAO(py::module & m)
  {
    py::class_<SimpleVAO,AbstractVAO>(m, "SimpleVAO")
        .def_static("create",&SimpleVAO::create)
        .def("draw", &SimpleVAO::draw)
        .def("bind", &SimpleVAO::bind)
        .def("unbind", &SimpleVAO::unbind)
        .def("removeVAO", &SimpleVAO::removeVAO)
        .def("setData", py::overload_cast<size_t,const std::vector<Vec3> &>(&SimpleVAO::setData))
        .def("setData", py::overload_cast<size_t,const std::vector<float> &>(&SimpleVAO::setData))
        .def("getBufferID", &SimpleVAO::getBufferID)
        ;

  }


}
