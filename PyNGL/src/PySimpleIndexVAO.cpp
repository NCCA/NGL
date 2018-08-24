#include <pybind11/pybind11.h>

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
        .def("setData", &SimpleIndexVAO::setData)
        .def("getBufferID", &SimpleIndexVAO::getBufferID)

        ;

  }

}
