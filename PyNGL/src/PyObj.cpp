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
        .def(py::init<const std::string_view&,AbstractMesh::CalcBB>(),
             "constructor", py::arg("_fname")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def(py::init<const std::string_view&,const std::string_view&,AbstractMesh::CalcBB>(),
             "constructor with texture", py::arg("_fname")="", py::arg("_texName")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def(py::init<const char *,const char *,AbstractMesh::CalcBB>(),
             "constructor", py::arg("_fname")="", py::arg("_texName")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)

        .def("load",(bool (Obj::*)(const std::string_view &_fname, AbstractMesh::CalcBB _calcBB)) &Obj::load,"load mesh returns true if succesful", py::arg("_fname")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def("save", &Obj::save)
        .def("isLoaded", &Obj::isLoaded)
        .def("addVertex",&Obj::addVertex)
        .def("addFace",&Obj::addFace)
        .def("addNormal",&Obj::addNormal)
        .def("addUV", (void (Obj::*)(const Vec2 &)) &Obj::addUV)
        .def("addUV", (void (Obj::*)(const Vec3 &)) &Obj::addUV)
        .def("setTexture",&Obj::setTexture)

        ;


  }

}
