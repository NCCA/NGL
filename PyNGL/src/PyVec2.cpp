#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Vec2.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitVec2(py::module & m)
  {
    py::class_<Vec2>(m, "Vec2")
        .def(py::init<>())
        .def(py::init<const Vec2 &>())
        .def(py::init<Real,Real>(),py::arg("_x")=0.0f,py::arg("_y")=1.0f)
        .def("dot", &Vec2::dot)
        .def("null", &Vec2::null)
        .def("__getitem__",(Real& (Vec2::*)(const size_t &)) &Vec2::operator[])
        .def("normalize", &Vec2::normalize)
        .def_static("zero", &Vec2::zero)
        .def("length", &Vec2::length)
        .def("lengthSquared", &Vec2::lengthSquared)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def_readwrite("m_x", &Vec2::m_x)
        .def_readwrite("m_y", &Vec2::m_y)
        .def_static("sizeof", [](){return sizeof(Vec2);}  )


       ;
  }

}
