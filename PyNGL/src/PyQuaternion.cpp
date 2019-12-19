#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "Quaternion.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitQuaternion(py::module & m)
  {
    py::class_<Quaternion>(m, "Quaternion")
        .def(py::init<Real,Real,Real,Real>())
        .def(py::init<const Mat4 &>())
        .def(py::init<const Vec3 &>())
        .def(py::init<const Quaternion &>())
        .def("set",&Quaternion::set)
        .def("getS",&Quaternion::getS)
        .def("getX",&Quaternion::getX)
        .def("getY",&Quaternion::getY)
        .def("getZ",&Quaternion::getZ)
        .def("getVector",&Quaternion::getVector)
        .def("setVector",&Quaternion::setVector)
        .def("setS",&Quaternion::setS)
        .def("setX",&Quaternion::setX)
        .def("setY",&Quaternion::setY)
        .def("setZ",&Quaternion::setZ)
        .def("normalise",&Quaternion::normalise)
        .def("magnitude",&Quaternion::magnitude)
        .def("conjugate",&Quaternion::conjugate)
        .def("inverse",&Quaternion::inverse)
        .def("slerp",&Quaternion::slerp)
        .def("rotateX",&Quaternion::rotateX)
        .def("rotateY",&Quaternion::rotateY)
        .def("rotateZ",&Quaternion::rotateZ)
        .def("fromAxisAngle",&Quaternion::fromAxisAngle)
        .def("fromEulerAngles",&Quaternion::fromEulerAngles)
        .def("rotatePoint",&Quaternion::rotatePoint)
        .def("toAxisAngle",&Quaternion::toAxisAngle)
        .def("toMat4",&Quaternion::toMat4)
        .def("toMat4Transpose",&Quaternion::toMat4Transpose)
        .def(py::self + py::self)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self * Real())
        .def(py::self * Vec4())
        .def(py::self *= Real())
        .def(py::self - py::self)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self == py::self)
        .def("__neg__",py::overload_cast<> (&Quaternion::operator-))
        .def("__neg__",py::overload_cast<> (&Quaternion::operator- ,py::const_))
        ;

}

}
