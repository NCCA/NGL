#include "PyBindIncludes.h"


#include "Obj.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitObj(py::module & m)
  {
    py::class_<Obj,AbstractMesh>(m, "Obj")
        .def(py::init<>())
        .def(py::init<const std::string&,AbstractMesh::CalcBB>(),
             "constructor", py::arg("_fname")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def(py::init<const std::string&,const std::string&,AbstractMesh::CalcBB>(),
             "constructor with texture", py::arg("_fname")="", py::arg("_texName")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def(py::init<const char *,const char *,AbstractMesh::CalcBB>(),
             "constructor", py::arg("_fname")="", py::arg("_texName")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)

        .def("load",py::overload_cast<const std::string &, AbstractMesh::CalcBB > (&Obj::load) ,"load mesh returns true if succesful", py::arg("_fname")="",py::arg("_calcBB")=AbstractMesh::CalcBB::False)
        .def("save", &Obj::save)
        .def("isLoaded", &Obj::isLoaded)
        .def("addVertex",&Obj::addVertex)
        .def("addFace",&Obj::addFace)
        .def("addNormal",&Obj::addNormal)
        .def("addUV", py::overload_cast<const Vec2 &> (&Obj::addUV))
        .def("addUV", py::overload_cast<const Vec3 &> (&Obj::addUV))
        .def("setTexture",&Obj::setTexture)

        ;


  }

}
