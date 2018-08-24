#include <pybind11/pybind11.h>

#include "AABB.h"
namespace py = pybind11;
namespace ngl
{
void pyInitAABB(py::module & m)
{
  py::class_<AABB>(m, "AABB")
      .def(py::init<>())
      .def(py::init<const Vec4 &, Real ,Real ,	Real>())
      .def("set", &AABB::set)
      //.def("setFromBBox",&AABB::setFromBBox)
      .def("getVertexP",&AABB::getVertexP)
      .def("getVertexN",&AABB::getVertexN)
      ;

}

}
