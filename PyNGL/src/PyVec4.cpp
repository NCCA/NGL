#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Vec4.h"
#include "Mat4.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitVec4(py::module & m)
  {

      py::class_<Vec4>(m, "Vec4")
          .def(py::init<>())
          .def(py::init<Real,Real,Real,Real>(),py::arg("_x") = 0.0f,py::arg("_y") = 0.0f,py::arg("_z") = 0.0f,py::arg("_w") = 1.0f)
          .def(py::init<Vec4 &>())
          .def(py::init<Vec3 &,Real >(),py::arg("_v"),py::arg("_w") = 1.0f)
          .def("set", py::overload_cast<Real,Real,Real,Real>( &Vec4::set))
          .def("set", py::overload_cast<const Vec3 &> (&Vec4::set))
          .def("set", py::overload_cast<const Vec4 &> (&Vec4::set))
          .def("dot", &Vec4::dot)
          .def("null", &Vec4::null)
          .def("__getitem__",py::overload_cast<const size_t &>( &Vec4::operator[]))
          .def("normalize", &Vec4::normalize)
          .def("inner", &Vec4::inner)
          .def("outer", &Vec4::outer)
          .def("length", &Vec4::length)
          .def("lengthSquared", &Vec4::lengthSquared)
          .def("cross",py::overload_cast<const Vec4&, const Vec4&> (&Vec4::cross))
          .def("cross",py::overload_cast<const Vec4&>( &Vec4::cross ,py::const_))
          .def_static("sizeof", [](){return sizeof(Vec4);}  )
          .def_static("up", &Vec4::up)
          .def_static("down", &Vec4::down)
          .def_static("left", &Vec4::left)
          .def_static("right", &Vec4::right)
          .def_static("inV", &Vec4::in) // note in is a reserved word so use inV
          .def_static("out", &Vec4::out)
          .def_static("zero", &Vec4::zero)
          .def("toVec3",&Vec4::toVec3)
          .def("toVec2",&Vec4::toVec2)
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
          .def(py::self * ngl::Mat4())
          .def("__neg__", py::overload_cast<> ( &Vec4::operator-))
          .def("__repr__",
                  [](const Vec4 &v) {
                      return "["+std::to_string(v.m_x)+","+
                          std::to_string(v.m_y)+","+
                          std::to_string(v.m_z)+","+
                          std::to_string(v.m_w)
                          +"]";})
          .def_readwrite("m_x", &Vec4::m_x)
          .def_readwrite("m_y", &Vec4::m_y)
          .def_readwrite("m_z", &Vec4::m_z)
          .def_readwrite("m_w", &Vec4::m_w)

          ;

  }

}
