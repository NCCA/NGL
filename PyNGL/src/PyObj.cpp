#include <pybind11/pybind11.h>

#include "Obj.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitObj(py::module & m)
  {
    py::class_<Obj,AbstractMesh>(m, "Obj")
        .def(py::init<>())
        .def(py::init<const std::string&,AbstractMesh::CalcBB>())
        .def(py::init<const std::string&,const std::string&,AbstractMesh::CalcBB>())
        .def(py::init<const char *,const char *,AbstractMesh::CalcBB>())
        .def("load", &Obj::load)
        .def("save", &Obj::save)
        ;

  }

}
