// #include <pybind11/pybind11.h>
// #include <pybind11/operators.h>
// #include <pybind11/stl.h>
// #include <pybind11/cast.h>
#include "PyBindIncludes.h"

#include "Plane.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitPlane(py::module & m)
  {
    py::class_<Plane>(m, "Plane")
        .def(py::init<>())
        .def(py::init<const Vec3 &, const Vec3 &, const Vec3 &>())
        .def("setPoints", &Plane::setPoints)
        .def("setNormalPoint",&Plane::setNormalPoint)
        .def("setFloats",&Plane::setFloats)
        .def("distance",&Plane::distance)
        .def("getNormal",&Plane::getNormal)
        .def("getPoint",&Plane::getPoint)
        .def("getD",&Plane::getD)
        ;

  }


}
