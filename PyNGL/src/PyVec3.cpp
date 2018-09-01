#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"

#ifdef USEGLM
  #include <glm/vec3.hpp>
#endif

namespace py = pybind11;
namespace ngl
{

  void pyInitVec3(py::module & m)
  {

      py::class_<Vec3>(m, "Vec3")
          .def(py::init<>())
          .def(py::init<Real,Real,Real>())
          .def(py::init<const Vec3 &>())
          .def(py::init<const glm::vec3 &>())
          .def("set", (void (Vec3::*)(Real,Real,Real)) &Vec3::set)
          .def("set", (void (Vec3::*)(const Vec3 &)) &Vec3::set)
          .def("set", (void (Vec3::*)(const Vec4 &)) &Vec3::set)
          .def("dot", &Vec3::dot)
          .def("null", &Vec3::null)
          .def("__getitem__",(Real& (Vec3::*)(const size_t &)) &Vec3::operator[])
          .def("normalize", &Vec3::normalize)
          .def("inner", &Vec3::inner)
          .def("outer", &Vec3::outer)
          .def("length", &Vec3::length)
          .def("lengthSquared", &Vec3::lengthSquared)
          .def("cross",(void (Vec3::*)(const Vec3&, const Vec3&)) &Vec3::cross)
          .def("cross",( Vec3 (Vec3::*)(const Vec3&) const) &Vec3::cross)
          .def("clamp",( void (Vec3::*)(float)) &Vec3::clamp)
          .def("clamp",( void (Vec3::*)(float,float)) &Vec3::clamp)
          .def("reflect", &Vec3::reflect)
          .def_static("up", &Vec3::up)
          .def_static("down", &Vec3::down)
          .def_static("left", &Vec3::left)
          .def_static("right", &Vec3::right)
          .def_static("inV", &Vec3::in) // note in is a reserved word so use inV
          .def_static("out", &Vec3::out)
          .def_static("zero", &Vec3::zero)

          .def(py::self == py::self)
          .def(py::self != py::self)
          .def(py::self += py::self)
          .def(py::self -= py::self)
          .def(py::self * ngl::Real())
          .def(ngl::Real() * py::self)
          .def(py::self + py::self)
          .def(py::self - py::self)
          .def(py::self * py::self)
          .def(py::self / ngl::Real())
          .def(py::self / py::self)
          .def(py::self /= ngl::Real())
          .def(py::self *= ngl::Real())
          .def(py::self * ngl::Mat3())
          .def("__neg__",(Vec3 (Vec3::*)()const) &Vec3::operator-)
          .def("__repr__",
                  [](const Vec3 &v) {
                      return "["+std::to_string(v.m_x)+","+
                          std::to_string(v.m_y)+","+
                          std::to_string(v.m_z)
                          +"]";})
          .def_readwrite("m_x", &Vec3::m_x)
          .def_readwrite("m_y", &Vec3::m_y)
          .def_readwrite("m_z", &Vec3::m_z)

          ;

  }
}
