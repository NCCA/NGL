#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
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
     //   .def(py::init<Real>())
  //      .def("set",(void(Vec2::*)(const Vec2&)) &Vec2::set)
  //      .def("set",(void(Vec2::*)(const Vec3&)) &Vec2::set)
  //      .def("set",(void(Vec2::*)(const Vec4&)) &Vec2::set)
  //      .def("set",(void(Vec2::*)(Real,Real)) &Vec2::set)
       ;
        #warning finish this and tidy the class anyway
  }

}
