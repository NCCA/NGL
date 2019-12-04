#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "SimpleIndexVAO.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitSimpleIndexVAO(py::module & m)
  {
    py::class_<SimpleIndexVAO,AbstractVAO>(m, "SimpleIndexVAO")
        .def_static("create",&SimpleIndexVAO::create)
        .def("draw", &SimpleIndexVAO::draw)
        .def("removeVAO", &SimpleIndexVAO::removeVAO)
        //.def("setData", &SimpleIndexVAO::setData)
        .def("setData", py::overload_cast<size_t , const std::vector<Vec3> &, unsigned int , const std::vector<GLushort> &>(&SimpleIndexVAO::setData))

        .def("getBufferID", &SimpleIndexVAO::getBufferID)

        ;

  }

}
