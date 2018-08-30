#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>


#include "Obj.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitObj(py::module & m)
  {
    py::class_<Obj,AbstractMesh>(m, "Obj")
        .def(py::init<>())
        .def(py::init<const std::string_view&,AbstractMesh::CalcBB>())
        .def(py::init<const std::string_view&,const std::string_view&,AbstractMesh::CalcBB>())
        .def(py::init<const char *,const char *,AbstractMesh::CalcBB>())
        .def("load",(bool (Obj::*)(const std::string_view &_fname, AbstractMesh::CalcBB _calcBB)) &Obj::load)
        .def("save", &Obj::save)
        .def("isLoaded", &Obj::isLoaded)
        .def("addVertex",&Obj::addVertex)
        .def("addFace",&Obj::addFace)
        ;


  }

}
