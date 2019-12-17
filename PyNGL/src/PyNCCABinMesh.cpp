#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "NCCABinMesh.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitNCCABinMesh(py::module & m)
  {
    py::class_<NCCABinMesh>(m, "NCCABinMesh")
        .def(py::init<>())
        .def(py::init<const std::string &>())
        .def(py::init<const std::string &,const std::string &>())
        .def("load",&NCCABinMesh::load)
        .def("save",&NCCABinMesh::save)

        ;

  }

}
